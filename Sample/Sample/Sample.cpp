#include <ntddk.h>

#define DRIVER_TAG 'dcba'
UNICODE_STRING g_RegistryPath;

void SampleUnload(_In_ PDRIVER_OBJECT DriverObject)
{
	UNREFERENCED_PARAMETER(DriverObject);

	ExFreePoolWithTag(g_RegistryPath.Buffer, DRIVER_TAG);

	KdPrint(("Sample driver Unload called\n"));
}

extern "C"
NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
	g_RegistryPath.Buffer = (WCHAR*)ExAllocatePoolWithTag(PagedPool, RegistryPath->Length, DRIVER_TAG);
	if (!g_RegistryPath.Buffer)
	{
		KdPrint(("Failed to allocate memory\n"));
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	g_RegistryPath.MaximumLength = RegistryPath->Length;
	RtlCopyUnicodeString(&g_RegistryPath, RegistryPath);

	KdPrint(("Copied registry path: %wZ\n", &g_RegistryPath));

	DriverObject->DriverUnload = SampleUnload;

	RTL_OSVERSIONINFOW info;
	NTSTATUS status = RtlGetVersion(&info);
	if (NT_SUCCESS(status))
	{
		KdPrint(("Sample driver initialized successfully\n"));
		KdPrint(("[MY] Major=%u, Minor=%u, Build=%u",
			info.dwMajorVersion, info.dwMinorVersion, info.dwBuildNumber));
	}
	else
	{
		KdPrint(("Sample driver initialized failed\n"));
		KdPrint(("[MY] RtlGetVersion returned %08X", status));
	}

	return status;
}
