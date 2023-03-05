//Class Header
#include "CDbPremadecivsManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbPremadecivsManager::CDbPremadecivsManager()
{
}

//Destructor
CDbPremadecivsManager::~CDbPremadecivsManager()
{
	memfreesafe(this->pTables);
}

//Public methods
void CDbPremadecivsManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
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

void CDbPremadecivsManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbPremadecivsManager::GetFileTitle() const
{
	return "dbpremadecivs";
}

void CDbPremadecivsManager::Init()
{
}

void CDbPremadecivsManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nTables);

	this->pTables = (SPremadeciv *)malloc(this->nTables * sizeof(*this->pTables));
	refInput.ReadBytes(this->pTables, this->nTables * sizeof(*this->pTables));
}

void CDbPremadecivsManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nTables);
	refOutput.WriteBytes(this->pTables, this->nTables * sizeof(*this->pTables));
}

CString CDbPremadecivsManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SPremadeciv &refTable = this->pTables[index];

	debugout(refTable.unknown1, sizeof(refTable.unknown1), index);
	
	APPENDCHARARRAY("Identifier", refTable.identifier, "", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown 2", refTable.unknown2, "", true);
		SETUNKNOWN;
	}

	APPENDUINT32("Name String Id", refTable.nameStringId, DbManager::Get().GetLanguageString(refTable.nameStringId).ToCString(), true);
	APPENDUINT32("Epoch-range String Id", refTable.epochRangeStringId, DbManager::Get().GetLanguageString(refTable.epochRangeStringId).ToCString(), true);
	APPENDUINT32("Civilization tech Id", refTable.civilizationTechId, "", true);
	
	return refTable.identifier;
}

bool CDbPremadecivsManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbPremadecivsManager::Uninit()
{
}