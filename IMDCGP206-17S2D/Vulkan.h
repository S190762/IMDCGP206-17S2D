#ifndef IMDCGP206_17S2D_VULKAN_H
#define IMDCGP206_17S2D_VULKAN_H

#include <vector>

#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <vulkan/vk_sdk_platform.h>
#endif

struct vulkan_physical_devices
{
	std::vector<VkPhysicalDevice> mDevices;
	std::vector<VkPhysicalDeviceProperties> mDeviceProperties;
	std::vector<std::vector<VkQueueFamilyProperties>> mQFamilyProperties;
	std::vector<std::vector<VkBool32>> mQSupportsPresent;
	std::vector<std::vector<VkSurfaceFormatKHR>> mSurfaceFormats;
	std::vector<VkSurfaceCapabilitiesKHR> mSurfaceCaps;
};

void vulkan_enum_ext_props(std::vector<VkExtensionProperties>& pExtProps)
{
	uint32_t num_extensions = 0;
	VkResult res = vkEnumerateInstanceExtensionProperties(nullptr, &num_extensions, nullptr);
	pExtProps.resize(num_extensions);
}
void vulkan_print_image_usage_flags(const VkImageUsageFlags& pFlags);
VkShaderModule vulkan_create_shader_module(VkDevice& pDevice, const char * pFileName);
void vulkan_get_physical_devices(const VkInstance& pInst, const VkSurfaceKHR& pSurface, vulkan_physical_devices& pPhysicalDevices);

class vulkan_window_control
{
protected:
	vulkan_window_control() {}
	~vulkan_window_control() {};
public:
	virtual void init(uint32_t pWidth, uint32_t pHeight) = 0;
	virtual VkSurfaceKHR create_surface(VkInstance& pInst) = 0;
};

#endif