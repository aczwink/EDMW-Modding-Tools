//Local
#include "IDbManager.h"

class CDbAIUnitTargeting : public IDbManager
{
	struct SAIUnitTargeting
	{
		char identifier[100];
		byte unknownRest[60];
	};
private:
	//Members
	uint32 nAIUnitTargetings;
	SAIUnitTargeting *pAIUnitTargetings;
public:
	//Constructor
	CDbAIUnitTargeting();
	//Destructor
	~CDbAIUnitTargeting();
	//Methods
	void Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const;
	void FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const;
	void Init();
	void ReadInput(AInputStream &refInput);
	void Save(AOutputStream &refOutput) const;
	CString SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const;
	bool SupportsFilterByDisplayString() const;
	void Uninit();
};