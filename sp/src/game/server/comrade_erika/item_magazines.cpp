// Implementation of all magazine entities
#include "cbase.h"
#include "items.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

class CItem_Mag_9x19_15 : public CItem
{
public:
	DECLARE_CLASS(CItem_Mag_9x19_15, CItem);

	void Spawn(void)
	{
		Precache();
		SetModel("models/items/boxsrounds.mdl");
		
		// ItemID must be established before running the common spawn code
		m_iItemID = 250;

		BaseClass::Spawn();
	}
	void Precache(void)
	{
		PrecacheModel("models/items/boxsrounds.mdl");
	}
	bool MyTouch(CBasePlayer *pPlayer)
	{
		return false;
	}
};
LINK_ENTITY_TO_CLASS(item_mag_9x19_15, CItem_Mag_9x19_15)