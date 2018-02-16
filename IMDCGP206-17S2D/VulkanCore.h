#ifndef IMDCGP206_17S2D_VULKAN_CORE_H
#define IMDCGP206_17S2D_VULKAN_CORE_H

#include <string>
#include <cstdio>
#include <cassert>
#include "Vulkan.h"

class vulkan_core
{
private:
	void create_instance();
	void create_surface();
	void select_physical_device();
	void create_logical_device();

	VkInstance mVulkanInst;
	VkSurfaceKHR mVulkanSurface;
	vulkan_physical_devices mPhysicalDevices;
	VkDevice mDevice;

	std::string mWindowTitle;
	int mGfxDevIndex;
	int mGfxQueueFamily;
public:
	vulkan_core(const char* pWindowTitle);
	~vulkan_core();
	void init(vulkan_window_control * pWindowControl);
	const VkPhysicalDevice& get_physical_device() const;
	const VkSurfaceFormatKHR& get_surface_format() const;
	const VkSurfaceCapabilitiesKHR get_surface_capabilities() const;
	const VkSurfaceKHR& get_surface() const { return mVulkanSurface; }
	int get_queue_family() const { return mGfxQueueFamily; }
	VkInstance& get_instance() { return mVulkanInst; }
	VkDevice& get_device() { return mDevice; }
};

#endif