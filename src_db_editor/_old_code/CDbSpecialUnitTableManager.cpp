//Class Header
#include "CDbSpecialUnitTableManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbSpecialUnitTableManager::CDbSpecialUnitTableManager()
{
}

//Destructor
CDbSpecialUnitTableManager::~CDbSpecialUnitTableManager()
{
	memfreesafe(this->pTables);
}

//Public methods
void CDbSpecialUnitTableManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
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

void CDbSpecialUnitTableManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbSpecialUnitTableManager::GetFileTitle() const
{
	return "dbspecialunittable";
}

void CDbSpecialUnitTableManager::Init()
{
}

void CDbSpecialUnitTableManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nTables);
	
	this->pTables = (SSpecialUnitTable *)malloc(this->nTables * sizeof(*this->pTables));
	refInput.ReadBytes(this->pTables, this->nTables * sizeof(*this->pTables));
}

void CDbSpecialUnitTableManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nTables);
	refOutput.WriteBytes(this->pTables, this->nTables * sizeof(*this->pTables));
}

CString CDbSpecialUnitTableManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SSpecialUnitTable &refTable = this->pTables[index];
	
	APPENDCHARARRAY("Identifier", refTable.identifier, "", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown 1", refTable.unknown1, "", true);
		APPENDUINT32("Unknown 2", refTable.unknown2, "", true);
		APPENDFLOAT("Unknown 3", refTable.unknown3, "", true);
		APPENDFLOAT("Unknown 4", refTable.unknown4, "", true);
	}
	
	debugout(refTable.unknownRest, sizeof(refTable.unknownRest), index);
	
	return refTable.identifier;
}

bool CDbSpecialUnitTableManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbSpecialUnitTableManager::Uninit()
{
}