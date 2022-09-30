#include <stdio.h>
#include <Windows.h>
#include <Internal.h>


PPEB GetPeb(void) //stolen from smelly-vx (https://github.com/vxunderground/VX-API)
{
#ifdef _M_X64
	//If 64 bits architecture
	return (PPEB)__readgsqword(0x60);
#else
	//If 32 bits architecture
	return (PPEB)__readfsdword(0x30);
#endif
}

void main()
{
	PPEB peb = GetPeb();

	//print PEB address

	printf("PEB is at 0x%llx\n", peb);

	//get _LDR_DATA from PEB

	PPEB_LDR_DATA ldr = peb->LoaderData;

	//print module lists addresses

	unsigned long long in_load_addr = &ldr->InLoadOrderModuleList;

	unsigned long long in_memory_addr = &ldr->InMemoryOrderModuleList;

	unsigned long long in_init_addr = &ldr->InInitializationOrderModuleList;

	printf("InLoadOrderModuleList is at 0x%llx\n", in_load_addr);	//these pointers don't need dereferencing because they point at the lists themselves

	printf("InMemoryOrderModuleList is at 0x%llx\n", in_memory_addr);

	printf("InInitializationOrderModuleList is at 0x%llx\n", in_init_addr);

	//get first node in InMemoryOrderModuleList list

	PLIST_ENTRY list_head = &ldr->InLoadOrderModuleList;

	PLIST_ENTRY next_entry = InLoadOrderHead->Flink;

	//loop the list while printing module names

	while (next_entry != list_head)	//code for walking the list stolen from smelly-vx (https://github.com/vxunderground/VX-API/blob/main/VX-API/RemoveDllFromPeb.cpp)
	{
		PLDR_MODULE module = next_entry;

		PWSTR module_name = module->FullDllName.Buffer;

		printf("Module name is %S\n", module_name);

		next_entry = next_entry->Flink;
	}

}
