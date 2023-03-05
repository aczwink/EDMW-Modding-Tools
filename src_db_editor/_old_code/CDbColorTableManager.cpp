//Class Header
#include "CDbColorTableManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbColorTableManager::CDbColorTableManager()
{
}

//Destructor
CDbColorTableManager::~CDbColorTableManager()
{
	memfreesafe(this->pColorTables);
}

//Public methods
void CDbColorTableManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nColorTables; i++)
	{
		const CString &refCurrentName = this->pColorTables[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbColorTableManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbColorTableManager::GetFileTitle() const
{
	return "dbcolortable";
}

void CDbColorTableManager::Init()
{
}

void CDbColorTableManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nColorTables);

	this->pColorTables = (SColorTable *)malloc(this->nColorTables * sizeof(*this->pColorTables));
	refInput.ReadBytes(this->pColorTables, this->nColorTables * sizeof(*this->pColorTables));

	//finding out values
	/*for(uint32 i = 0; i < this->nAmbientSounds; i++)
	{
		if(this->pAmbientSounds[i].unknown1[1] != i)
		{
			stdOut << i << " " << this->pAmbientSounds[i].identifier << endl;
		}
	}*/
}

void CDbColorTableManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nColorTables);
	refOutput.WriteBytes(this->pColorTables, this->nColorTables * sizeof(*this->pColorTables));
}

CString CDbColorTableManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SColorTable &refColorTable = this->pColorTables[index];

	debugout(refColorTable.unknown1, sizeof(refColorTable.unknown1), index);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 7", refColorTable.unknownFloat7, "", true);
		APPENDFLOAT("Unknown Float 8", refColorTable.unknownFloat8, "", true);
		APPENDFLOAT("Unknown Float 9", refColorTable.unknownFloat9, "", true);
		APPENDFLOAT("Unknown Float 1", refColorTable.unknownFloat1, "", true);
		APPENDFLOAT("Unknown Float 2", refColorTable.unknownFloat2, "", true);
		APPENDFLOAT("Unknown Float 3", refColorTable.unknownFloat3, "", true);
		APPENDFLOAT("Unknown Float 4", refColorTable.unknownFloat4, "", true);
		APPENDFLOAT("Unknown Float 5", refColorTable.unknownFloat5, "", true);
		APPENDFLOAT("Unknown Float 6", refColorTable.unknownFloat6, "", true);
	}
	
	debugout(refColorTable.unknownrest, sizeof(refColorTable.unknownrest), index);
	
	return refColorTable.identifier;
}

bool CDbColorTableManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbColorTableManager::Uninit()
{
}