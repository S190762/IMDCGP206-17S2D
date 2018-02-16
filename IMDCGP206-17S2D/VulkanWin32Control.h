#ifndef IMDCGP206_17S2D_VULKAN_WIN32_CONTROL_H
#define IMDCGP206_17S2D_VULKAN_WIN32_CONTROL_H

#include "Vulkan.h"
#include <cassert>

class vulkan_win32_control : public vulkan_window_control
{
private:
	HINSTANCE mHinstance;
	HWND mHwnd;
	std::wstring mWindowName;
public:
	vulkan_win32_control(const char* pWindowName);
	~vulkan_win32_control();
	virtual void init(uint32_t pWidth, uint32_t pHeight);
	virtual VkSurfaceKHR create_vulkan_surface(VkInstance& pInst);
};

#endif