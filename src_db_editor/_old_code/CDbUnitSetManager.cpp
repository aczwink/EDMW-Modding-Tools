//Class Header
#include "CDbUnitSetManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbUnitSetManager::CDbUnitSetManager()
{
}

//Destructor
CDbUnitSetManager::~CDbUnitSetManager()
{
	memfreesafe(this->pUnitSets);
}

//Public methods
void CDbUnitSetManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nUnitSets; i++)
	{
		const CString &refCurrentName = this->pUnitSets[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbUnitSetManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbUnitSetManager::GetFileTitle() const
{
	return "dbunitset";
}

void CDbUnitSetManager::Init()
{
}

void CDbUnitSetManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nUnitSets);

	this->pUnitSets = (SUnitSet *)malloc(this->nUnitSets * sizeof(*this->pUnitSets));
	refInput.ReadBytes(this->pUnitSets, this->nUnitSets * sizeof(*this->pUnitSets));
}

void CDbUnitSetManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nUnitSets);
	refOutput.WriteBytes(this->pUnitSets, this->nUnitSets * sizeof(*this->pUnitSets));
}

CString CDbUnitSetManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SUnitSet &refUnitSet = this->pUnitSets[index];
	
	APPENDCHARARRAY("Identifier", refUnitSet.identifier, "", true);

	debugout(refUnitSet.unknownrest, sizeof(refUnitSet.unknownrest), index);

	return refUnitSet.identifier;
}

bool CDbUnitSetManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbUnitSetManager::Uninit()
{
}