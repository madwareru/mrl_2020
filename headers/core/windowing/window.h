#pragma once

#include <variant>
#include <vector>
#include <core/types.h>

namespace core::render {
   struct SOASpriteRGB;
}

struct GLFWwindow;

namespace core::windowing {

typedef void (* GLFWkeyfun)(GLFWwindow*,int,int,int,int);
typedef void (* GLFWcursorposfun)(GLFWwindow*,double,double);
typedef void (* GLFWmousebuttonfun)(GLFWwindow*,int,int,int);

typedef void (*render_proc)(core::render::SOASpriteRGB& back_buffer);
typedef void (*update_proc)(double delta_time);
typedef bool (*init_proc)(void);

struct WindowSize {
    core::types::u16 width;
    core::types::u16 height;
};

struct FramebufferSize {
    core::types::u16 width;
    core::types::u16 height;
};

enum class sreen_mode : bool {fullscreen = true, windowed = false};

struct WindowCreationParams {
    const char* window_name;
    WindowSize window_size;
    FramebufferSize framebuffer_size;
    sreen_mode mode;
};

struct LifetimeProcHolder {
    init_proc   init_proc_addr;
    update_proc update_proc_addr;
    render_proc render_proc_addr;
    LifetimeProcHolder(
        init_proc   init_proc_addr_p,
        update_proc update_proc_addr_p,
        render_proc render_proc_addr_p
    );
};

struct KeyCallbackHolder{
    GLFWkeyfun fun;
};
struct CursorPosCallbackHolder{
    GLFWcursorposfun fun;
};
struct MouseButtonCallbackHolder{
    GLFWmousebuttonfun fun;
};

#define INIT_WINDOW(window_params)                  \
    glfwCreateWindow(                               \
        window_params.window_size.width,            \
        window_params.window_size.height,           \
        window_params.window_name,                  \
        static_cast<bool>(window_params.mode) \
            ? glfwGetPrimaryMonitor()               \
            : nullptr,                              \
        nullptr                                     \
    )

bool start_main_loop(
    GLFWwindow* glfw_window,
    const WindowCreationParams& window_params,
    const LifetimeProcHolder& lifetime_procs,
    const std::vector<
        std::variant<
            KeyCallbackHolder,
            CursorPosCallbackHolder,
            MouseButtonCallbackHolder>
        >& eventCallbacks
    );
}