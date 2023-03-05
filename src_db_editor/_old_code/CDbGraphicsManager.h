//Local
#include "IDbManager.h"

class CDbGraphicsManager : public IDbManager
{
	struct SGraphic
	{
		CString identifier;
		CString textures[32];
		char anotherIdentifier[100];
		char identifier3[100];
		uint32 unknown2;
		uint32 id;
		uint32 unknown1[146];
		float32 unknownFloat1;
		uint32 unknownLong1;
		float32 unknownFloat2;
		byte unknownRest[12];
	};
private:
	//Members
	uint32 nGraphics;
	SGraphic *pGraphics;
	//Methods
	void ReadGraphic(SGraphic &refGraphic, AInputStream &refInput);
	void ReadString(CString &refString, AInputStream &refInput);
	void WriteGraphic(SGraphic &refGraphic, AOutputStream &refOutput) const;
	void WriteString(CString &refString, AOutputStream &refOutput) const;
public:
	//Constructor
	CDbGraphicsManager();
	//Destructor
	~CDbGraphicsManager();
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