# peb-shenanigans
Simple code for interacting with Process Memory Structs. It prints the addresses for the PEB and each of the loaded modules lists (InLoadOrderModuleList, InMemoryOrderModuleList and InInitializationOrderModuleList).

After printing the addresses, the code walks the `InLoadOrderModuleList` and prints the name of the loaded modules via the `FullDllName` member of the `_LDR_MODULE` structure. Said structure starts at the same address as the links of `InLoadOrderModuleList` list, which is why the code attributes the types `PLIST_ENTRY` and `PLDR_MODULE` to the same variable (`Next`).

The Windows internal memory structs and the code to get the PEB address and to walk the loaded modules list were supplied by the [VX-API](https://github.com/vxunderground/VX-API) repository from [vx-undeground](https://github.com/vxunderground).
