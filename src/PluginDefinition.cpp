//
//SubShortCut
//this file is part of notepad++
//
//	E : save file & quit editor
//	N : open file
//	O : reopen file
//	S : save file
//	T : go to top of file
//
// if you set SubShortCut at short cut ESC, for example,
//	push ESC, and push N, then open file.
//

#include "PluginDefinition.h"
#include "menuCmdID.h"

//
// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE /*hModule*/)
{
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{

    //--------------------------------------------//
    //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
    //--------------------------------------------//
    // with function :
    // setCommand(int index,                      // zero based number to indicate the order of command
    //            TCHAR *commandName,             // the command name that you want to see in plugin menu
    //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
    //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
    //            bool check0nInit                // optional. Make this menu item be checked visually
    //            );
    setCommand(0, TEXT("SubShortCut"), SubShortCut, NULL, false);
}

//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut here
}


//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit) 
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}

//----------------------------------------------//
//-- STEP 4. DEFINE YOUR ASSOCIATED FUNCTIONS --//
//----------------------------------------------//
//

#include	<conio.h>

HWND GetCurrentScintilla ()
{
    int	which = -1;
    ::SendMessage( nppData._nppHandle,
							NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which );
    if( which == -1 ) return NULL;
	return (which == 0) ?
				nppData._scintillaMainHandle : nppData._scintillaSecondHandle ;
}

//
// もうひとつキー入力を受けて、それに割り当てられた処理をする。
//
void SubShortCut ()
{

	//int		c = 'A';

	while( 1 ){

		/*
		if( _kbhit() != 0 ){
			c = _getch();
			char	b[100];
			sprintf( b, "SubShortCut : c = %d %c\n", c, c );
			::MessageBox( NULL, (LPCTSTR)b, TEXT( "SubShortCut" ), MB_OK );
			if( ( c == 'n' )||( c == 'N' ) ){ c = 'N'; break; }
		}
		*/

		MSG			msg;
		GetMessage( &msg, NULL, 0, 0 );

		if( msg.message != WM_CHAR ){
			TranslateMessage( &msg );
			DispatchMessage( &msg );
			continue;
		}

		switch( msg.wParam ){

		case 'E':
		case 'e':
			{
			// save and quit
		    ::SendMessage( nppData._nppHandle,
										NPPM_MENUCOMMAND, 0, IDM_FILE_SAVE );
		    ::SendMessage( nppData._nppHandle,
										NPPM_MENUCOMMAND, 0, IDM_FILE_EXIT );
			}
			return;

		case 'N':
		case 'n':
			{
			// open file
		    ::SendMessage( nppData._nppHandle,
										NPPM_MENUCOMMAND, 0, IDM_FILE_OPEN );
			}
			return;

		case 'O':
		case 'o':
			{
			// reopen file
		    ::SendMessage( nppData._nppHandle,
										NPPM_MENUCOMMAND, 0, IDM_FILE_RELOAD );
			}
			return;

		case 'S':
		case 's':
			{
			// save
		    ::SendMessage( nppData._nppHandle,
										NPPM_MENUCOMMAND, 0, IDM_FILE_SAVE );
			}
			return;

		case 'T':
		case 't':
			{
			// go to top of file
		    ::SendMessage( GetCurrentScintilla(), SCI_GOTOLINE, 0, 0 );
			}
			return;

		default:
			return;

		}// switch msg.wParam

	}// while 1

	/*

    // Open a new document
    ::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FILE_NEW);

    // Get the current scintilla
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    if (which == -1)
        return;
    HWND curScintilla = (which == 0)?nppData._scintillaMainHandle:nppData._scintillaSecondHandle;

    // Say hello now :
    // Scintilla control has no Unicode mode, so we use (char *) here
	char	b[100];
	sprintf( b, "SubShortCut : c = %d %c\n", c, c );
    ::SendMessage(curScintilla, SCI_SETTEXT, 0, (LPARAM)b);

	*/

}



