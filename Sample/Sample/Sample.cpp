#include <ntddk.h>


NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverOBject, _In_ PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(DriverOBject);
	UNREFERENCED_PARAMETER(RegistryPath);

	return STATUS_SUCCESS;
}
