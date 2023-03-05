//Local
#include "IDbManager.h"

enum EResourceType
{
	RESOURCETYPE_NONE,
	RESOURCETYPE_UNKNOWNRESOURCE,
	RESOURCETYPE_FOOD,
	RESOURCETYPE_WOOD,
	RESOURCETYPE_STONE,
	RESOURCETYPE_GOLD
};

class CDbObjectsManager : public IDbManager
{
	struct SDbObject
	{
		char identifier[100];
		uint32 unknownLong4;
		uint32 familyId;
		uint32 unknownLong2;
		uint32 unknownLong3;
		uint32 id;
		uint32 lifepoints;
		uint32 unknownLong5;
		float32 minimumAttackRange;
		float32 maximumAttackRange;
		float32 lineOfSight;
		float32 reloadTime;
		float32 detonationRadius;
		float32 velocity;
		float32 acceleration;
		float32 unknownFloat6;
		float32 unknownFloat7;
		float32 turretTurnSpeed;
		float32 unknownFloat1;
		uint32 unknownLong10;
		uint32 fuelCapacity;
		float32 unknownLong11;
		float32 unknownFloat8;
		uint32 unknownLong12;
		uint32 weaponToHitId;
		uint32 damage;
		uint32 armorAgainstShock;
		uint32 armorAgainstArrows;
		uint32 armorAgainstPierce;
		uint32 armorAgainstGuns;
		uint32 unknownLong17;
		uint32 unknownLong18;
		uint32 projectileObjectId;
		uint32 targetFlags;
		uint32 unknownLong20;
		float32 modelScaleFactor;
		char type[32];
		uint32 unknownLong21;
		uint32 unknownLong22;
		uint32 unknownLong23;
		uint32 unknownLong24;
		uint32 unknownLong25;
		uint32 unknownLong26;
		uint32 stringTableId;
		uint32 buttonId;
		uint32 graphicsId;
		float32 buildingRate;
		float32 unknownFloat200;
		float32 fieldFoodGatherRate;
		float32 goldGatherRate;
		float32 stoneGatherRate;
		float32 woodGatherRate;
		float32 animalFoodGatherRate;
		float32 treeFoodGatherRate;
		uint32 constMax[6];
		uint32 unknown8;
		int32 buttonIdLeftPanel_BottomLeft;
		int32 buttonIdLeftPanel_BottomCenter;
		int32 buttonIdLeftPanel_BottomRight;
		int32 buttonIdLeftPanel_MiddleLeft;
		int32 buttonIdLeftPanel_MiddleCenter;
		int32 buttonIdLeftPanel_MiddleRight;
		int32 buttonIdLeftPanel_TopLeft;
		int32 buttonIdLeftPanel_TopCenter;
		int32 buttonIdLeftPanel_TopRight;
		uint32 unknown9;
		uint32 requiredSpace;
		uint32 resourceType;
		float32 resourceAmount;
		uint32 unknownLong55;
		uint32 unknownLong56;
		float32 unknownFloat55;
		uint32 populationCount;
		uint32 transportCount;
		bool showAttackRadius;
		bool showRepairValue;
		bool showArmorAgainstShock;
		bool showArmorAgainstPierce;
		bool showArmorAgainstArrows;
		bool showArmorAgainstLaser;
		bool showArmorAgainstGuns;
		bool showArmorAgainstMissiles;
		bool showAttackRange;
		bool unknownBool32;
		bool unknownBool33;
		bool unknownBool34;
		uint32 unknown16;
		float32 unknownFloat201;
		uint32 unknown17;
		float32 steeringRotation;
		uint32 unknown18;
		float32 altitude;
		uint32 unknown10[4];
		bool unknownBool21;
		bool unknownBool22;
		bool unknownBool23;
		bool unknownBool24;
		uint32 bombsPerRun;
		uint32 unknownLong71;
		uint32 unknownLong72;
		float32 unknownFloat70;
		float32 unknownFloat71;
		uint32 unknownLong73;
		float32 unknownFloat72;
		float32 unknownFloat73;
		uint32 unknownLong74;
		float32 unknownFloat74;
		uint32 unknownLong75;
		uint32 bombsCount;
		uint32 unknown12[11];
		float32 unknownFloat76;
		uint32 unknown13[5];
		uint32 unitStringId1;
		uint32 unitStringId2;
		int32 tooltipStringId;
		uint32 appendNameStringId;
		uint32 unknownarr10[26];
		float32 unknownFloat118;
		float32 unknownFloat119;
		float32 unknownFloat120;
		bool unknownBool1;
		bool unknownBool2;
		bool unknownBool3;
		bool unknownBool4;
		bool unknownBool5;
		bool unknownBool6;
		bool unknownBool7;
		bool unknownBool8;
		bool unknownBool9;
		bool unknownBool10;
		bool unknownBool11;
		bool unknownBool12;
		bool unknownBool13;
		bool unknownBool14;
		bool unknownBool15;
		bool unknownBool16;
		uint32 unknownarr11[8];
		float32 unknownFloat155;
		uint32 unknown15[2];
		bool unknownBool17;
		bool unknownBool18;
		bool unknownBool19;
		bool unknownBool20;
		uint32 unknownarr12[14];
		float32 unknownFloat151;
		float32 unknownFloat152;
		float32 unknownFloat153;
		uint32 unknownLong201;
		float32 unknownFloat154;
		uint32 unknown19[4];
		uint32 techId;
		uint32 unknown14[58];
		uint32 constructionTechIds[199];
		uint32 alwaysMax[1]; //always 0xFF FF FF FF
	};
private:
	//Members
	uint32 nObjects;
	SDbObject *pObjects;
public:
	//Constructor
	CDbObjectsManager();
	//Destructor
	~CDbObjectsManager();
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
	//Functions
	static CString GetResourceTypeString(EResourceType type);
};