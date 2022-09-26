#include <Core.h>
#include <Win32.h>

SEC( text, B ) VOID Entry( VOID ) 
{
    INSTANCE Instance = { };

    Instance.Modules.Kernel32   = LdrModulePeb( HASH_KERNEL32 ); 
    Instance.Modules.Ntdll      = LdrModulePeb( HASH_NTDLL ); 

    if ( Instance.Modules.Kernel32 != NULL )
    {
        // Load needed functions
        Instance.Win32.LoadLibraryA = LdrFunction( Instance.Modules.Kernel32, 0xb7072fdb );

        // Load needed Libraries
        Instance.Modules.User32     = Instance.Win32.LoadLibraryA( GET_SYMBOL( "User32" ) );
        
        if ( Instance.Modules.User32 != NULL ) 
        {
            Instance.Win32.MessageBoxA = LdrFunction( Instance.Modules.User32, 0xb303ebb4 );
        } 
    }
    
    // ------ Code ------
    Instance.Win32.MessageBoxA( NULL, GET_SYMBOL( "Hello World" ), GET_SYMBOL( "MessageBox Title" ), MB_OK );
} 