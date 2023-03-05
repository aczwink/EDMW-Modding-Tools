//Class Header
#include "CDbWeaponToHitManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbWeaponToHitManager::CDbWeaponToHitManager()
{
}

//Destructor
CDbWeaponToHitManager::~CDbWeaponToHitManager()
{
	memfreesafe(this->pTables);
}

//Public methods
void CDbWeaponToHitManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nTables; i++)
	{
		const CString &refCurrentName = this->pTables[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbWeaponToHitManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbWeaponToHitManager::GetFileTitle() const
{
	return "dbweapontohit";
}

void CDbWeaponToHitManager::Init()
{
}

void CDbWeaponToHitManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nTables);
	
	this->pTables = (SWeaponToHit *)malloc(this->nTables * sizeof(*this->pTables));
	refInput.ReadBytes(this->pTables, this->nTables * sizeof(*this->pTables));
}

void CDbWeaponToHitManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nTables);
	refOutput.WriteBytes(this->pTables, this->nTables * sizeof(*this->pTables));
}

CString CDbWeaponToHitManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SWeaponToHit &refTable = this->pTables[index];
	
	APPENDCHARARRAY("Identifier", refTable.identifier, "", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown 1", refTable.unknown1, "", true);
	}

	APPENDUINT32("Id", refTable.id, "", false);
	
	debugout(refTable.unknownRest, sizeof(refTable.unknownRest), index);
	
	return refTable.identifier;
}

bool CDbWeaponToHitManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbWeaponToHitManager::Uninit()
{
}