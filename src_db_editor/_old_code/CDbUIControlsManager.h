//Local
#include "IDbManager.h"

class CDbUIControlsManager : public IDbManager
{
	struct SDbUIControl
	{
		char identifier[100];
		byte unknown1[500];
		float32 unknownFloat1;
		float32 unknownFloat2;
		float32 unknownFloat3;
		uint32 alwaysZero[5];
		float32 unknownFloat4;
		float32 unknownFloat5;
		float32 unknownFloat6;
		float32 unknownFloat7;
		uint32 alwaysZero2;
		float32 unknownFloat8;
		byte unknown2[64];
		uint32 stringId;
		byte unknownRest[212];
		uint32 unknownFlags1;
		uint32 unknownLong2;
	};
private:
	//Members
	uint32 nUIControls;
	SDbUIControl *pUIControls;
public:
	//Constructor
	CDbUIControlsManager();
	//Destructor
	~CDbUIControlsManager();
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