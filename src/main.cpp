#include <cstdint>
#include <cstddef>
#include <variant>
#include <memory>

#include <util/defer_action.h>
#include <util/macro_shared.h>

#include <core/render/soa_sprite_rgb.h>
#include <core/render/standart_blit_policy.h>
#include <core/windowing/window.h>
#include <core/loaders/png_loader.h>
#include <GLFW/glfw3.h>

namespace {
    std::shared_ptr<core::render::SOASpriteRGB> grass_sprite;

    void global_init() {
        grass_sprite = core::loaders::load_sprite_from_png_24("grassCenter.png");
        
    }

    void global_update(double delta_time) {
        
    }

    void global_render(core::render::SOASpriteRGB& back_buffer) {
        for(std::int32_t j = 0; j < 12; ++j) {
            for(std::int32_t i = 0; i < 19; ++i) {
                core::render::blit_sprite(*grass_sprite, back_buffer, i * 70, j * 70);
            }
        }
    }

    void key_callback(GLFWwindow* glfw_window, int par0, int par1, int par2, int par3) {

    }

    void mouse_cursor_position_callback(GLFWwindow* glfw_window, double par0, double par1) {
        
    }

    void mouse_button_callback(GLFWwindow* glfw_window, int par0, int par1, int par2) {
        
    }

    void glfw_error_hooker(int code, const char* description) {
        LOG_ERROR("GLFW_ERROR: [" << code << "]: " << description);
    }
}

int main(int argc, char** argv) {
    core::windowing::WindowCreationParams window_params {
        "mrl_2020", // title
        640, // width
        480, // height
        false, // fullscreen
        0x07, 0x02, 0x13 // clear color
    };

    core::windowing::LifetimeProcHolder lifetime_procs {
        global_init,
        global_update,
        global_render
    };

    using callback_holder = std::variant<
        core::windowing::KeyCallbackHolder,
        core::windowing::CursorPosCallbackHolder,
        core::windowing::MouseButtonCallbackHolder>;

    std::vector<callback_holder> event_callbacks;
    event_callbacks.emplace_back(core::windowing::KeyCallbackHolder{key_callback});
    event_callbacks.emplace_back(core::windowing::CursorPosCallbackHolder{mouse_cursor_position_callback});
    event_callbacks.emplace_back(core::windowing::MouseButtonCallbackHolder{mouse_button_callback});

    if(!glfwInit()) {
        LOG_ERROR("Fatal: failed to init glfw");
        return 1;
    }
    glfwSetErrorCallback(glfw_error_hooker);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = INIT_WINDOW(window_params);

    if(!window) {
        LOG_ERROR("Fatal: failed to create a window");
        return 1;
    }

    DEFER([&](){ glfwDestroyWindow(window); })

    if(!core::windowing::start_main_loop(
        window,
        window_params,
        lifetime_procs,
        event_callbacks
    )) {
        LOG_ERROR("Fatal: failed to start main loop");
        return 1;
    }

    return 0;
}
