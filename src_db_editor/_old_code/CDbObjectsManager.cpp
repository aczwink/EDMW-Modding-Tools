//Class Header
#include "CDbObjectsManager.h"
//Global
#include <iostream>
//Local
#include "DbManager.h"
#include "debug.h"

//Constructor
CDbObjectsManager::CDbObjectsManager()
{
	this->pObjects = NULL;
}

//Destructor
CDbObjectsManager::~CDbObjectsManager()
{
	memfreesafe(this->pObjects);
}

//Public methods
void CDbObjectsManager::Filter(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nObjects; i++)
	{
		const CString &refCurrentName = this->pObjects[i].identifier;
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

void CDbObjectsManager::FilterByDisplayName(const CString &refSearchLowerCase, SJCWinLibCommCtrl::CListView &refItemList) const
{
	uint32 i, index;
	
	for(i = 0; i < this->nObjects; i++)
	{
		const CString &refCurrentName = DbManager::Get().GetLanguageString(this->pObjects[i].stringTableId, true).ToCString();
		const CString &refCurrentLowerCase = refCurrentName.ToLowercase();
		
		if(refCurrentLowerCase.Find(refSearchLowerCase) != STRING_NOMATCH)
		{
			index = refItemList.InsertItem();
			refItemList.SetItemText(refCurrentName, index, 0);
			refItemList.SetItemData(index, i);
		}
	}
}

CString CDbObjectsManager::GetFileTitle() const
{
	return "dbobjects";
}

void CDbObjectsManager::Init()
{
}

void CDbObjectsManager::ReadInput(AInputStream &refInput)
{
	refInput.ReadUInt32(this->nObjects);
	this->pObjects = (SDbObject *)malloc(this->nObjects * sizeof(*this->pObjects));
	refInput.ReadBytes(this->pObjects, this->nObjects * sizeof(*this->pObjects));
	
	//finding out values
	//uint32 j;
	//for(j = sizeof(this->pObjects[0].unknownrest)/sizeof(this->pObjects[0].unknownrest[0])-1; j > 109; j--){
	for(uint32 i = 0; i < this->nObjects; i++)
	{
		if((this->pObjects[i].appendNameStringId != UINT32_MAX) && *this->pObjects[i].identifier) // & 0xFEFEFEFE
		{
			stdOut << i << " -> " << this->pObjects[i].unknown10[0] << " -> " << " .. " << this->pObjects[i].identifier << endl;
		}
	}
}

void CDbObjectsManager::Save(AOutputStream &refOutput) const
{
	refOutput.WriteUInt32(this->nObjects);
	refOutput.WriteBytes(this->pObjects, this->nObjects * sizeof(*this->pObjects));
}

CString CDbObjectsManager::SetItem(uint32 index, bool showUnknownValues, bool showConstValues) const
{
	uint32 i;
	
	SDbObject &refObject = this->pObjects[index];
	
	APPENDCHARARRAY("Identifier", refObject.identifier, "", true);
	APPENDUINT32("Unknown (Id?) (Unique except 0)", refObject.unknownLong4, "", true);
	APPENDUINT32("Family Id", refObject.familyId, "", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown Long 2", refObject.unknownLong2, "", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown Long 3", refObject.unknownLong3, "", true);
		SETUNKNOWN;
	}
	
	APPENDUINT32("Id", refObject.id, "", false);
	APPENDUINT32("Lifepoints", refObject.lifepoints, "", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown Long 5", refObject.unknownLong5, "1 for some ships... 0 otherwise", true);
		SETUNKNOWN;
	}

	APPENDUINT32("Minimum attack range", refObject.minimumAttackRange, "", true);
	APPENDFLOAT("Maximum attack range", refObject.maximumAttackRange, "", true);
	APPENDFLOAT("Line of sight", refObject.lineOfSight, "", true);
	APPENDFLOAT("Reload time", refObject.reloadTime, "", true);
	APPENDFLOAT("Detonation radius", refObject.detonationRadius, "", true);
	APPENDFLOAT("Velocity", refObject.velocity, "", true);
	APPENDFLOAT("Acceleration", refObject.acceleration, "acceleration = deceleration", true);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 6", refObject.unknownFloat6, "has something to do with turning speed", true);
		SETUNKNOWN;
		APPENDFLOAT("Unknown Float 7", refObject.unknownFloat7, "has something to do with turning speed", true);
		SETUNKNOWN;
	}

	APPENDFLOAT("Turret turn speed", refObject.turretTurnSpeed, "", true);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 1", refObject.unknownFloat1, "", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown Long 10", refObject.unknownLong10, "1 for airplanes, else 0", true);
		SETUNKNOWN;
	}

	APPENDUINT32("Fuel Capacity", refObject.fuelCapacity, "In Action Mode +50%, so: " + CString(refObject.fuelCapacity*3/2), true);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 11", refObject.unknownLong11, "seems to be 1 for some ships, else 0", true);
		SETUNKNOWN;
		APPENDFLOAT("Unknown Float 8", refObject.unknownFloat8, "the bigger the value, the less the unit needs to turn to attack", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown Long 12", refObject.unknownLong12, "", true);
		SETUNKNOWN;
	}
	
	APPENDUINT32("Weapon to hit id", refObject.weaponToHitId, "", true);
	APPENDUINT32("Damage", refObject.damage, "", true);
	APPENDUINT32("Armor against shock", refObject.armorAgainstShock, "", true);
	APPENDUINT32("Armor against arrows", refObject.armorAgainstArrows, "", true);
	APPENDUINT32("Armor against pierce", refObject.armorAgainstPierce, "", true);
	APPENDUINT32("Armor against guns", refObject.armorAgainstGuns, "", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown Long 17", refObject.unknownLong17, "", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown Long 18", refObject.unknownLong18, "", true);
		SETUNKNOWN;
	}

	APPENDUINT32("Projectile object Id", refObject.projectileObjectId, "", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Target Mode", refObject.targetFlags, "The pattern is really confusing...", true);
		SETUNKNOWN;
	}
	//APPENDULONGCUSTOM("Target Mode", currentObject->targetFlags, "What can be targeted? Still not editable", ITEMDATATYPE_OBJECT_ULONG_TARGETMODE);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown Long 20", refObject.unknownLong20, "mostly 1, zero for stone and gold mines; cavalier and leo 451 have special values... could be booleans...", true);
		SETUNKNOWN;
	}
	
	APPENDFLOAT("Model scale factor", refObject.modelScaleFactor, "", true);
	APPENDCHARARRAY("Type", refObject.type, "", false);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown Long 21", refObject.unknownLong21, "mostly 0, could be a bitmask...", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown Long 22", refObject.unknownLong22, "mostly 0, could be a bitmask...", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown Long 23", refObject.unknownLong23, "mostly 0, could be a bitmask...", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown Long 24", refObject.unknownLong24, "mostly 0, could be a bitmask...", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown Long 25", refObject.unknownLong25, "mostly 0, could be a bitmask...", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown Long 26", refObject.unknownLong26, "some kind of type of object? 0 = ambient stuff, 1 = resources stuff, 2 = buildings, 3 = aircraft, 4 = ship, 5 = ground unit, 6 = citizens, repair workers... there are some others also", true);
		SETUNKNOWN;
	}
	
	APPENDUINT32("String Table Id", refObject.stringTableId, DbManager::Get().GetLanguageString(refObject.stringTableId, true).ToCString(), false);
	APPENDUINT32("Button Id", refObject.buttonId, "", true);
	APPENDUINT32("Graphics Id", refObject.graphicsId, "", true);
	APPENDFLOAT("Building rate", refObject.buildingRate, "could be close to ms?! However time between amount is built", true);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 200", refObject.unknownFloat200, "for sure also a rate... iron from empire earth?", true);
		SETUNKNOWN;
	}
	
	APPENDFLOAT("Field food gather rate", refObject.fieldFoodGatherRate, "", true);
	APPENDFLOAT("Gold gather rate", refObject.goldGatherRate, "could be close to ms?! However time until 1 gold unit is picked", true);
	APPENDFLOAT("Stone gather rate", refObject.stoneGatherRate, "could be close to ms?! However time until 1 stone unit is picked", true);
	APPENDFLOAT("Wood gather rate", refObject.woodGatherRate, "", true);
	APPENDFLOAT("Animal food gather rate", refObject.animalFoodGatherRate, "also fish", true);
	APPENDFLOAT("Tree food gather rate", refObject.treeFoodGatherRate, "", true);

	if(showConstValues)
	{
		for(i = 0; i < sizeof(refObject.constMax) / sizeof(refObject.constMax[0]); i++)
		{
			APPENDUINT32("Constant FF FF FF FF", refObject.constMax[i], "", true);
			SETCONSTANT;
		}
	}

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown 8", refObject.unknown8, "2 for citizens, 0 otherwise", true);
		SETUNKNOWN;
	}
	
	APPENDINT32("Button id left panel - Bottom left", refObject.buttonIdLeftPanel_BottomLeft, "-1 = none; for some reason this is not a button id from dbbuttons", true);
	APPENDINT32("Button id left panel - Bottom center", refObject.buttonIdLeftPanel_BottomCenter, "-1 = none; for some reason this is not a button id from dbbuttons", true);
	APPENDINT32("Button id left panel - Bottom right", refObject.buttonIdLeftPanel_BottomRight, "-1 = none; for some reason this is not a button id from dbbuttons", true);
	APPENDINT32("Button id left panel - Middle left", refObject.buttonIdLeftPanel_MiddleLeft, "-1 = none; for some reason this is not a button id from dbbuttons", true);
	APPENDINT32("Button id left panel - Middle center", refObject.buttonIdLeftPanel_MiddleCenter, "-1 = none; for some reason this is not a button id from dbbuttons", true);
	APPENDINT32("Button id left panel - Middle right", refObject.buttonIdLeftPanel_MiddleRight, "-1 = none; for some reason this is not a button id from dbbuttons", true);
	APPENDINT32("Button id left panel - Top left", refObject.buttonIdLeftPanel_TopLeft, "-1 = none; for some reason this is not a button id from dbbuttons", true);
	APPENDINT32("Button id left panel - Top center", refObject.buttonIdLeftPanel_TopCenter, "-1 = none; for some reason this is not a button id from dbbuttons", true);
	APPENDINT32("Button id left panel - Top right", refObject.buttonIdLeftPanel_TopRight, "-1 = none; for some reason this is not a button id from dbbuttons", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown 9", refObject.unknown9, "", true);
	}

	APPENDUINT32("Required space", refObject.requiredSpace, "which measurement unit?!", true);
	APPENDCUSTOM("Resource Type", refObject.resourceType, this->GetResourceTypeString((EResourceType)refObject.resourceType), ITEMDATATYPE_OBJECT_RESOURCETYPE);
	APPENDFLOAT("Resource Amount", refObject.resourceAmount, "", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown Long 55", refObject.unknownLong55, "mostly 0", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown Long 56", refObject.unknownLong56, "mostly 0, sometimes 32-bit MAX, rarely something else", true);
		SETUNKNOWN;
		APPENDFLOAT("Unknown Float 55", refObject.unknownFloat55, "", true);
		SETUNKNOWN;
	}
	
	APPENDUINT32("Population count", refObject.populationCount, "", true);
	APPENDUINT32("Transport count", refObject.transportCount, "", true);

	APPENDBOOL("Show attack radius in HUD", refObject.showAttackRadius, "", true);
	APPENDBOOL("Show repair value in HUD", refObject.showRepairValue, "", true);
	APPENDBOOL("Show armor against shock value in HUD", refObject.showArmorAgainstShock, "", true);
	APPENDBOOL("Show armor against pierce value in HUD", refObject.showArmorAgainstPierce, "", true);
	APPENDBOOL("Show armor against arrows value in HUD", refObject.showArmorAgainstArrows, "", true);
	APPENDBOOL("Show armor against laser value in HUD", refObject.showArmorAgainstLaser, "", true);
	APPENDBOOL("Show armor against guns value in HUD", refObject.showArmorAgainstGuns, "", true);
	APPENDBOOL("Show armor against missiles value in HUD", refObject.showArmorAgainstMissiles, "", true);
	APPENDBOOL("Show attack range in HUD", refObject.showAttackRange, "", true);

	if(showUnknownValues)
	{
		APPENDBOOL("Unknown Bool 32", refObject.unknownBool32, "only set for german armory and enligsh mary something ship", true);
		SETUNKNOWN;
	}

	if(showConstValues)
	{
		APPENDBOOL("Unknown Bool 33", refObject.unknownBool33, "", true);
		SETCONSTANT;
		APPENDBOOL("Unknown Bool 34", refObject.unknownBool34, "", true);
		SETCONSTANT;
	}

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown 16", refObject.unknown16, "", true);
		SETUNKNOWN;
		APPENDFLOAT("Unknown Float 201", refObject.unknownFloat201, "always 0, except for french communications truck", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown 17", refObject.unknown17, "", true);
		SETUNKNOWN;
	}
	
	APPENDFLOAT("Steering rotation", refObject.steeringRotation, "unit?", true);
	
	if(showUnknownValues)
	{
		APPENDUINT32("Unknown 18", refObject.unknown18, "", true);
		SETUNKNOWN;
	}
	
	APPENDFLOAT("Altitude", refObject.altitude, "unit? it is some kind of scale factor", true);
	
	debugout(refObject.unknown10, sizeof(refObject.unknown10), index);

	if(showUnknownValues)
	{
		APPENDBOOL("Unknown Bool 21", refObject.unknownBool21, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 22", refObject.unknownBool22, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 23", refObject.unknownBool23, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 24", refObject.unknownBool24, "", true);
		SETUNKNOWN;
	}

	APPENDUINT32("Dropped Bombs per Run", refObject.bombsPerRun, "", true);

	if(showUnknownValues)
	{
		APPENDUINT32("Unknown Long 71", refObject.unknownLong71, "", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown Long 72", refObject.unknownLong72, "", true);
		SETUNKNOWN;
		APPENDFLOAT("Unknown Float 70", refObject.unknownFloat70, "", true);
		SETUNKNOWN;
		APPENDFLOAT("Unknown Float 71", refObject.unknownFloat71, "", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown Long 73", refObject.unknownLong73, "", true);
		SETUNKNOWN;
		APPENDFLOAT("Unknown Float 72", refObject.unknownFloat72, "", true);
		SETUNKNOWN;
		APPENDFLOAT("Unknown Float 73", refObject.unknownFloat73, "", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown Long 74", refObject.unknownLong74, "", true);
		SETUNKNOWN;
		APPENDFLOAT("Unknown Float 74", refObject.unknownFloat74, "", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown Long 75", refObject.unknownLong75, "", true);
		SETUNKNOWN;
	}
	
	APPENDUINT32("Number of carried Bombs", refObject.bombsCount, "", true);

	debugout(refObject.unknown12, sizeof(refObject.unknown12), index);

	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 76", refObject.unknownFloat76, "", true);
		SETUNKNOWN;
	}

	debugout(refObject.unknown13, sizeof(refObject.unknown13), index);

	APPENDUINT32("Unit String Id 1", refObject.unitStringId1, DbManager::Get().GetLanguageString(refObject.unitStringId1).ToCString(), false);
	APPENDUINT32("Unit String Id 2", refObject.unitStringId2, DbManager::Get().GetLanguageString(refObject.unitStringId2).ToCString(), false);
	APPENDUINT32("Tooltip String Id", refObject.tooltipStringId, DbManager::Get().GetLanguageString(refObject.tooltipStringId).ToCString(), false);
	APPENDINT32("Appended Name string Id", refObject.appendNameStringId, "The following will be appended to the units name in Szenario-Editor (-1 = nothing): " + DbManager::Get().GetLanguageString(refObject.appendNameStringId).ToCString(), true);
	
	debugout(refObject.unknownarr10, sizeof(refObject.unknownarr10), index);
	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 118", refObject.unknownFloat118, "", true);
		SETUNKNOWN;
		APPENDFLOAT("Unknown Float 119", refObject.unknownFloat119, "", true);
		SETUNKNOWN;
		APPENDFLOAT("Unknown Float 120", refObject.unknownFloat120, "", true);
		SETUNKNOWN;

		APPENDBOOL("Unknown Bool 1", refObject.unknownBool1, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 2", refObject.unknownBool2, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 3", refObject.unknownBool3, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 4", refObject.unknownBool4, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 5", refObject.unknownBool5, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 6", refObject.unknownBool6, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 7", refObject.unknownBool7, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 8", refObject.unknownBool8, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 9", refObject.unknownBool9, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 10", refObject.unknownBool10, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 11", refObject.unknownBool11, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 12", refObject.unknownBool12, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 13", refObject.unknownBool13, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 14", refObject.unknownBool14, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 15", refObject.unknownBool15, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 16", refObject.unknownBool16, "", true);
		SETUNKNOWN;
	}
	debugout(refObject.unknownarr11, sizeof(refObject.unknownarr11), index);
	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 155", refObject.unknownFloat155, "", true);
		SETUNKNOWN;
	}
	debugout(refObject.unknown15, sizeof(refObject.unknown15), index);
	if(showUnknownValues)
	{
		APPENDBOOL("Unknown Bool 17", refObject.unknownBool17, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 18", refObject.unknownBool18, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 19", refObject.unknownBool19, "", true);
		SETUNKNOWN;
		APPENDBOOL("Unknown Bool 20", refObject.unknownBool20, "", true);
		SETUNKNOWN;
	}
	debugout(refObject.unknownarr12, sizeof(refObject.unknownarr12), index);
	if(showUnknownValues)
	{
		APPENDFLOAT("Unknown Float 151", refObject.unknownFloat151, "", true);
		SETUNKNOWN;
		APPENDFLOAT("Unknown Float 152", refObject.unknownFloat152, "", true);
		SETUNKNOWN;
		APPENDFLOAT("Unknown Float 153", refObject.unknownFloat153, "", true);
		SETUNKNOWN;
		APPENDUINT32("Unknown Long 201", refObject.unknownLong201, "", true);
		SETUNKNOWN;
		APPENDFLOAT("Unknown Float 154", refObject.unknownFloat154, "", true);
		SETUNKNOWN;
	}
	debugout(refObject.unknown19, sizeof(refObject.unknown19), index);
	
	APPENDUINT32("Tech Id", refObject.techId, "", true);
	
	debugout(refObject.unknown14, sizeof(refObject.unknown14), index);
	
	for(i = 0; i < sizeof(refObject.constructionTechIds) / sizeof(refObject.constructionTechIds[0]); i++)
	{
		APPENDUINT32("Construction tech id - " + CString(i+1), refObject.constructionTechIds[i], "tech for a building, that the unit can construct", true);
	}
	
	return DbManager::Get().GetLanguageString(refObject.stringTableId, true).ToCString();
}

bool CDbObjectsManager::SupportsFilterByDisplayString() const
{
	return true;
}

void CDbObjectsManager::Uninit()
{
}

//Public Functions
CString CDbObjectsManager::GetResourceTypeString(EResourceType type)
{
	switch(type)
	{
	case RESOURCETYPE_NONE:
		return "None";
	case RESOURCETYPE_UNKNOWNRESOURCE:
		return "Unknown";
	case RESOURCETYPE_FOOD:
		return "Food";
	case RESOURCETYPE_WOOD:
		return "Wood";
	case RESOURCETYPE_STONE:
		return "Stone";
	case RESOURCETYPE_GOLD:
		return "Gold";
	}
	return "Illegal";
}