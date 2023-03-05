//Class Header
#include "CDbCivSpecAIManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbCivSpecAIManager::CDbCivSpecAIManager()
{
}

//Destructor
CDbCivSpecAIManager::~CDbCivSpecAIManager()
{
	memfreesafe(this->pCivSpecAIs);
}

//Public methods
void CDbCivSpecAIManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nCivSpecAIs; i++)
	{
		const CString &refCurrentName = CString(i);
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbCivSpecAIManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbCivSpecAIManager::GetFileTitle() const
{
	return "dbcivspecai";
}

void CDbCivSpecAIManager::Init()
{
}

void CDbCivSpecAIManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nCivSpecAIs);

	this->pCivSpecAIs = (SCivSpecAI *)malloc(this->nCivSpecAIs * sizeof(*this->pCivSpecAIs));
	refInput.ReadBytes(this->pCivSpecAIs, this->nCivSpecAIs * sizeof(*this->pCivSpecAIs));

	//finding out values
	/*for(uint32 i = 0; i < this->nAmbientSounds; i++)
	{
		if(this->pAmbientSounds[i].unknown1[1] != i)
		{
			stdOut << i << " " << this->pAmbientSounds[i].identifier << endl;
		}
	}*/
}

void CDbCivSpecAIManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nCivSpecAIs);
	refOutput.WriteBytes(this->pCivSpecAIs, this->nCivSpecAIs * sizeof(*this->pCivSpecAIs));
}

CString CDbCivSpecAIManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SCivSpecAI &refCivSpecAI = this->pCivSpecAIs[index];

	debugout(refCivSpecAI.unknown1, sizeof(refCivSpecAI.unknown1), index);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 1", refCivSpecAI.unknownFloat1, "", true);
		APPENDFLOAT("Unknown Float 2", refCivSpecAI.unknownFloat2, "", true);
		APPENDFLOAT("Unknown Float 3", refCivSpecAI.unknownFloat3, "", true);
		APPENDFLOAT("Unknown Float 4", refCivSpecAI.unknownFloat4, "", true);
		APPENDFLOAT("Unknown Float 5", refCivSpecAI.unknownFloat5, "", true);
		APPENDFLOAT("Unknown Float 6", refCivSpecAI.unknownFloat6, "", true);
		APPENDFLOAT("Unknown Float 7", refCivSpecAI.unknownFloat7, "", true);
		APPENDFLOAT("Unknown Float 8", refCivSpecAI.unknownFloat8, "", true);
		APPENDFLOAT("Unknown Float 9", refCivSpecAI.unknownFloat9, "", true);
		APPENDFLOAT("Unknown Float 10", refCivSpecAI.unknownFloat10, "", true);
		APPENDFLOAT("Unknown Float 11", refCivSpecAI.unknownFloat11, "", true);
		APPENDFLOAT("Unknown Float 12", refCivSpecAI.unknownFloat12, "", true);
		APPENDFLOAT("Unknown Float 13", refCivSpecAI.unknownFloat13, "", true);
		APPENDFLOAT("Unknown Float 14", refCivSpecAI.unknownFloat14, "", true);
		APPENDFLOAT("Unknown Float 15", refCivSpecAI.unknownFloat15, "", true);
		APPENDFLOAT("Unknown Float 16", refCivSpecAI.unknownFloat16, "", true);
	}
	
	debugout(refCivSpecAI.unknownrest, sizeof(refCivSpecAI.unknownrest), index);

	return CString(index);
}

bool CDbCivSpecAIManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbCivSpecAIManager::Uninit()
{
}