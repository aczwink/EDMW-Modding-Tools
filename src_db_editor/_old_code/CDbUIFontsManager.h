//Local
#include "IDbManager.h"

class CDbUIFontsManager : public IDbManager
{
	struct SUIFont
	{
		char identifier[100];
		uint32 unknown1;
		uint32 unknown2;
		uint32 fontType;
		uint32 fontSize;
		uint32 unknown5;
		bool isBold;
		bool unknownBool2;
		bool isUnderlined;
		bool isShadowed;
		uint32 alwaysZero;
	};
private:
	//Members
	uint32 nFonts;
	SUIFont *pFonts;
public:
	//Constructor
	CDbUIFontsManager();
	//Destructor
	~CDbUIFontsManager();
	//Methods
	void Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const;
	void FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const;
	CString GetFileTitle() const;
	void Init();
	void ReadInput(AInputStream &refInput);
	void Save(AOutputStream &refOutput) const;
	CString SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const;
	bool SupportsFilterByDisplayString() const;
	void Uninit();
};