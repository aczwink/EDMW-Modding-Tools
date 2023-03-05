//Class Header
#include "CDbRandomMapManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbRandomMapManager::CDbRandomMapManager()
{
}

//Destructor
CDbRandomMapManager::~CDbRandomMapManager()
{
	memfreesafe(this->pTables);
}

//Public methods
void CDbRandomMapManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
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

void CDbRandomMapManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbRandomMapManager::GetFileTitle() const
{
	return "dbrandommap";
}

void CDbRandomMapManager::Init()
{
}

void CDbRandomMapManager::ReadInput(AInputStream &refInput)
{
	refInput.Skip(4); //hm...
	refInput.ReadUInt32(this->nTables);

	this->pTables = (SRandomMap *)malloc(this->nTables * sizeof(*this->pTables));
	refInput.ReadBytes(this->pTables, this->nTables * sizeof(*this->pTables));
}

void CDbRandomMapManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(10); //also hm...
	refOutput.WriteUInt32(this->nTables);
	refOutput.WriteBytes(this->pTables, this->nTables * sizeof(*this->pTables));
}

CString CDbRandomMapManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SRandomMap &refTable = this->pTables[index];

	debugout(refTable.unknown1, sizeof(refTable.unknown1), index);
	
	APPENDCHARARRAY("Identifier", refTable.identifier, "", true);
	
	debugout(refTable.unknownRest, sizeof(refTable.unknownRest), index);
	
	return refTable.identifier;
}

bool CDbRandomMapManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbRandomMapManager::Uninit()
{
}