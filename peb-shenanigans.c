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

	printf("PEB is at 0x%p\n", peb);

	//get _LDR_DATA from PEB

	PPEB_LDR_DATA ldr = peb->LoaderData;

	//print module lists addresses

	PLIST_ENTRY load_head = &ldr->InLoadOrderModuleList;	//use first node of LIST_ENTRY as head

	PLIST_ENTRY memory_head = &ldr->InMemoryOrderModuleList;

	PLIST_ENTRY init_head = &ldr->InInitializationOrderModuleList;

	printf("InLoadOrderModuleList is at 0x%p\n", load_head);

	printf("InMemoryOrderModuleList is at 0x%p\n", memory_head);

	printf("InInitializationOrderModuleList is at 0x%p\n", init_head);

	//loop the list while printing module names
	
	PLIST_ENTRY next = load_head->Flink;

	while (next != load_head)	//code for walking the list stolen from smelly-vx (https://github.com/vxunderground/VX-API/blob/main/VX-API/RemoveDllFromPeb.cpp)
	{
		PLDR_MODULE module = next;

		PWSTR module_name = module->FullDllName.Buffer;

		printf("Module name is %S\n", module_name);

		next = next->Flink;
	}

}
