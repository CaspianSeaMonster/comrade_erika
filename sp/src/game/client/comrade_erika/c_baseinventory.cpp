//
//  c_baseinventory.cpp
//  games
//
//  Created by Michelle Darcy on 3/2/14.
//
//

#include "cbase.h"
#include "c_baseinventory.h"
#include "usermessages.h"
#include "c_user_message_register.h"

CBaseInventory::CBaseInventory()
{
	for (int i = 0; i < MAX_INVENTORY; ++i)
	{
		UpdateObject( i, -1, 0, 0);
	}
}

// declare the user message handler
void __MsgFunc_InventoryUpdate( bf_read &msg )
{
	int element = msg.ReadByte();
	int id = msg.ReadLong(); // No integer type. Huh.
	int cap = msg.ReadByte();
	int maxcap = msg.ReadByte();
	
	CBasePlayer *pPlayer = ToBasePlayer( UTIL_PlayerByIndex( 1 ) );
	
	if ( pPlayer )
	{
		pPlayer->UpdateInventoryObject(element, id, cap, maxcap );
	}
	
}

// register message handler once
USER_MESSAGE_REGISTER(InventoryUpdate)

int CBaseInventory::GetItemID( int element )
{
	return ItemID[element];
}

int CBaseInventory::GetItemCapacity( int element )
{
	return ItemCap[element];
}

int CBaseInventory::GetItemMaxCapacity( int element )
{
	return ItemMaxCap[element];
}

bool CBaseInventory::GetItemDirtiness( int element )
{
	return ItemDirty[element];
}

int CBaseInventory::FindFirstFreeObject()
{
	for (int i = 0; i < MAX_INVENTORY; ++i)
	{
		if (ItemID[i] == -1)
		{
			return i;
		}
	}
	return -1;
}

void CBaseInventory::UpdateObject( int ObjectIndex, int NewItemID, int NewItemCap, int NewItemMaxCap )
{
	ItemID[ObjectIndex] = NewItemID;
	ItemCap[ObjectIndex] = NewItemCap;
	ItemMaxCap[ObjectIndex] = NewItemMaxCap;
	ItemDirty[ObjectIndex] = true;
	DevMsg("Client: Updated object at position %d of type %d with capacity %d and max capacity %d\n", ObjectIndex, NewItemID, NewItemCap, NewItemMaxCap);
}

int CBaseInventory::CountAllObjectContentsOfID(int itemid)
{
	int itemcount = 0;

	for (int i = 0; i < MAX_INVENTORY; ++i)
	{
		if (GetItemID(i) == itemid)
		{
			itemcount = itemcount + GetItemCapacity(i);
		}
	}

	return itemcount;
}

int CBaseInventory::CountAllObjectsOfID(int itemid)
{
	int items = 0;
	for (int i = 0; i < MAX_INVENTORY; ++i)
	{
		if (GetItemID(i) == itemid)
			++items;
	}
	return items;
}
void CBaseInventory::ItemIsClean( int element )
{
	ItemDirty[element] = false;
}