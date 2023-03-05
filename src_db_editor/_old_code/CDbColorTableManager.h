//Local
#include "IDbManager.h"

class CDbColorTableManager : public IDbManager
{
	struct SColorTable
	{
		char identifier[100];
		uint32 unknown1[2];
		float32 unknownFloat7;
		float32 unknownFloat8;
		float32 unknownFloat9;
		float32 unknownFloat1;
		float32 unknownFloat2;
		float32 unknownFloat3;
		float32 unknownFloat4;
		float32 unknownFloat5;
		float32 unknownFloat6;
		uint32 unknownrest[6];
	};
private:
	//Members
	uint32 nColorTables;
	SColorTable *pColorTables;
public:
	//Constructor
	CDbColorTableManager();
	//Destructor
	~CDbColorTableManager();
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