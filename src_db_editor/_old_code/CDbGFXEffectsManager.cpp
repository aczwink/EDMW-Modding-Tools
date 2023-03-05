//Class Header
#include "CDbGFXEffectsManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbGFXEffectsManager::CDbGFXEffectsManager()
{
}

//Destructor
CDbGFXEffectsManager::~CDbGFXEffectsManager()
{
	memfreesafe(this->pEffects);
}

//Public methods
void CDbGFXEffectsManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nEffects; i++)
	{
		const CString &refCurrentName = this->pEffects[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbGFXEffectsManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbGFXEffectsManager::GetFileTitle() const
{
	return "dbgfxeffects";
}

void CDbGFXEffectsManager::Init()
{
}

void CDbGFXEffectsManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nEffects);

	this->pEffects = (SGFXEffect *)malloc(this->nEffects * sizeof(*this->pEffects));
	refInput.ReadBytes(this->pEffects, this->nEffects * sizeof(*this->pEffects));
}

void CDbGFXEffectsManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nEffects);
	refOutput.WriteBytes(this->pEffects, this->nEffects * sizeof(*this->pEffects));
}

CString CDbGFXEffectsManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SGFXEffect &refEffect = this->pEffects[index];
	
	APPENDCHARARRAY("Identifier", refEffect.identifier, "", true);

	debugout(refEffect.unknown1, sizeof(refEffect.unknown1), index);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 1", refEffect.unknownFloat1, "", true);
		APPENDFLOAT("Unknown Float 2", refEffect.unknownFloat2, "", true);
		APPENDFLOAT("Unknown Float 9", refEffect.unknownFloat9, "", true);
	}

	debugout(refEffect.unknown2, sizeof(refEffect.unknown2), index);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 5", refEffect.unknownFloat5, "", true);
		APPENDFLOAT("Unknown Float 6", refEffect.unknownFloat6, "", true);
		APPENDFLOAT("Unknown Float 7", refEffect.unknownFloat7, "", true);
		APPENDFLOAT("Unknown Float 8", refEffect.unknownFloat8, "", true);
		APPENDFLOAT("Unknown Float 3", refEffect.unknownFloat3, "", true);
		APPENDFLOAT("Unknown Float 10", refEffect.unknownFloat10, "", true);
		APPENDFLOAT("Unknown Float 13", refEffect.unknownFloat13, "", true);
		APPENDFLOAT("Unknown Float 11", refEffect.unknownFloat11, "", true);
	}
	
	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 15", refEffect.unknownFloat15, "", true);
		APPENDFLOAT("Unknown Float 14", refEffect.unknownFloat14, "", true);
		APPENDFLOAT("Unknown Float 12", refEffect.unknownFloat12, "", true);
		APPENDFLOAT("Unknown Float 4", refEffect.unknownFloat4, "", true);

		APPENDBOOL("Unknown Bool 1", refEffect.unknownBool1, "", true);
		APPENDBOOL("Unknown Bool 2", refEffect.unknownBool2, "", true);
		APPENDBOOL("Unknown Bool 3", refEffect.unknownBool3, "", true);
		APPENDBOOL("Unknown Bool 4", refEffect.unknownBool4, "", true);
	}
	
	debugout(refEffect.unknownrest, sizeof(refEffect.unknownrest), index);

	return refEffect.identifier;
}

bool CDbGFXEffectsManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbGFXEffectsManager::Uninit()
{
}