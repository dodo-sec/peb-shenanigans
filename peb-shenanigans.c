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
	PPEB pointPEB = GetPeb();

	//print PEB address

	unsigned long long int *PEBAddr = &pointPEB;

	printf("PEB is at 0x%llx\n", *PEBAddr);	//we dereference PEBAddr here because it points to a pointer that points to PEB

	//get _LDR_DATA from PEB

	PPEB_LDR_DATA pointLdr = pointPEB->LoaderData;

	//print module lists addresses

	unsigned long long InLoadOrderAddr = &pointLdr->InLoadOrderModuleList;

	unsigned long long InMemoryOrderAddr = &pointLdr->InMemoryOrderModuleList;

	unsigned long long InInitOrderAddr = &pointLdr->InInitializationOrderModuleList;

	printf("InLoadOrderModuleList is at 0x%llx\n", InLoadOrderAddr);	//these pointers don't need dereferencing because they point at the lists themselves

	printf("InMemoryOrderModuleList is at 0x%llx\n", InMemoryOrderAddr);

	printf("InInitializationOrderModuleList is at 0x%llx\n", InInitOrderAddr);

	//get first node in InMemoryOrderModuleList list

	PLIST_ENTRY InMemoryListHead = &pointLdr->InLoadOrderModuleList;

	PLIST_ENTRY Next = InMemoryListHead->Flink;

	//loop the list while printing module names

	while (Next != InMemoryListHead)
	{
		PLDR_MODULE PModule = Next;

		PWSTR ModuleName = PModule->FullDllName.Buffer;

		printf("Module name is %S\n", ModuleName);

		Next = Next->Flink;
	}

}
