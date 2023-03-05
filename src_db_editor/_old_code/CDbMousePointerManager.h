//Local
#include "IDbManager.h"

class CDbMousePointerManager : public IDbManager
{
	struct SMousePointer
	{
		char identifier[100];
		char texture[100];
		uint32 unknownrest[6];
	};
private:
	//Members
	uint32 nMousePointers;
	SMousePointer *pMousePointers;
public:
	//Constructor
	CDbMousePointerManager();
	//Destructor
	~CDbMousePointerManager();
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