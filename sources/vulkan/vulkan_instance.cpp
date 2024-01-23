#include "vulkan_instance.hpp"
#include "vulkan_physical_device.hpp"
#include "vulkan_surface.hpp"


// -- public static methods ---------------------------------------------------

/* shared */
//auto vulkan::instance::shared(void) -> self& {
//	static self instance{};
//	return instance;
//}

/* pick physical device */
auto vulkan::instance::pick_physical_device(const vulkan::surface& surface) -> vulkan::physical_device {

	// get physical devices
	auto devices = self::physical_devices();

	// loop over devices
	for (const auto& device : devices) {
		//&& features.geometryShader;
		//	device_type(properties);
		//device_features(features);

		//auto capabilities = device.surface_capabilities(surface);

		auto properties = device.properties();
		auto features   = device.features();

		if (device.supports_swapchain()          == true
		&&  device.have_surface_formats(surface) == true
		&&  device.have_present_modes(surface)   == true
		&& (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
		 || properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)) {
			return device;
		}
	}
	// no suitable physical device found
	throw engine::exception{"failed to find suitable physical device"};
}


// -- public lifecycle --------------------------------------------------------

/* default constructor (debug) */
#if defined(ENGINE_VL_DEBUG)
vulkan::instance::instance(void)
//: _instance{VK_NULL_HANDLE}, _messenger{VK_NULL_HANDLE} {
: _instance{}, _messenger{} {
//: _messenger{}, _instance{} {
//: _instance{}, _messenger{VK_NULL_HANDLE} {
#else
/* default constructor */
vulkan::instance::instance(void)
: _instance{} {
//: _instance{VK_NULL_HANDLE} {
#endif

	// create application info
	const vk::application_info app_info{
		.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext              = nullptr,
		.pApplicationName   = "application",
		.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0),
		.pEngineName        = "engine",
		.engineVersion      = VK_MAKE_API_VERSION(0, 1, 0, 0),
		.apiVersion         = VK_API_VERSION_1_0
	};

	// get required extensions
	auto extensions = glfw::system::vulkan_required_extensions();


	// create instance info
	vk::instance_info create{};

	create.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

	#if defined(ENGINE_VL_DEBUG)

	static constexpr xns::array<const char*, 1> layers = {
		"VK_LAYER_KHRONOS_validation",
		//"VK_LAYER_LUNARG_api_dump",
		//"VK_LAYER_KHRONOS_profiles",
		//"VK_LAYER_KHRONOS_synchronization2",
		//"VK_LAYER_KHRONOS_shader_object"
	};


	// get messenger info
	const vk::debug_utils_messenger_info debug_info{
		.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
		.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
						 | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
						 | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
		.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
						 | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
						 | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
		.pfnUserCallback = self::callback,
		.pUserData       = nullptr // optional (user data)
	};


	create.pNext                   = &debug_info;
	create.enabledLayerCount       = static_cast<vk::u32>(layers.size());
	create.ppEnabledLayerNames     = layers.data();
	#else
	create.pNext                   = nullptr;
	create.enabledLayerCount       = 0;
	create.ppEnabledLayerNames     = nullptr;
	#endif

	#if defined(ENGINE_OS_MACOS)
	create.flags                   = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
	#else
	create.flags                   = 0;
	#endif

	create.pApplicationInfo        = &app_info;
	create.enabledExtensionCount   = static_cast<::uint32_t>(extensions.size());
	create.ppEnabledExtensionNames = extensions.data();


	// create shared instance
	_instance = vk::make_shared(create);

	// create debug messenger
	#ifdef ENGINE_VL_DEBUG
	_messenger = vk::make_managed(vk::create(_instance, debug_info),
									  _instance);
	#endif

	//self::extension_properties();
}


// -- public conversion operators ---------------------------------------------

/* vk::instance conversion operator */
vulkan::instance::operator const vk::instance&(void) const noexcept {
	return _instance;
}

/* vk::shared<vk::instance> conversion operator */
vulkan::instance::operator const vk::shared<vk::instance>&(void) const noexcept {
	return _instance;
}


// -- public accessors --------------------------------------------------------

/* physical devices */
auto vulkan::instance::physical_devices(void) -> vk::vector<vulkan::physical_device> {

	// get shared instance
	//const auto& instance = self::shared();

	const auto devices = vk::enumerate_physical_devices(_instance);

	vk::vector<vulkan::physical_device> result{};
	result.reserve(devices.size());

	for (const auto& device : devices)
		result.emplace_back(device);

	return result;
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
VKAPI_ATTR VkBool32 VKAPI_CALL vulkan::instance::callback(const message_severity severity,
														  const message_type type,
														  const callback_data* cdata,
														  void*) {
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
		std::cerr << "[general] \x1b[0m" << std::endl;

	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
		std::cerr << "[validation] \x1b[0m" << std::endl;

	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
		std::cerr << "[performance] \x1b[0m" << std::endl;

	std::cerr << cdata->pMessage << std::endl << std::endl;

	return VK_FALSE;
}
#endif



