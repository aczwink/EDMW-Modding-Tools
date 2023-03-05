//Class Header
#include "CDbAmbientSoundsManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbAmbientSoundsManager::CDbAmbientSoundsManager()
{
}

//Destructor
CDbAmbientSoundsManager::~CDbAmbientSoundsManager()
{
	memfreesafe(this->pAmbientSounds);
}

//Public methods
void CDbAmbientSoundsManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nAmbientSounds; i++)
	{
		const CString &refCurrentName = this->pAmbientSounds[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbAmbientSoundsManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbAmbientSoundsManager::GetFileTitle() const
{
	return "dbambientsounds";
}

void CDbAmbientSoundsManager::Init()
{
}

void CDbAmbientSoundsManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nAmbientSounds);

	this->pAmbientSounds = (SAmbientSounds *)malloc(this->nAmbientSounds * sizeof(*this->pAmbientSounds));
	refInput.ReadBytes(this->pAmbientSounds, this->nAmbientSounds * sizeof(*this->pAmbientSounds));

	//finding out values
	/*for(uint32 i = 0; i < this->nAmbientSounds; i++)
	{
		if(this->pAmbientSounds[i].unknown1[1] != i)
		{
			stdOut << i << " " << this->pAmbientSounds[i].identifier << endl;
		}
	}*/
}

void CDbAmbientSoundsManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nAmbientSounds);
	refOutput.WriteBytes(this->pAmbientSounds, this->nAmbientSounds * sizeof(*this->pAmbientSounds));
}

CString CDbAmbientSoundsManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SAmbientSounds &refAmbientSounds = this->pAmbientSounds[index];
	
	APPENDCHARARRAY("Identifier", refAmbientSounds.identifier, "", true);

	debugout(refAmbientSounds.unknown1, sizeof(refAmbientSounds.unknown1), index);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 1", refAmbientSounds.unknownFloat1, "", true);
		APPENDFLOAT("Unknown Float 2", refAmbientSounds.unknownFloat2, "", true);
		APPENDFLOAT("Unknown Float 3", refAmbientSounds.unknownFloat3, "", true);
		APPENDFLOAT("Unknown Float 4", refAmbientSounds.unknownFloat4, "", true);
		APPENDFLOAT("Unknown Float 5", refAmbientSounds.unknownFloat5, "", true);
	}

	debugout(refAmbientSounds.unknownrest, sizeof(refAmbientSounds.unknownrest), index);

	return refAmbientSounds.identifier;
}

bool CDbAmbientSoundsManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbAmbientSoundsManager::Uninit()
{
}