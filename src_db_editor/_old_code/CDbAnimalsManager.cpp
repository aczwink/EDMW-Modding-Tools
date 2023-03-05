//Class Header
#include "CDbAnimalsManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbAnimalsManager::CDbAnimalsManager()
{
}

//Destructor
CDbAnimalsManager::~CDbAnimalsManager()
{
	memfreesafe(this->pAnimals);
}

//Public methods
void CDbAnimalsManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nAnimals; i++)
	{
		const CString &refCurrentName = this->pAnimals[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbAnimalsManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbAnimalsManager::GetFileTitle() const
{
	return "dbanimals";
}

void CDbAnimalsManager::Init()
{
}

void CDbAnimalsManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nAnimals);

	this->pAnimals = (SAnimal *)malloc(this->nAnimals * sizeof(*this->pAnimals));
	refInput.ReadBytes(this->pAnimals, this->nAnimals * sizeof(*this->pAnimals));

	//finding out values
	/*for(uint32 i = 0; i < this->nAmbientSounds; i++)
	{
		if(this->pAmbientSounds[i].unknown1[1] != i)
		{
			stdOut << i << " " << this->pAmbientSounds[i].identifier << endl;
		}
	}*/
}

void CDbAnimalsManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nAnimals);
	refOutput.WriteBytes(this->pAnimals, this->nAnimals * sizeof(*this->pAnimals));
}

CString CDbAnimalsManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SAnimal &refAnimal = this->pAnimals[index];
	
	APPENDCHARARRAY("Identifier", refAnimal.identifier, "", true);

	debugout(refAnimal.unknown1, sizeof(refAnimal.unknown1), index);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 1", refAnimal.unknownFloat1, "", true);
	}

	debugout(refAnimal.unknown2, sizeof(refAnimal.unknown2), index);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 2", refAnimal.unknownFloat2, "", true);
		APPENDFLOAT("Unknown Float 3", refAnimal.unknownFloat3, "", true);
	}

	debugout(refAnimal.unknown3, sizeof(refAnimal.unknown3), index);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 4", refAnimal.unknownFloat4, "", true);
	}
	
	debugout(refAnimal.unknownrest, sizeof(refAnimal.unknownrest), index);

	return refAnimal.identifier;
}

bool CDbAnimalsManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbAnimalsManager::Uninit()
{
}