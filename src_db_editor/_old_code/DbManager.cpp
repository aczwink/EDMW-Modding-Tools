#include "CDbAmbientSoundsManager.h"
#include "CDbAnimalsManager.h"
#include "CDbAreaEffectManager.h"
#include "CDbButtonsManager.h"
#include "CDbCalamityManager.h"
#include "CDbCivSpecAIManager.h"
#include "CDbColorTableManager.h"
#include "CDbFamilyManager.h"
#include "CDbGFXEffectsManager.h"
#include "CDbGraphicsManager.h"
#include "CDbMousePointerManager.h"
#include "CDbMusicManager.h"
#include "CDbObjectsManager.h"
#include "CDbPhoenixCivTableManager.h"
#include "CDbPremadecivsManager.h"
#include "CDbRandomMapManager.h"
#include "CDbSoundsManager.h"
#include "CDbSpecialUnitTableManager.h"
#include "CDbTechtreeManager.h"
#include "CDbUIControlsManager.h"
#include "CDbUIFontsManager.h"
#include "CDbUIHotKeyManager.h"
#include "CDbUnitSetManager.h"
#include "CDbWeaponToHitManager.h"
#include "Definitions.h"
#include "globals.h"

//Constructor
DbManager::DbManager()
{
	this->dbType = DBFILETYPE_NONE;
	this->pLangdll = NULL;
	this->pLang2dll = NULL;
	
	this->dbFileManagers.Insert(DBFILETYPE_AMBIENTSOUNDS, new CDbAmbientSoundsManager);
	this->dbFileManagers.Insert(DBFILETYPE_ANIMALS, new CDbAnimalsManager);
	this->dbFileManagers.Insert(DBFILETYPE_AREAEFFECTS, new CDbAreaEffectManager);
	this->dbFileManagers.Insert(DBFILETYPE_BUTTONS, new CDbButtonsManager);
	this->dbFileManagers.Insert(DBFILETYPE_CALAMITIES, new CDbCalamityManager);
	this->dbFileManagers.Insert(DBFILETYPE_CIVSPECAI, new CDbCivSpecAIManager);
	this->dbFileManagers.Insert(DBFILETYPE_COLORTABLE, new CDbColorTableManager);
	this->dbFileManagers.Insert(DBFILETYPE_FAMILY, new CDbFamilyManager);
	this->dbFileManagers.Insert(DBFILETYPE_GFXEFFECTS, new CDbGFXEffectsManager);
	this->dbFileManagers.Insert(DBFILETYPE_GRAPHICS, new CDbGraphicsManager);
	this->dbFileManagers.Insert(DBFILETYPE_MOUSEPOINTERS, new CDbMousePointerManager);
	this->dbFileManagers.Insert(DBFILETYPE_MUSIC, new CDbMusicManager);
	this->dbFileManagers.Insert(DBFILETYPE_OBJECTS, new CDbObjectsManager);
	this->dbFileManagers.Insert(DBFILETYPE_PHOENIXCIVTABLES, new CDbPhoenixCivTableManager);
	this->dbFileManagers.Insert(DBFILETYPE_PREMADECIVS, new CDbPremadecivsManager);
	this->dbFileManagers.Insert(DBFILETYPE_RANDOMMAP, new CDbRandomMapManager);
	this->dbFileManagers.Insert(DBFILETYPE_SPECIALUNITTABLE, new CDbSpecialUnitTableManager);
	this->dbFileManagers.Insert(DBFILETYPE_SOUNDS, new CDbSoundsManager);
	this->dbFileManagers.Insert(DBFILETYPE_TECHTREES, new CDbTechtreeManager);
	this->dbFileManagers.Insert(DBFILETYPE_UICONTROLS, new CDbUIControlsManager);
	this->dbFileManagers.Insert(DBFILETYPE_UIFONTS, new CDbUIFontsManager);
	this->dbFileManagers.Insert(DBFILETYPE_UIHOTKEYS, new CDbUIHotKeyManager);
	this->dbFileManagers.Insert(DBFILETYPE_UNITSET, new CDbUnitSetManager);
	this->dbFileManagers.Insert(DBFILETYPE_WEAPONTOHIT, new CDbWeaponToHitManager);
}

//Destructor
DbManager::~DbManager()
{
	HeapDeleteSafe(this->pLangdll);
	HeapDeleteSafe(this->pLang2dll);
}

//Public Functions
void DbManager::Filter(const CString &refText)
{
	IDbManager *pMgr;

	g_MainWindow.itemList.Clear();

	if(this->dbType != DBFILETYPE_NONE)
	{
		pMgr = this->dbFileManagers[this->dbType];

		if(this->byIdentifier)
			pMgr->Filter(refText.ToLowercase(), g_MainWindow.itemList);
		else
			pMgr->FilterByDisplayName(refText.ToLowercase(), g_MainWindow.itemList);
	}
	g_MainWindow.itemList.Sort();
}

void DbManager::FilterBy(bool byIdentifier)
{
	this->byIdentifier = byIdentifier;
	this->Filter(g_MainWindow.editFilter.GetText());
}

void DbManager::Init()
{
	uint32 unreadBytes;

	foreach(it, this->dbFileManagers)
	{
		CFileInputStream file;
		
		if(!file.Open(g_Settings.GetStringValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_EDMWPATH) + "\\Data\\db\\" + it.GetValue()->GetFileTitle() + FILE_DB_EXT))
		{
			g_MainWindow.MessageBox(L"File couldn't be opened. Please make sure that the directory to EDMW is correct and that patch 1.3 is installed.", L"Critical Error", MB_ICONERROR);
		}
		
		it.GetValue()->ReadInput(file);
		
		unreadBytes = file.GetRemainingBytes();
		if(unreadBytes)
		{
			g_MainWindow.MessageBox(CString(unreadBytes) + L" bytes were not read from file: " + it.GetValue()->GetFileTitle() + (CWString)FILE_DB_EXT + L".", L"Warning", MB_ICONWARNING);
		}
	}
}

void DbManager::InsertTableItem(CString description, void *pBuffer, uint32 bufferSize, EItemDataType type, CString assoc, uint32 itemListIndex, bool isEditable)
{
	uint32 index;

	index = g_MainWindow.table.InsertItem();
	this->lastIdx = index;
	g_MainWindow.table.SetItemText(description, index, 0);
	g_MainWindow.table.SetItemText(assoc, index, 2);

	switch(type)
	{
	case ITEMDATATYPE_BOOL:
		{
			CString text;
			
			if(*(bool *)pBuffer)
				text = "true";
			else
				text = "false";
			
			g_MainWindow.table.SetItemText(text, index, 1);
		}
		break;
	case ITEMDATATYPE_CHARARRAY:
		g_MainWindow.table.SetItemText(CString((char *)pBuffer, bufferSize), index, 1);
		break;
	case ITEMDATATYPE_INT32:
		{
			g_MainWindow.table.SetItemText(CString(*(int32 *)pBuffer), index, 1);
		}
		break;
	case ITEMDATATYPE_STRING:
		{
			CString *pStr;

			pStr = (CString *)pBuffer;
			g_MainWindow.table.SetItemText(*pStr, index, 1);
		}
		break;
	case ITEMDATATYPE_UINT32:
	case ITEMDATATYPE_OBJECT_RESOURCETYPE:
		g_MainWindow.table.SetItemText(CString(*(uint32 *)pBuffer), index, 1);
		break;
	case ITEMDATATYPE_FLOAT:
		g_MainWindow.table.SetItemText(CString(*(float *)pBuffer), index, 1);
		break;
	}

	this->data[index].pBuffer = pBuffer;
	this->data[index].bufferSize = bufferSize;
	this->data[index].type = type;
	this->data[index].itemIndex = itemListIndex;
	this->data[index].isEditable = isEditable;
	this->data[index].state = 0;

	g_MainWindow.table.SetItemData(index, index);
}

void DbManager::Save()
{
	foreach(it, this->dbFileManagers)
	{
		CFileOutputStream file;

		const CString &refFilePath = g_Settings.GetStringValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_EDMWPATH) + "\\Data\\db\\" + it.GetValue()->GetFileTitle() + FILE_DB_EXT;
		
		//Create a backup of the original but only if it not exists
		CopyFile(refFilePath.GetC_Str(), (g_Settings.GetStringValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_EDMWPATH) + "\\Data\\db\\" + it.GetValue()->GetFileTitle() + ".bkp").GetC_Str(), TRUE);

		if(file.Open(refFilePath))
		{
			it.GetValue()->Save(file);
		}
		else
		{
			g_MainWindow.MessageBox(L"File '" + refFilePath + L"' couldn't be saved.", L"Critical Error", MB_ICONERROR);
		}
	}
	
	g_MainWindow.buttonSave.Enable(false);
}

void DbManager::SetFile(uint64 itemData)
{
	IDbManager *pMgr;

	if(this->dbType != DBFILETYPE_NONE)
	{
		pMgr = this->dbFileManagers[this->dbType];
		pMgr->Uninit();
	}

	this->dbType = (EDbFileType)itemData;	
	pMgr = this->dbFileManagers[this->dbType];
	
	g_MainWindow.comboBoxFilterBy.Clear();
	g_MainWindow.comboBoxFilterBy.Enable();
	g_MainWindow.comboBoxFilterBy.AddItem("Identifier");
	if(pMgr->SupportsFilterByDisplayString())
		g_MainWindow.comboBoxFilterBy.AddItem("Displayed-String");
	g_MainWindow.comboBoxFilterBy.Select(0);
	this->byIdentifier = true;
	
	pMgr->Init();
	
	g_MainWindow.editFilter.SetText(CString());
	g_MainWindow.table.Clear();
}

void DbManager::SetItem(uint32 index)
{
	bool showUnknownValues, showConstValues;
	IDbManager *pMgr;

	showUnknownValues = g_Settings.GetBoolValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_SHOWUNKNOWNVALUES);
	showConstValues = g_Settings.GetBoolValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_SHOWCONSTANTVALUES);
	
	if(this->dbType != DBFILETYPE_NONE)
	{
		this->data.Release();
		
		pMgr = this->dbFileManagers[this->dbType];
		
		g_MainWindow.table.Clear();
		
		const CString &refTitle = pMgr->SetItem(index, showUnknownValues, showConstValues);
		
		g_MainWindow.title.SetText(refTitle);
		g_MainWindow.table.Show(SW_SHOW);
	}
}