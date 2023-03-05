//Class Header
#include "CDbCalamityManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbCalamityManager::CDbCalamityManager()
{
}

//Destructor
CDbCalamityManager::~CDbCalamityManager()
{
	memfreesafe(this->pCalamities);
}

//Public methods
void CDbCalamityManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nCalamities; i++)
	{
		const CString &refCurrentName = this->pCalamities[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbCalamityManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbCalamityManager::GetFileTitle() const
{
	return "dbcalamity";
}

void CDbCalamityManager::Init()
{
}

void CDbCalamityManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nCalamities);

	this->pCalamities = (SCalamity *)malloc(this->nCalamities * sizeof(*this->pCalamities));
	refInput.ReadBytes(this->pCalamities, this->nCalamities * sizeof(*this->pCalamities));

	//finding out values
	/*for(uint32 i = 0; i < this->nAmbientSounds; i++)
	{
		if(this->pAmbientSounds[i].unknown1[1] != i)
		{
			stdOut << i << " " << this->pAmbientSounds[i].identifier << endl;
		}
	}*/
}

void CDbCalamityManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nCalamities);
	refOutput.WriteBytes(this->pCalamities, this->nCalamities * sizeof(*this->pCalamities));
}

CString CDbCalamityManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SCalamity &refCalamity = this->pCalamities[index];
	
	APPENDCHARARRAY("Identifier", refCalamity.identifier, "", true);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 1", refCalamity.unknownFloat1, "", true);
		APPENDFLOAT("Unknown Float 2", refCalamity.unknownFloat2, "", true);
		APPENDFLOAT("Unknown Float 3", refCalamity.unknownFloat3, "", true);
		APPENDFLOAT("Unknown Float 4", refCalamity.unknownFloat4, "", true);
		APPENDFLOAT("Unknown Float 5", refCalamity.unknownFloat5, "", true);
		APPENDFLOAT("Unknown Float 6", refCalamity.unknownFloat6, "", true);
	}

	debugout(refCalamity.unknown1, sizeof(refCalamity.unknown1), index);
	
	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 7", refCalamity.unknownFloat7, "", true);
	}

	debugout(refCalamity.unknown2, sizeof(refCalamity.unknown2), index);

	if(showUnknownValues)
	{
		APPENDBOOL("Unknown Bool 1", refCalamity.unknownBool1, "", true);
		APPENDBOOL("Unknown Bool 2", refCalamity.unknownBool2, "", true);
		APPENDBOOL("Unknown Bool 3", refCalamity.unknownBool3, "", true);
		APPENDBOOL("Unknown Bool 4", refCalamity.unknownBool4, "", true);
	}
	
	debugout(refCalamity.unknownrest, sizeof(refCalamity.unknownrest), index);

	return refCalamity.identifier;
}

bool CDbCalamityManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbCalamityManager::Uninit()
{
}