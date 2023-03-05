//Class Header
#include "CDbSoundsManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbSoundsManager::CDbSoundsManager()
{
}

//Destructor
CDbSoundsManager::~CDbSoundsManager()
{
	HeapDeleteArraySafe(this->pSounds);
}

//Public methods
void CDbSoundsManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nSounds; i++)
	{
		const CString &refCurrentName = this->pSounds[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbSoundsManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbSoundsManager::GetFileTitle() const
{
	return "dbsounds";
}

void CDbSoundsManager::Init()
{
}

void CDbSoundsManager::ReadInput(AInputStream &refInput)
{
	uint32 length;
	
	refInput.ReadUInt32(this->nSounds);
	
	this->pSounds = new CSound[this->nSounds];

	for(uint32 i = 0; i < this->nSounds; i++)
	{
		refInput.ReadUInt32(length);
		this->pSounds[i].fileName = refInput.ReadString(length);

		refInput.ReadBytes(this->pSounds[i].identifier, sizeof(this->pSounds[i].identifier));
		refInput.ReadBytes(this->pSounds[i].identifier2, sizeof(this->pSounds[i].identifier2));
		refInput.ReadBytes(this->pSounds[i].unknownRest, sizeof(this->pSounds[i].unknownRest));
	}
}

void CDbSoundsManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nSounds);
	
	for(uint32 i = 0; i < this->nSounds; i++)
	{
		refOutput.WriteUInt32(this->pSounds[i].fileName.GetLength());
		refOutput.WriteString(this->pSounds[i].fileName);

		refOutput.WriteBytes(this->pSounds[i].identifier, sizeof(this->pSounds[i].identifier));
		refOutput.WriteBytes(this->pSounds[i].identifier2, sizeof(this->pSounds[i].identifier2));
		refOutput.WriteBytes(this->pSounds[i].unknownRest, sizeof(this->pSounds[i].unknownRest));
	}
}

CString CDbSoundsManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	CSound &refSound = this->pSounds[index];
	
	APPENDSTRING("File name", refSound.fileName, "", true);
	APPENDCHARARRAY("Identifier", refSound.identifier, "", true);
	APPENDCHARARRAY("Identifier 2", refSound.identifier2, "", true);
	
	debugout(refSound.unknownRest, sizeof(refSound.unknownRest), index);
	
	return refSound.identifier;
}

bool CDbSoundsManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbSoundsManager::Uninit()
{
}