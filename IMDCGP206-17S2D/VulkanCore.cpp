#include "VulkanCore.h"

void vulkan_core::create_instance()
{
	VkApplicationInfo application_info = {};
	application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	application_info.pApplicationName = mWindowTitle.c_str();
	application_info.engineVersion = 1;
	application_info.apiVersion = VK_API_VERSION_1_0;

	const char* instance_extensions[] = {
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME
	};

	VkInstanceCreateInfo instance_info = {};
	instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_info.pApplicationInfo = &application_info;
	instance_info.enabledLayerCount = pInstance
}

void vulkan_core::create_surface()
{
}

void vulkan_core::select_physical_device()
{
	for(uint32_t i = 0; i < mPhysicalDevices.mDevices.size(); i++)
	{
		for(uint32_t j = 0; j < mPhysicalDevices.mQFamilyProperties[i].size(); j++)
		{
			VkQueueFamilyProperties& queue_family_property = mPhysicalDevices.mQFamilyProperties[i][j];
			VkQueueFlags flags = queue_family_property.queueFlags;

			if((flags & VK_QUEUE_GRAPHICS_BIT) && mGfxDevIndex == -1)
			{
				if (!mPhysicalDevices.mQSupportsPresent[i][j]) continue;

				mGfxDevIndex = i;
				mGfxQueueFamily = j;
			}
		}
	}

	if (mGfxDevIndex == -1) { assert(0); }
}

void vulkan_core::create_logical_device()
{
}

vulkan_core::vulkan_core(const char* pWindowTitle)
{
	mWindowTitle = std::string(pWindowTitle);
	mGfxDevIndex = -1;
	mGfxQueueFamily = -1;
}

vulkan_core::~vulkan_core()
{
}

void vulkan_core::init(vulkan_window_control* pWindowControl)
{
	std::vector<VkExtensionProperties> extension_properties;
	vulkan_enum_ext_props(extension_properties);

	create_instance();
	mVulkanSurface = pWindowControl->create_surface(mVulkanInst);
	assert(mVulkanSurface);

	vulkan_get_physical_devices(mVulkanInst, mVulkanSurface, mPhysicalDevices);
	select_physical_device();
	create_logical_device();
}

const VkPhysicalDevice& vulkan_core::get_physical_device() const
{
	assert(mGfxDevIndex >= 0);
	return mPhysicalDevices.mDevices[mGfxDevIndex];
}

const VkSurfaceFormatKHR& vulkan_core::get_surface_format() const
{
	assert(mGfxDevIndex >= -0);
	return mPhysicalDevices.mSurfaceFormats[mGfxDevIndex][0];
}

const VkSurfaceCapabilitiesKHR vulkan_core::get_surface_capabilities() const
{
	assert(mGfxDevIndex >= -0);
	return mPhysicalDevices.mSurfaceCaps[mGfxDevIndex];
}
