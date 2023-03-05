//Class Header
#include "CDbAreaEffectManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbAreaEffectManager::CDbAreaEffectManager()
{
}

//Destructor
CDbAreaEffectManager::~CDbAreaEffectManager()
{
	memfreesafe(this->pAreaEffects);
}

//Public methods
void CDbAreaEffectManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nAreaEffects; i++)
	{
		const CString &refCurrentName = this->pAreaEffects[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbAreaEffectManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbAreaEffectManager::GetFileTitle() const
{
	return "dbareaeffect";
}

void CDbAreaEffectManager::Init()
{
}

void CDbAreaEffectManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nAreaEffects);

	this->pAreaEffects = (SAreaEffect *)malloc(this->nAreaEffects * sizeof(*this->pAreaEffects));
	refInput.ReadBytes(this->pAreaEffects, this->nAreaEffects * sizeof(*this->pAreaEffects));

	//finding out values
	/*for(uint32 i = 0; i < this->nAmbientSounds; i++)
	{
		if(this->pAmbientSounds[i].unknown1[1] != i)
		{
			stdOut << i << " " << this->pAmbientSounds[i].identifier << endl;
		}
	}*/
}

void CDbAreaEffectManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nAreaEffects);
	refOutput.WriteBytes(this->pAreaEffects, this->nAreaEffects * sizeof(*this->pAreaEffects));
}

CString CDbAreaEffectManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SAreaEffect &refAreaEffect = this->pAreaEffects[index];
	
	APPENDCHARARRAY("Identifier", refAreaEffect.identifier, "", true);

	debugout(refAreaEffect.unknown1, sizeof(refAreaEffect.unknown1), index);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 1", refAreaEffect.unknownFloat1, "", true);
		APPENDUINT32("Unknown 2", refAreaEffect.unknown2, "", true);
		APPENDFLOAT("Unknown Float 2", refAreaEffect.unknownFloat2, "", true);
		APPENDFLOAT("Unknown Float 3", refAreaEffect.unknownFloat3, "", true);
		APPENDFLOAT("Unknown Float 4", refAreaEffect.unknownFloat4, "", true);
		APPENDFLOAT("Unknown Float 5", refAreaEffect.unknownFloat5, "", true);
	}
	
	debugout(refAreaEffect.unknownrest, sizeof(refAreaEffect.unknownrest), index);

	return refAreaEffect.identifier;
}

bool CDbAreaEffectManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbAreaEffectManager::Uninit()
{
}