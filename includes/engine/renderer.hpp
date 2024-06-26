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

#ifndef ENGINE_RENDERER_HEADER
#define ENGINE_RENDERER_HEADER

#include <vulkan/vulkan.h>

//#include "engine/vertex/basic_vertex.hpp"

#include "engine/vulkan/swapchain.hpp"
#include "engine/vulkan/semaphore.hpp"
#include "engine/vulkan/command_pool.hpp"
#include "engine/vulkan/pipeline.hpp"
#include "engine/vulkan/commands.hpp"
#include "engine/vulkan/queue.hpp"
#include "engine/glfw/events.hpp"
#include "engine/glfw/window.hpp"

#include "shader_library.hpp"

//#include "vulkan/global/instance.hpp"



// -- E N G I N E  N A M E S P A C E ------------------------------------------

namespace engine {


	// -- R E N D E R E R -----------------------------------------------------

	class renderer final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = engine::renderer;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			renderer(void);

			/* deleted copy constructor */
			renderer(const self&) = delete;

			/* deleted move constructor */
			renderer(self&&) noexcept = delete;

			/* destructor */
			~renderer(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) noexcept -> self& = delete;


			// -- public methods ----------------------------------------------

			/* draw frame */
			auto draw_frame(void) -> void;

			/* launch */
			auto launch(void) -> void;


		private:

			// -- private members ---------------------------------------------

			/* window */
			glfw::window _window;

			/* gflw events */
			glfw::events _events;

			/* surface */
			vulkan::surface _surface;

			/* device */
			vulkan::device _device;

			/* queue */
			vulkan::queue _queue;

			/* swapchain */
			vulkan::swapchain _swapchain;

			/* command pool */
			vulkan::command_pool<vk::void_bit> _pool;

			/* command buffers */
			vulkan::commands<vulkan::primary> _cmds;

			/* image available semaphore */
			vulkan::semaphore _image_available;

			/* render finished semaphore */
			vulkan::semaphore _render_finished;

			/* pipeline */
			vulkan::pipeline _pipeline;
			/* shader library */
			//shader_library _shaders;


	}; // class renderer

} // namespace engine

#endif // ENGINE_RENDERER_HEADER
