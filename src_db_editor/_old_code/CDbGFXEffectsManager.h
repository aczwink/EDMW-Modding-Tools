//Local
#include "IDbManager.h"

class CDbGFXEffectsManager : public IDbManager
{
	struct SGFXEffect
	{
		char identifier[100];
		uint32 unknown1[5];
		float32 unknownFloat1;
		float32 unknownFloat2;
		float32 unknownFloat9;
		uint32 unknown2[10];
		float32 unknownFloat5;
		float32 unknownFloat6;
		float32 unknownFloat7;
		float32 unknownFloat8;
		float32 unknownFloat3;
		float32 unknownFloat10;
		float32 unknownFloat13;
		float32 unknownFloat11;
		float32 unknownFloat15;
		float32 unknownFloat14;
		float32 unknownFloat12;
		float32 unknownFloat4;
		bool unknownBool1;
		bool unknownBool2;
		bool unknownBool3;
		bool unknownBool4;
		uint32 unknownrest[2];
	};
private:
	//Members
	uint32 nEffects;
	SGFXEffect *pEffects;
public:
	//Constructor
	CDbGFXEffectsManager();
	//Destructor
	~CDbGFXEffectsManager();
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