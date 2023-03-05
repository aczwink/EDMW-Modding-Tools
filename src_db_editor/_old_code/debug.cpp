//Main Header
#include "debug.h"
//SJCLib
#include <SJCLib.h>
//Local
#include "DbManager.h"
#include "Definitions.h"
#include "Globals.h"
//Namespaces
using namespace SJCLib;

void debugout(uint32 *ptr, uint32 size, uint32 index)
{
	CString text, value;

	if(g_Settings.GetBoolValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_SHOWUNKNOWNVALUES))
	{
		for(uint32 i = 0; i < size/4; i++)
		{
			APPENDUINT32("Unknown Values (4 bytes)", ptr[i], "Offset" + CString(uint32((&ptr[i] - ptr)*4), NS_HEX, true, 2), true);
			SETUNKNOWN;
			/*if(DbManager::Get().GetLanguageString(ptr[i]).length())
			{
			wcout << "1" << DbManager::Get().GetLanguageString(ptr[i]) << endl;
			}
			if(DbManager::Get().GetLanguageString(ptr[i], true).length())
			{
			wcout << "2" << DbManager::Get().GetLanguageString(ptr[i], true) << endl;
			}*/
		}
	}
}