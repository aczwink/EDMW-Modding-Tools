//Class Header
#include "CDbUIFontsManager.h"
//Local
#include "DbManager.h"

//Constructor
CDbUIFontsManager::CDbUIFontsManager()
{
}

//Destructor
CDbUIFontsManager::~CDbUIFontsManager()
{
	memfreesafe(this->pFonts);
}

//Public methods
void CDbUIFontsManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nFonts; i++)
	{
		const CString &refCurrentName = this->pFonts[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbUIFontsManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	ASSERT(0);
}

CString CDbUIFontsManager::GetFileTitle() const
{
	return "dbuifonts";
}

void CDbUIFontsManager::Init()
{
}

void CDbUIFontsManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nFonts);

	this->pFonts = (SUIFont *)malloc(this->nFonts * sizeof(*this->pFonts));
	refInput.ReadBytes(this->pFonts, this->nFonts * sizeof(*this->pFonts));

	//finding out values
	/*for(uint32 i = 0; i < this->nFonts; i++)
	{
		if(this->pFonts[i].unknown2 != i)
		{
			stdOut << i << " " << this->pFonts[i].unknown2 << " -> " << this->pFonts[i].identifier << endl;
		}
	}*/
}

void CDbUIFontsManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nFonts);
	refOutput.WriteBytes(this->pFonts, this->nFonts * sizeof(*this->pFonts));
}

CString CDbUIFontsManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	SUIFont &refFont = this->pFonts[index];
	
	APPENDCHARARRAY("Identifier", refFont.identifier, "", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown 1", refFont.unknown1, "", true);
		APPENDUINT32("Unknown 2", refFont.unknown2, "", true);
	}
	
	APPENDUINT32("Font type", refFont.fontType, "0 = None, 1 = Arial, 2 = Times New Roman, 3 = Courier New, 4 = Tahoma, 5 = Georgia, ", true);
	APPENDUINT32("Font size", refFont.fontSize, "", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown 5", refFont.unknown5, "0 when Low Quality... else 2", true);
		APPENDBOOL("Unknown Bool 2", refFont.unknownBool2, "always false...", true);
	}
	
	APPENDBOOL("Bold", refFont.isBold, "", true);
	APPENDBOOL("Underline", refFont.isUnderlined, "", true);
	APPENDBOOL("Shadowed", refFont.isShadowed, "", true);
	
	return refFont.identifier;
}

bool CDbUIFontsManager::SupportsFilterByDisplayString() const
{
	return false;
}

void CDbUIFontsManager::Uninit()
{
}