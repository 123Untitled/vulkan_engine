/*****************************************************************************/
/*                                                                           */
/*          ░  ░░░░  ░  ░░░░  ░  ░░░░░░░  ░░░░  ░░      ░░   ░░░  ░          */
/*          ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒  ▒    ▒▒  ▒          */
/*          ▓▓  ▓▓  ▓▓  ▓▓▓▓  ▓  ▓▓▓▓▓▓▓     ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓  ▓          */
/*          ███    ███  ████  █  ███████  ███  ██        █  ██    █          */
/*          ████  █████      ██        █  ████  █  ████  █  ███   █          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef ENGINE_VK_UTILS_HEADER
#define ENGINE_VK_UTILS_HEADER

#include "engine/vk/typedefs.hpp"
#include "engine/vk/exception.hpp"

#include <xns/forward.hpp>
#include <xns/string_literal.hpp>


// -- V K  N A M E S P A C E --------------------------------------------------

namespace vk {


	/* try execute */
	template <decltype(sizeof(0)) ___size, typename ___function, typename... ___params>
	inline auto try_execute(___function&& ___func, const char (&___msg)[___size], ___params&&... ___args) -> void {
		// get return type
		using ret_type = decltype(___func(xns::forward<___params>(___args)...));
		// assert return type is vk::result
		static_assert(xns::is_same<ret_type, vk::result>, "invalid return type.");
		// execute function
		if (auto ___result = ___func(xns::forward<___params>(___args)...); ___result != VK_SUCCESS)
			throw vk::exception{___msg, ___result};
	}

	/* try execute */
	template <xns::basic_string_literal ___msg, typename ___function, typename... ___params>
	inline auto try_execute(___function&& ___func, ___params&&... ___args) -> void {

		// get return type
		using ret_type = decltype(___func(xns::forward<___params>(___args)...));

		// assert return type is vk::result
		static_assert(xns::is_same<ret_type, vk::result>, "invalid return type.");

		// execute function
		if (auto ___result = ___func(xns::forward<___params>(___args)...); ___result != VK_SUCCESS)
			throw vk::exception{___msg.data(), ___result};
	}


} // namespace vk

#endif // ENGINE_VK_UTILS_HEADER
