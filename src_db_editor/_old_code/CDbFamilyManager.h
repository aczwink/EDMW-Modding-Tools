//Local
#include "IDbManager.h"

class CDbFamilyManager : public IDbManager
{
	struct SFamily
	{
		char identifier[100];
		uint32 unknown1;
		uint32 id;
		uint32 unknownrest[76];
	};
private:
	//Members
	uint32 nFamilies;
	SFamily *pFamilies;
public:
	//Constructor
	CDbFamilyManager();
	//Destructor
	~CDbFamilyManager();
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