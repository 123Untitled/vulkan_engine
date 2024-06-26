#include "engine/vulkan/instance.hpp"
#include "engine/vk/destroy.hpp"
#include "engine/vk/create.hpp"
#include "engine/glfw/system.hpp"

#include "engine/os.hpp"


// -- constants ---------------------------------------------------------------

/* create flags */
enum : vk::instance_create_flags {
	#if defined(ENGINE_OS_MACOS)
	CREATE_FLAGS = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
	#else
	CREATE_FLAGS = 0,
	#endif
};


// -- public conversion operators ---------------------------------------------

/* vk::instance conversion operator */
vulkan::instance::operator const vk::instance&(void) const noexcept {
	return _instance;
}


// -- public static methods ---------------------------------------------------

/* shared */
auto vulkan::instance::shared(void) -> self& {
	static self __self{};
	return __self;
}

/* physical devices */
auto vulkan::instance::physical_devices(void) -> const vk::vector<vulkan::physical_device>& {
	static auto __pdevices = vk::enumerate_physical_devices<vulkan::physical_device>(self::shared());
	return __pdevices;
}

/* validation layers */
#if defined(ENGINE_VL_DEBUG)
auto vulkan::instance::validation_layers(void) -> const vk::array<const char*, 1>& {
	static const vk::array<const char*, 1> __layers {
		"VK_LAYER_KHRONOS_validation"
		//"VK_LAYER_LUNARG_api_dump",
		//"VK_LAYER_KHRONOS_profiles",
		//"VK_LAYER_KHRONOS_synchronization2",
		//"VK_LAYER_KHRONOS_shader_object"
	};
	return __layers;
}
#endif


// -- private lifecycle -------------------------------------------------------

/* default constructor */
vulkan::instance::instance(void)
#if defined(ENGINE_VL_DEBUG)
: _instance{}, _messenger{} {
#else
: _instance{} {
#endif

	// create application info
	constexpr vk::application_info app_info{
		.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext              = nullptr,
		.pApplicationName   = "application",
		.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0),
		.pEngineName        = "engine",
		.engineVersion      = VK_MAKE_API_VERSION(0, 1, 0, 0),
		.apiVersion         = VK_API_VERSION_1_0
	};

	// get required extensions
	auto extensions = glfw::system::shared().vulkan_required_extensions();


	#if defined(ENGINE_VL_DEBUG)

	// get messenger info
	constexpr vk::debug_utils_messenger_info debug_info{
		.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
		.pNext           = VK_NULL_HANDLE,
		.flags           = 0,
		.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
						 | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
						 | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
		.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
						 | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
						 | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
		.pfnUserCallback = self::callback,
		.pUserData       = nullptr // optional (user data)
	};

	// create instance info (with debug info)
	const vk::instance_info create {
		.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext                   = &debug_info,
		.flags                   = CREATE_FLAGS,
		.pApplicationInfo        = &app_info,
		.enabledLayerCount       = self::validation_layers().size(),
		.ppEnabledLayerNames     = self::validation_layers().data(),
		.enabledExtensionCount   = static_cast<::uint32_t>(extensions.size()),
		.ppEnabledExtensionNames = extensions.data(),
	};

	#else

	// create instance info (without debug info)
	const vk::instance_info create {
		.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext                   = nullptr,
		.flags                   = CREATE_FLAGS,
		.pApplicationInfo        = &app_info,
		.enabledLayerCount       = 0,
		.ppEnabledLayerNames     = nullptr,
		.enabledExtensionCount   = static_cast<::uint32_t>(extensions.size()),
		.ppEnabledExtensionNames = extensions.data()
	};

	#endif


	// create instance
	_instance = vk::make_unique(create);


	// create debug messenger
	#ifdef ENGINE_VL_DEBUG
	_messenger = vk::create(_instance, debug_info);
	#endif

	//self::extension_properties();
}

/* destructor */
vulkan::instance::~instance(void) noexcept {
#if defined(ENGINE_VL_DEBUG)
	vk::destroy(_messenger, _instance);
#endif
}


// -- private static methods --------------------------------------------------

/* extension properties */
auto vulkan::instance::extension_properties(void) -> vk::vector<vk::extension_properties> {
	return vk::enumerate_instance_extension_properties();
}

/* layer properties */
#if defined(ENGINE_VL_DEBUG)
auto vulkan::instance::layer_properties(void) -> vk::vector<vk::layer_properties> {
	return vk::enumerate_instance_layer_properties();
}
#endif

/* callback */
#if defined(ENGINE_VL_DEBUG)

#include <iostream>

VKAPI_ATTR auto VKAPI_CALL
vulkan::instance::callback(const message_severity severity,
								   const message_type type,
								   const callback_data* cdata,
								   void*) -> vk::bool32 {
	switch (severity) {
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			std::cerr << "\x1b[7;35m verbose: ";
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			std::cerr << "\x1b[7;36m info: ";
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			std::cerr << "\x1b[7;32m warning: ";
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			std::cerr << "\x1b[7;31m error: ";
			break;
		default:
			break;
	}

	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
		std::cerr << "[general] \x1b[0m\r\n";

	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
		std::cerr << "[validation] \x1b[0m\r\n";

	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
		std::cerr << "[performance] \x1b[0m\r\n";

	std::cerr << cdata->pMessage << std::endl << std::endl;

	return VK_FALSE;
}

#endif
