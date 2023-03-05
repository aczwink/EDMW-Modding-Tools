//Local
#include "IDbManager.h"

class CDbAreaEffectManager : public IDbManager
{
	struct SAreaEffect
	{
		char identifier[100];
		uint32 unknown1[14];
		float32 unknownFloat1;
		uint32 unknown2;
		float32 unknownFloat2;
		float32 unknownFloat3;
		float32 unknownFloat4;
		float32 unknownFloat5;
		uint32 unknownrest[5];
	};
private:
	//Members
	uint32 nAreaEffects;
	SAreaEffect *pAreaEffects;
public:
	//Constructor
	CDbAreaEffectManager();
	//Destructor
	~CDbAreaEffectManager();
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