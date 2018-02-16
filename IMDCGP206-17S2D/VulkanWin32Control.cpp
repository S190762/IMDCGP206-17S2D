#include "Vulkan.h"
#include "VulkanWin32Control.h"

LRESULT CALLBACK WinProc(HWND mHwnd, UINT mUmsg, WPARAM mWparam, LPARAM mLparam)
{
	return DefWindowProc(mHwnd, mUmsg, mWparam, mLparam);
}

vulkan_win32_control::vulkan_win32_control(const char* pWindowName)
{
	mHinstance = GetModuleHandle(nullptr);
	assert(mHinstance);
	mHwnd = 0;
	std::string s(pWindowName);
	mWindowName = std::wstring(s.begin(), s.end());
}

vulkan_win32_control::~vulkan_win32_control()
{
}

void vulkan_win32_control::init(uint32_t pWidth, uint32_t pHeight)
{
	WNDCLASSEX wndcls = {};

	wndcls.cbSize = sizeof(wndcls);
	wndcls.lpfnWndProc = WinProc;
	wndcls.hInstance = mHinstance;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndcls.lpszClassName = L"imdcgp206_17s2d";

	if (!RegisterClassEx(&wndcls))
		DWORD error = GetLastError();

	mHwnd = CreateWindowEx(0, L"imdcgp206_17s2d", mWindowName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, pWidth, pHeight, nullptr, nullptr, mHinstance, nullptr);

	if (mHwnd == 0)
		DWORD error = GetLastError();
	
	ShowWindow(mHwnd, SW_SHOW);
}

VkSurfaceKHR vulkan_win32_control::create_vulkan_surface(VkInstance& pInst)
{
	VkWin32SurfaceCreateInfoKHR surface_create_info = {};
	surface_create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surface_create_info.hinstance = mHinstance;
	surface_create_info.hwnd = mHwnd;

	VkSurfaceKHR surface;
	VkResult res = vkCreateWin32SurfaceKHR(pInst, &surface_create_info, nullptr, &surface);
	return surface;
}
