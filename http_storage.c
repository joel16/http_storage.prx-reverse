#include http_storage.h

/*
Subroutine sceHttpStorageOpen - Address 0x00000000 
Exported in sceHttpStorage_driver
Exported in sceHttpStorage
*/
s32 sceHttpStorageOpen()
{

}

/*
Subroutine sceHttpStorageClose - Address 0x000000E0 
Exported in sceHttpStorage_driver
Exported in sceHttpStorage
*/
s32 sceHttpStorageClose()
{

}

/*
Subroutine sceHttpStorageRead - Address 0x00000160 
Exported in sceHttpStorage_driver
Exported in sceHttpStorage
*/
s32 sceHttpStorageRead()
{

}

/*
Subroutine sceHttpStorageWrite - Address 0x000001F0 
Exported in sceHttpStorage_driver
Exported in sceHttpStorage
*/
s32 sceHttpStorageWrite()
{

}

/*
Subroutine sceHttpStorageLseek - Address 0x00000280 
Exported in sceHttpStorage_driver
Exported in sceHttpStorage
*/
s32 sceHttpStorageLseek(int storage_number)
{
	int ret;
    //this is a table of two integers - this is why the $a0 had a << 2, to get the $a0-th integer :-)
    // Data ref 0x000009C0 ... 0xFFFFFFFF 0xFFFFFFFF 0x00000000 0x00000000
    int* http_storage_fd_table = 0x000009C0
 
    int k1_restore = pspSdkSetK1(0);
 
    if (storage_number < 0x2)
	{
		//Enter kernel mode
		pspSdkSetK1(k1 << 11);
		int target_fd = http_storage_fd_table[storage_number];
       
		// check if fd is valid, i-e if the storage has been opened (probably?)
		if (target_fd != -1)
		{
			ret = sceIoLseek(target_fd);
		} 
		else
		{
			ret = 0x80000001;
		}		
    } 
		
	else 
	{
		ret = 0x80000100;
    }
        
	pspSdkSetK1(k1_restore);
    return ret;
}

/*
Subroutine sceHttpStorageGetstat - Address 0x000002F0 
Exported in sceHttpStorage_driver
Exported in sceHttpStorage
*/
s32 sceHttpStorageGetstat(int arg0, SceIoStat * stat)
{
	int ret = 0x80001FFF; 
    int k1 = pspSdkSetK1(0);
       
    if(stat & 0x80000000 >= 0) //kernel check
    {
		if(arg0 == 0)
			ret = sceIoGetStat("flash1:/net/http/auth.dat", stat);
		else if(arg0 == 1)
			ret = sceIoGetStat("flash1:/net/http/cookie.dat", stat);
		else           
			ret = 0x80000100;
	}
       
    pspSdkSetK1(k1);
    return ret;
}

/*
Subroutine module_stop - Address 0x00000368 - Aliases: sceHttpStorageEnd
Exported in syslib
Exported in sceHttpStorage_driver
*/
s32 module_stop()
{
	unsigned * s0 = 0x9C0; //2496
       
    for(int i = 0; i < 2; i++)
    {
		SceUID fd = s0[0]; //$v1
        if(fd != -1)
        {
			sceIoClose(fd);
            s0[0] = -1;
        }       
        s0++; //unsigned pointers increase 4 with ++ operator
	}
           
	return 0;
}

/*
Subroutine module_reboot_before - Address 0x000003D0  
Exported in syslib
Funny how this does the exact same as module_stop o_O
*/
s32 module_reboot_before()
{
	unsigned * s0 = 0x9C0; //2496
		
	for (int i = 0; i < 2; i++)
	{
		SceUID fd = s0[0]; //$v1
		if (v1 != -1)
		{
			sceIoClose(v1);
			s0 = -1;
		}
		s0++; //unsigned pointers increase 4 with ++ operator
	}
		
	return 0;
}

/*
Subroutine sceHttpStorage_bridge_04EF00F8 - Address 0x00000438 
Exported in sceHttpStorage_bridge
*/
s32 sceHttpStorage_bridge_04EF00F8()
{

}

/*
Subroutine sceHttpStorage_bridge_EFE06A20 - Address 0x00000550 
Exported in sceHttpStorage_bridge
*/
s32 sceHttpStorage_bridge_EFE06A20()
{

}
