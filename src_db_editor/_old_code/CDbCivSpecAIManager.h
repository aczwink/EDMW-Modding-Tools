//Local
#include "IDbManager.h"

class CDbCivSpecAIManager : public IDbManager
{
	struct SCivSpecAI
	{
		uint32 unknown1[28];
		float32 unknownFloat1;
		float32 unknownFloat2;
		float32 unknownFloat3;
		float32 unknownFloat4;
		float32 unknownFloat5;
		float32 unknownFloat6;
		float32 unknownFloat7;
		float32 unknownFloat8;
		float32 unknownFloat9;
		float32 unknownFloat10;
		float32 unknownFloat11;
		float32 unknownFloat12;
		float32 unknownFloat13;
		float32 unknownFloat14;
		float32 unknownFloat15;
		float32 unknownFloat16;
		uint32 unknownrest[5];
	};
private:
	//Members
	uint32 nCivSpecAIs;
	SCivSpecAI *pCivSpecAIs;
public:
	//Constructor
	CDbCivSpecAIManager();
	//Destructor
	~CDbCivSpecAIManager();
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