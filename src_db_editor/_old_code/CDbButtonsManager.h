//Local
#include "IDbManager.h"

class CDbButtonsManager : public IDbManager
{
	struct SDbButton
	{
		char identifier[100];
		char textureName[100];
		uint32 unknownLong1;
		uint32 unknownLong2;
		uint32 alwaysZero[2];
		uint32 buttonPosition;
		uint32 alwaysMax; //always 0xFF FF FF FF
		uint32 unknownLong4;
	};
private:
	//Members
	uint32 nButtons;
	SDbButton *pButtons;
public:
	//Constructor
	CDbButtonsManager();
	//Destructor
	~CDbButtonsManager();
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