#include <ntddk.h>

void SampleUnload(_In_ PDRIVER_OBJECT DriverObject)
{
	UNREFERENCED_PARAMETER(DriverObject);

	KdPrint(("Sample driver Unload called\n"));
}

extern "C"
NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);

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
