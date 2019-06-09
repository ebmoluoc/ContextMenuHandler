#include "pch.h"
#include "ContextMenuHandler.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

ContextMenuHandler::ContextMenuHandler(Dll& dll) : dll_{ dll }, refCount_{ 1 }, hBitmapMenu_{ nullptr }
{
	dll_.AddRef();

	hBitmapMenu_ = hlp::BitmapFromIconResource(dll_.Handle(), IDI_ICON_MENU, 0, 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

ContextMenuHandler::~ContextMenuHandler()
{
	if (hBitmapMenu_ != nullptr)
	{
		DeleteObject(hBitmapMenu_);
	}

	dll_.Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP ContextMenuHandler::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
	if (ppvObject == nullptr)
	{
		return E_POINTER;
	}
	else if (IsEqualIID(riid, IID_IContextMenu))
	{
		*ppvObject = static_cast<LPCONTEXTMENU>(this);
	}
	else if (IsEqualIID(riid, IID_IShellExtInit))
	{
		*ppvObject = static_cast<LPSHELLEXTINIT>(this);
	}
	else
	{
		*ppvObject = nullptr;
		return E_NOINTERFACE;
	}

	this->AddRef();

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP_(ULONG) ContextMenuHandler::AddRef()
{
	return ++refCount_;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP_(ULONG) ContextMenuHandler::Release()
{
	auto rc{ --refCount_ };
	if (rc == 0)
	{
		delete this;
	}
	return rc;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP ContextMenuHandler::Initialize(PCIDLIST_ABSOLUTE pidlFolder, LPDATAOBJECT pdtobj, HKEY hkeyProgID)
{
	UNREFERENCED_PARAMETER(pidlFolder);
	UNREFERENCED_PARAMETER(hkeyProgID);

	if (pdtobj == nullptr)
	{
		return E_INVALIDARG;
	}

	return pathList_.Load(pdtobj) ? S_OK : E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP ContextMenuHandler::QueryContextMenu(HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
	UNREFERENCED_PARAMETER(idCmdLast);

	if ((uFlags & CMF_DEFAULTONLY) != 0)
	{
		return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);
	}

	auto hSubmenu{ CreatePopupMenu() };
	if (hSubmenu == nullptr)
	{
		return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);
	}

	auto idCmd{ idCmdFirst };
	auto hModule{ dll_.Handle() };
	auto submenuItem1{ hlp::LoadStringResource(hModule, IDS_SUBMENU_ITEM_1) };
	auto submenuItem2{ hlp::LoadStringResource(hModule, IDS_SUBMENU_ITEM_2) };
	auto submenuItem3{ hlp::LoadStringResource(hModule, IDS_SUBMENU_ITEM_3) };
	auto menuItem{ hlp::LoadStringResource(hModule, IDS_MENU_ITEM) };

	if (!hlp::AddMenuItem(hSubmenu, SUBMENU_ITEM_1, submenuItem1.c_str(), idCmd++, nullptr, hBitmapMenu_) ||
		!hlp::AddMenuItem(hSubmenu, SUBMENU_ITEM_2, submenuItem2.c_str(), idCmd++, nullptr, hBitmapMenu_) ||
		!hlp::AddMenuItem(hSubmenu, SUBMENU_SEPARATOR_1, nullptr, idCmd++, nullptr, nullptr) ||
		!hlp::AddMenuItem(hSubmenu, SUBMENU_ITEM_3, submenuItem3.c_str(), idCmd++, nullptr, hBitmapMenu_) ||
		!hlp::AddMenuItem(hmenu, indexMenu, menuItem.c_str(), idCmd++, hSubmenu, hBitmapMenu_))
	{
		DestroyMenu(hSubmenu);
		return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);
	}

	return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, idCmd - idCmdFirst);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP ContextMenuHandler::InvokeCommand(LPCMINVOKECOMMANDINFO pici)
{
	if (HIWORD(pici->lpVerb) != 0)
	{
		return E_FAIL;
	}

	auto msg{ pathList_.GetItems()[0] };

	switch (LOWORD(pici->lpVerb))
	{
	case SUBMENU_ITEM_1:
		msg.insert(0, L"SUBMENU_ITEM_1 : ");
		break;
	case SUBMENU_ITEM_2:
		msg.insert(0, L"SUBMENU_ITEM_2 : ");
		break;
	case SUBMENU_ITEM_3:
		msg.insert(0, L"SUBMENU_ITEM_3 : ");
		break;
	default:
		return E_FAIL;
	}

	MessageBoxW(nullptr, msg.c_str(), PRODUCT_NAME_W, MB_OK);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP ContextMenuHandler::GetCommandString(UINT_PTR idCmd, UINT uType, UINT* pReserved, LPSTR pszName, UINT cchMax)
{
	UNREFERENCED_PARAMETER(idCmd);
	UNREFERENCED_PARAMETER(uType);
	UNREFERENCED_PARAMETER(pReserved);
	UNREFERENCED_PARAMETER(pszName);
	UNREFERENCED_PARAMETER(cchMax);

	return E_NOTIMPL;
}
