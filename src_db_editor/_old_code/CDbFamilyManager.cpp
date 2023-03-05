//Class Header
#include "CDbFamilyManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbFamilyManager::CDbFamilyManager()
{
}

//Destructor
CDbFamilyManager::~CDbFamilyManager()
{
	memfreesafe(this->pFamilies);
}

//Public methods
void CDbFamilyManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nFamilies; i++)
	{
		const CString &refCurrentName = this->pFamilies[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbFamilyManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbFamilyManager::GetFileTitle() const
{
	return "dbfamily";
}

void CDbFamilyManager::Init()
{
}

void CDbFamilyManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nFamilies);

	this->pFamilies = (SFamily *)malloc(this->nFamilies * sizeof(*this->pFamilies));
	refInput.ReadBytes(this->pFamilies, this->nFamilies * sizeof(*this->pFamilies));
}

void CDbFamilyManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nFamilies);
	refOutput.WriteBytes(this->pFamilies, this->nFamilies * sizeof(*this->pFamilies));
}

CString CDbFamilyManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SFamily &refFamily = this->pFamilies[index];
	
	APPENDCHARARRAY("Identifier", refFamily.identifier, "", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown 1", refFamily.unknown1, "", true);
	}

	APPENDUINT32("Id", refFamily.id, "", false);

	debugout(refFamily.unknownrest, sizeof(refFamily.unknownrest), index);

	return refFamily.identifier;
}

bool CDbFamilyManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbFamilyManager::Uninit()
{
}