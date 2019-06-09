#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#define VER_N(major,minor,build,revision) major,minor,build,revision

#define VER_A_(v) #v
#define VER_A(major,minor,build,revision) VER_A_(major.minor.build.revision)

#define WSTR_(sa) L##sa
#define WSTR(sa) WSTR_(sa)

///////////////////////////////////////////////////////////////////////////////////////////////////

#define VERSION_MAJOR				2
#define VERSION_MINOR				3
#define VERSION_BUILD				4
#define VERSION_REVISION			5

///////////////////////////////////////////////////////////////////////////////////////////////////

#define IDI_ICON_MENU				100
#define ICON_MENU_NAME_A			"icon.ico"

///////////////////////////////////////////////////////////////////////////////////////////////////

#define SUBMENU_ITEM_1				0
#define SUBMENU_ITEM_2				1
#define SUBMENU_SEPARATOR_1			2
#define SUBMENU_ITEM_3				3
#define MENU_ITEM					4

#define IDS_SUBMENU_ITEM_1			200 + SUBMENU_ITEM_1
#define IDS_SUBMENU_ITEM_2			200 + SUBMENU_ITEM_2
#define IDS_SUBMENU_ITEM_3			200 + SUBMENU_ITEM_3
#define IDS_MENU_ITEM				200 + MENU_ITEM

///////////////////////////////////////////////////////////////////////////////////////////////////

#define PRODUCT_NAME_A				"Context Menu Handler"
#define PRODUCT_NAME_W				WSTR(PRODUCT_NAME_A)

///////////////////////////////////////////////////////////////////////////////////////////////////

#define PRODUCT_DESCRIPTION_A		"Context Menu Handler Shell Extension"

///////////////////////////////////////////////////////////////////////////////////////////////////

#define PRODUCT_COPYRIGHT_A			"Copyright (c) 2019 ebmoluoc"

///////////////////////////////////////////////////////////////////////////////////////////////////

#define PRODUCT_HKCR_W				L"*", L"Directory"

///////////////////////////////////////////////////////////////////////////////////////////////////

#define PRODUCT_CLSID_W				L"{AAAAAAAA-BBBB-CCCC-DDDD-EEEEEEEEEEEE}"