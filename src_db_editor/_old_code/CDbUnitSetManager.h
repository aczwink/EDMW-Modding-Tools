//Local
#include "IDbManager.h"

class CDbUnitSetManager : public IDbManager
{
	struct SUnitSet
	{
		char identifier[100];
		uint32 unknownrest[43];
	};
private:
	//Members
	uint32 nUnitSets;
	SUnitSet *pUnitSets;
public:
	//Constructor
	CDbUnitSetManager();
	//Destructor
	~CDbUnitSetManager();
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