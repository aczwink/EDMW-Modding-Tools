//Class Header
#include "CDbMousePointerManager.h"
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbMousePointerManager::CDbMousePointerManager()
{
}

//Destructor
CDbMousePointerManager::~CDbMousePointerManager()
{
	memfreesafe(this->pMousePointers);
}

//Public methods
void CDbMousePointerManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nMousePointers; i++)
	{
		const CString &refCurrentName = this->pMousePointers[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbMousePointerManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbMousePointerManager::GetFileTitle() const
{
	return "dbmousepointer";
}

void CDbMousePointerManager::Init()
{
}

void CDbMousePointerManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nMousePointers);

	this->pMousePointers = (SMousePointer *)malloc(this->nMousePointers * sizeof(*this->pMousePointers));
	refInput.ReadBytes(this->pMousePointers, this->nMousePointers * sizeof(*this->pMousePointers));
}

void CDbMousePointerManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nMousePointers);
	refOutput.WriteBytes(this->pMousePointers, this->nMousePointers * sizeof(*this->pMousePointers));
}

CString CDbMousePointerManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SMousePointer &refMousePointer = this->pMousePointers[index];
	
	APPENDCHARARRAY("Identifier", refMousePointer.identifier, "", true);
	APPENDCHARARRAY("Texture", refMousePointer.texture, "", true);
	
	debugout(refMousePointer.unknownrest, sizeof(refMousePointer.unknownrest), index);

	return refMousePointer.identifier;
}

bool CDbMousePointerManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbMousePointerManager::Uninit()
{
}