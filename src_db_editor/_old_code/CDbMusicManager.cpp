//Class Header
#include "CDbMusicManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbMusicManager::CDbMusicManager()
{
}

//Destructor
CDbMusicManager::~CDbMusicManager()
{
	memfreesafe(this->pMusic);
}

//Public methods
void CDbMusicManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nMusic; i++)
	{
		const CString &refCurrentName = this->pMusic[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbMusicManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbMusicManager::GetFileTitle() const
{
	return "dbmusic";
}

void CDbMusicManager::Init()
{
}

void CDbMusicManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nMusic);

	this->pMusic = (SMusic *)malloc(this->nMusic * sizeof(*this->pMusic));
	refInput.ReadBytes(this->pMusic, this->nMusic * sizeof(*this->pMusic));
}

void CDbMusicManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nMusic);
	refOutput.WriteBytes(this->pMusic, this->nMusic * sizeof(*this->pMusic));
}

CString CDbMusicManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SMusic &refMusic = this->pMusic[index];

	debugout(refMusic.unknown, sizeof(refMusic.unknown), index);
	
	APPENDCHARARRAY("Identifier", refMusic.identifier, "", true);
	APPENDCHARARRAY("SPT file name", refMusic.sptFileName, "", true);
	
	return refMusic.identifier;
}

bool CDbMusicManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbMusicManager::Uninit()
{
}