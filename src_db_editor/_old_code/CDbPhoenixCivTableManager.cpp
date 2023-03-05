//Class Header
#include "CDbPhoenixCivTableManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbPhoenixCivTableManager::CDbPhoenixCivTableManager()
{
}

//Destructor
CDbPhoenixCivTableManager::~CDbPhoenixCivTableManager()
{
	memfreesafe(this->pTables);
}

//Public methods
void CDbPhoenixCivTableManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
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

void CDbPhoenixCivTableManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbPhoenixCivTableManager::GetFileTitle() const
{
	return "dbphoenixcivtable";
}

void CDbPhoenixCivTableManager::Init()
{
}

void CDbPhoenixCivTableManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nTables);

	this->pTables = (SPhoenixCivTable *)malloc(this->nTables * sizeof(*this->pTables));
	refInput.ReadBytes(this->pTables, this->nTables * sizeof(*this->pTables));
}

void CDbPhoenixCivTableManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nTables);
	refOutput.WriteBytes(this->pTables, this->nTables * sizeof(*this->pTables));
}

CString CDbPhoenixCivTableManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SPhoenixCivTable &refTable = this->pTables[index];

	debugout(refTable.unknown1, sizeof(refTable.unknown1), index);
	
	APPENDCHARARRAY("Identifier", refTable.identifier, "", true);

	debugout(refTable.unknown2, sizeof(refTable.unknown2), index);

	APPENDUINT32("Name String Id", refTable.nameStringId, DbManager::Get().GetLanguageString(refTable.nameStringId).ToCString(), true);

	debugout(refTable.unknown4, sizeof(refTable.unknown4), index);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 2", refTable.unknownFloat2, "", true);
		APPENDFLOAT("Unknown Float 3", refTable.unknownFloat3, "", true);
		APPENDFLOAT("Unknown Float 4", refTable.unknownFloat4, "", true);
		APPENDUINT32("Unknown 3", refTable.unknown3, "", true);
		APPENDFLOAT("Unknown Float 1", refTable.unknownFloat1, "", true);
	}

	debugout(refTable.unknownRest, sizeof(refTable.unknownRest), index);
	
	return refTable.identifier;
}

bool CDbPhoenixCivTableManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbPhoenixCivTableManager::Uninit()
{
}