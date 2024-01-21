#ifndef ENGINE_OVERLOADS_HPP
#define ENGINE_OVERLOADS_HPP

#if defined(ENGINE_VL_DEBUG)

#include "vk_typedefs.hpp"
#include <iostream>


/* physical device type */
inline auto operator<<(std::ostream& os, const vk::physical_device_type& type) -> std::ostream& {
	switch (type) {
		case VK_PHYSICAL_DEVICE_TYPE_OTHER:
			os << "other";
			break;
		case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
			os << "integrated gpu";
			break;
		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
			os << "discrete gpu";
			break;
		case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
			os << "virtual gpu";
			break;
		case VK_PHYSICAL_DEVICE_TYPE_CPU:
			os << "cpu";
			break;
		default:
			os << "unknown";
			break;
	}
	return os;
}

/* physical device features */
inline auto operator<<(std::ostream& os, const vk::physical_device_features& features) -> std::ostream& {

	os << "                     robustBufferAccess: " << features.robustBufferAccess << "\n";
	os << "                    fullDrawIndexUint32: " << features.fullDrawIndexUint32 << "\n";
	os << "                         imageCubeArray: " << features.imageCubeArray << "\n";
	os << "                       independentBlend: " << features.independentBlend << "\n";
	os << "                         geometryShader: " << features.geometryShader << "\n";
	os << "                     tessellationShader: " << features.tessellationShader << "\n";
	os << "                      sampleRateShading: " << features.sampleRateShading << "\n";
	os << "                           dualSrcBlend: " << features.dualSrcBlend << "\n";
	os << "                                logicOp: " << features.logicOp << "\n";
	os << "                      multiDrawIndirect: " << features.multiDrawIndirect << "\n";
	os << "              drawIndirectFirstInstance: " << features.drawIndirectFirstInstance << "\n";
	os << "                             depthClamp: " << features.depthClamp << "\n";
	os << "                         depthBiasClamp: " << features.depthBiasClamp << "\n";
	os << "                       fillModeNonSolid: " << features.fillModeNonSolid << "\n";
	os << "                            depthBounds: " << features.depthBounds << "\n";
	os << "                              wideLines: " << features.wideLines << "\n";
	os << "                            largePoints: " << features.largePoints << "\n";
	os << "                             alphaToOne: " << features.alphaToOne << "\n";
	os << "                          multiViewport: " << features.multiViewport << "\n";
	os << "                      samplerAnisotropy: " << features.samplerAnisotropy << "\n";
	os << "                 textureCompressionETC2: " << features.textureCompressionETC2 << "\n";
	os << "             textureCompressionASTC_LDR: " << features.textureCompressionASTC_LDR << "\n";
	os << "                   textureCompressionBC: " << features.textureCompressionBC << "\n";
	os << "                  occlusionQueryPrecise: " << features.occlusionQueryPrecise << "\n";
	os << "                pipelineStatisticsQuery: " << features.pipelineStatisticsQuery << "\n";
	os << "         vertexPipelineStoresAndAtomics: " << features.vertexPipelineStoresAndAtomics << "\n";
	os << "               fragmentStoresAndAtomics: " << features.fragmentStoresAndAtomics << "\n";
	os << " shaderTessellationAndGeometryPointSize: " << features.shaderTessellationAndGeometryPointSize << "\n";
	os << "              shaderImageGatherExtended: " << features.shaderImageGatherExtended << "\n";
	os << "      shaderStorageImageExtendedFormats: " << features.shaderStorageImageExtendedFormats << "\n";
	os << "          shaderStorageImageMultisample: " << features.shaderStorageImageMultisample << "\n";
	os << "    shaderStorageImageReadWithoutFormat: " << features.shaderStorageImageReadWithoutFormat << "\n";
	os << "   shaderStorageImageWriteWithoutFormat: " << features.shaderStorageImageWriteWithoutFormat << "\n";
	os << "shaderUniformBufferArrayDynamicIndexing: " << features.shaderUniformBufferArrayDynamicIndexing << "\n";
	os << " shaderSampledImageArrayDynamicIndexing: " << features.shaderSampledImageArrayDynamicIndexing << "\n";
	os << "shaderStorageBufferArrayDynamicIndexing: " << features.shaderStorageBufferArrayDynamicIndexing << "\n";
	os << " shaderStorageImageArrayDynamicIndexing: " << features.shaderStorageImageArrayDynamicIndexing << "\n";
	os << "                     shaderClipDistance: " << features.shaderClipDistance << "\n";
	os << "                     shaderCullDistance: " << features.shaderCullDistance << "\n";
	os << "                          shaderFloat64: " << features.shaderFloat64 << "\n";
	os << "                            shaderInt64: " << features.shaderInt64 << "\n";
	os << "                            shaderInt16: " << features.shaderInt16 << "\n";
	os << "                shaderResourceResidency: " << features.shaderResourceResidency << "\n";
	os << "                   shaderResourceMinLod: " << features.shaderResourceMinLod << "\n";
	os << "                          sparseBinding: " << features.sparseBinding << "\n";
	os << "                  sparseResidencyBuffer: " << features.sparseResidencyBuffer << "\n";
	os << "                 sparseResidencyImage2D: " << features.sparseResidencyImage2D << "\n";
	os << "                 sparseResidencyImage3D: " << features.sparseResidencyImage3D << "\n";
	os << "                sparseResidency2Samples: " << features.sparseResidency2Samples << "\n";
	os << "                sparseResidency4Samples: " << features.sparseResidency4Samples << "\n";
	os << "                sparseResidency8Samples: " << features.sparseResidency8Samples << "\n";
	os << "               sparseResidency16Samples: " << features.sparseResidency16Samples << "\n";
	os << "                 sparseResidencyAliased: " << features.sparseResidencyAliased << "\n";
	os << "                variableMultisampleRate: " << features.variableMultisampleRate << "\n";
	os << "                       inheritedQueries: " << features.inheritedQueries << "\n";

	return os;
}


/* queue family flags */
inline auto operator<<(std::ostream& os, const vk::queue_flags& flag) -> std::ostream& {

	if (flag & VK_QUEUE_GRAPHICS_BIT) {
		os << "graphics ";
	}

	if (flag & VK_QUEUE_COMPUTE_BIT) {
		os << "compute ";
	}

	if (flag & VK_QUEUE_TRANSFER_BIT) {
		os << "transfer ";
	}

	if (flag & VK_QUEUE_SPARSE_BINDING_BIT) {
		os << "sparse binding ";
	}

	if (flag & VK_QUEUE_PROTECTED_BIT) {
		os << "protected ";
	}

	if (flag & VK_QUEUE_VIDEO_DECODE_BIT_KHR) {
		os << "video decode ";
	}

	#ifdef VK_ENABLE_BETA_EXTENSIONS
	if (flag & VK_QUEUE_VIDEO_ENCODE_BIT_KHR) {
		os << "video encode ";
	}
	#endif

	if (flag & VK_QUEUE_OPTICAL_FLOW_BIT_NV) {
		os << "optical flow ";
	}

	return os;
}








#endif // ENGINE_VL_DEBUG


#endif // ENGINE_OVERLOADS_HPP