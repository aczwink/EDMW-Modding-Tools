//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbAIUnitTargeting::CDbAIUnitTargeting()
{
}

//Destructor
CDbAIUnitTargeting::~CDbAIUnitTargeting()
{
	memfreesafe(this->pAIUnitTargetings);
}

//Public methods
void CDbAIUnitTargeting::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nAIUnitTargetings; i++)
	{
		const CString &refCurrentName = this->pAIUnitTargetings[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbAIUnitTargeting::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
}

void CDbAIUnitTargeting::Init()
{
}

void CDbAIUnitTargeting::ReadInput(AInputStream &refInput)
{
	uint32 size;
	
	refInput.ReadUInt32(this->nAIUnitTargetings);
	
	size = this->nAIUnitTargetings * sizeof(*this->pAIUnitTargetings);
	this->pAIUnitTargetings = (SAIUnitTargeting *)malloc(size);
	refInput.ReadBytes(this->pAIUnitTargetings, size);
}

void CDbAIUnitTargeting::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nAIUnitTargetings);
	refOutput.WriteBytes(this->pAIUnitTargetings, this->nAIUnitTargetings * sizeof(*this->pAIUnitTargetings));
}

CString CDbAIUnitTargeting::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SAIUnitTargeting &refAIUnitTargeting = this->pAIUnitTargetings[index];

	APPENDCHARARRAY("Identifier", refAIUnitTargeting.identifier, "", false);

	debugout((uint32 *)refAIUnitTargeting.unknownRest, sizeof(refAIUnitTargeting.unknownRest), index);

	return refAIUnitTargeting.identifier;
}

bool CDbAIUnitTargeting::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbAIUnitTargeting::Uninit()
{
}