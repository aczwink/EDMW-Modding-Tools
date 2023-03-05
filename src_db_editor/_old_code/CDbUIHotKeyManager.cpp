//Class Header
#include "CDbUIHotKeyManager.h"
//Local
#include "DbManager.h"

//Constructor
CDbUIHotKeyManager::CDbUIHotKeyManager()
{
}

//Destructor
CDbUIHotKeyManager::~CDbUIHotKeyManager()
{
	memfreesafe(this->pHotKeys);
}

//Public methods
void CDbUIHotKeyManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nHotKeys; i++)
	{
		const CString &refCurrentName = this->pHotKeys[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbUIHotKeyManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nHotKeys; i++)
	{
		const CString &refCurrentName = DbManager::Get().GetLanguageString(this->pHotKeys[i].stringId, true).ToCString();
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

CString CDbUIHotKeyManager::GetFileTitle() const
{
	return "dbuihotkey";
}

void CDbUIHotKeyManager::Init()
{
}

void CDbUIHotKeyManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nHotKeys);

	this->pHotKeys = (SHotKey *)malloc(this->nHotKeys * sizeof(*this->pHotKeys));
	refInput.ReadBytes(this->pHotKeys, this->nHotKeys * sizeof(*this->pHotKeys));
}

void CDbUIHotKeyManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nHotKeys);
	refOutput.WriteBytes(this->pHotKeys, this->nHotKeys * sizeof(*this->pHotKeys));
}

CString CDbUIHotKeyManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SHotKey &refHotKey = this->pHotKeys[index];

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown 1", refHotKey.unknown1, "", true);
		APPENDUINT32("Unknown 2", refHotKey.unknown2, "", true);
	}

	APPENDCHARARRAY("Identifier", refHotKey.identifier, "", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown 3", refHotKey.unknown3, "", true);
		APPENDUINT32("Unknown 4", refHotKey.unknown4, "", true);
		APPENDUINT32("Unknown 5", refHotKey.unknown5, "", true);
		APPENDUINT32("Unknown 6", refHotKey.unknown6, "", true);
	}

	APPENDUINT32("String id", refHotKey.stringId, DbManager::Get().GetLanguageString(refHotKey.stringId, true).ToCString(), true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown 8", refHotKey.unknown8, "", true);
		APPENDUINT32("Unknown 9", refHotKey.unknown9, "", true);
	}
	
	return refHotKey.identifier;
}

bool CDbUIHotKeyManager::SupportsFilterByDisplayString() const
{
	return true;
}

void CDbUIHotKeyManager::Uninit()
{
}