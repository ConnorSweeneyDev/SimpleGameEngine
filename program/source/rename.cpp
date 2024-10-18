#include "rename.hpp"
#include "SDL.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_main.h"
#include "SDL_platform.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include "ext/matrix_transform.hpp"
#include "glad.h"
#include "stb_image.h"

namespace sdl
{
  const char *SDLCALL get_error(void) { return SDL_GetError(); }
  void set_main_ready(void) { SDL_SetMainReady(); }
  int init(Uint32 flags) { return SDL_Init(flags); }
  int get_num_video_displays(void) { return SDL_GetNumVideoDisplays(); }
  int get_display_bounds(int display_index, Rect *rect)
  {
    return SDL_GetDisplayBounds(display_index, rect);
  }
  int get_desktop_display_mode(int display_index, Display_mode *mode)
  {
    return SDL_GetDesktopDisplayMode(display_index, mode);
  }
  Window *create_window(const char *title, int x, int y, int w, int h, Uint32 flags)
  {
    return SDL_CreateWindow(title, x, y, w, h, flags);
  }
  void destroy_window(Window *window) { SDL_DestroyWindow(window); }
  int set_window_fullscreen(Window *window, Uint32 flags)
  {
    return SDL_SetWindowFullscreen(window, flags);
  }
  void set_window_bordered(Window *window, Bool bordered)
  {
    SDL_SetWindowBordered(window, bordered);
  }
  void set_window_resizable(Window *window, Bool resizable)
  {
    SDL_SetWindowResizable(window, resizable);
  }
  void set_window_size(Window *window, int w, int h) { SDL_SetWindowSize(window, w, h); }
  void set_window_position(Window *window, int x, int y) { SDL_SetWindowPosition(window, x, y); }
  void get_window_position(Window *window, int *x, int *y) { SDL_GetWindowPosition(window, x, y); }
  int get_window_display_index(Window *window) { return SDL_GetWindowDisplayIndex(window); }
  void quit(void) { SDL_Quit(); }
  int poll_event(Event *event) { return SDL_PollEvent(event); }
  const Uint8 *get_keyboard_state(int *num_keys) { return SDL_GetKeyboardState(num_keys); }
  Uint64 get_ticks_64(void) { return SDL_GetTicks(); }
  Gl_context gl_create_context(Window *window) { return SDL_GL_CreateContext(window); }
  int gl_set_attribute(Gl_attr attr, int value) { return SDL_GL_SetAttribute(attr, value); }
  int gl_set_swap_interval(int interval) { return SDL_GL_SetSwapInterval(interval); }
  void gl_swap_window(Window *window) { SDL_GL_SwapWindow(window); }
  void gl_delete_context(Gl_context context) { SDL_GL_DeleteContext(context); }
  void *SDLCALL gl_get_proc_address(const char *proc) { return SDL_GL_GetProcAddress(proc); }
}

namespace glad
{
  GLAPI int load_gl_loader(Glad_load_proc load) { return gladLoadGLLoader(load); }
}

namespace gl
{
  Enum get_error(void) { return glGetError(); }
  void enable(Enum cap) { glEnable(cap); }
  void disable(Enum cap) { glDisable(cap); }
  void blend_func(Enum sfactor, Enum dfactor) { glBlendFunc(sfactor, dfactor); }
  void viewport(Int x, Int y, Sizei width, Sizei height) { glViewport(x, y, width, height); }
  void clear_color(Float red, Float green, Float blue, Float alpha)
  {
    glClearColor(red, green, blue, alpha);
  }
  void clear(Enum mask) { glClear(mask); }
  Uint create_shader(Enum type) { return glCreateShader(type); }
  void shader_source(Uint shader, Sizei count, const Char *const *string, const Int *length)
  {
    glShaderSource(shader, count, string, length);
  }
  void compile_shader(Uint shader) { glCompileShader(shader); }
  void get_shaderiv(Uint shader, Enum pname, Int *params) { glGetShaderiv(shader, pname, params); }
  void get_shader_info_log(Uint shader, Sizei max_length, Sizei *length, Char *info_log)
  {
    glGetShaderInfoLog(shader, max_length, length, info_log);
  }
  void delete_shader(Uint shader) { glDeleteShader(shader); }
  Uint create_program() { return glCreateProgram(); }
  void attach_shader(Uint program, Uint shader) { glAttachShader(program, shader); }
  void link_program(Uint program) { glLinkProgram(program); }
  void validate_program(Uint program) { glValidateProgram(program); }
  void gen_vertex_arrays(Sizei n, Uint *arrays) { glGenVertexArrays(n, arrays); }
  void bind_vertex_array(Uint array) { glBindVertexArray(array); }
  void gen_buffers(Sizei n, Uint *buffers) { glGenBuffers(n, buffers); }
  void bind_buffer(Enum target, Uint buffer) { glBindBuffer(target, buffer); }
  void buffer_data(Enum target, Sizei size, const void *data, Enum usage)
  {
    glBufferData(target, size, data, usage);
  }
  void buffer_sub_data(Enum target, Intptr offset, Sizei_ptr size, const void *data)
  {
    glBufferSubData(target, offset, size, data);
  }
  void vertex_attrib_pointer(Uint index, Int size, Enum type, Boolean normalized, Sizei stride,
                             const void *pointer)
  {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  }
  void enable_vertex_attrib_array(Uint index) { glEnableVertexAttribArray(index); }
  void gen_textures(Sizei n, Uint *textures) { glGenTextures(n, textures); }
  void bind_texture(Enum target, Uint texture) { glBindTexture(target, texture); }
  void tex_parameter_i(Enum target, Enum name, Int param) { glTexParameteri(target, name, param); }
  void tex_image_2d(Enum target, Int level, Int internal_format, Sizei width, Sizei height,
                    Int border, Enum format, Enum type, const Void *pixels)
  {
    glTexImage2D(target, level, internal_format, width, height, border, format, type, pixels);
  }
  void use_program(Uint program) { glUseProgram(program); }
  Int get_uniform_location(Uint program, const Char *name)
  {
    return glGetUniformLocation(program, name);
  }
  void uniform_matrix_4fv(Int location, Sizei count, Boolean transpose, const Float *value)
  {
    glUniformMatrix4fv(location, count, transpose, value);
  }
  void draw_elements(Enum mode, Sizei count, Enum type, const Void *indices)
  {
    glDrawElements(mode, count, type, indices);
  }
  void delete_vertex_arrays(Sizei n, const Uint *arrays) { glDeleteVertexArrays(n, arrays); }
  void disable_vertex_attrib_array(Uint index) { glDisableVertexAttribArray(index); }
  void delete_buffers(Sizei n, const Uint *buffers) { glDeleteBuffers(n, buffers); }
  void delete_textures(Sizei n, const Uint *textures) { glDeleteTextures(n, textures); }
  void delete_program(Uint program) { glDeleteProgram(program); }
}

namespace glm
{
  Mat4 look_at(Vec3 eye, Vec3 center, Vec3 up) { return lookAt(eye, center, up); }
}

namespace stbi
{
  void set_flip_vertically_on_load(int flag) { stbi_set_flip_vertically_on_load(flag); }
  unsigned char *load(const char *filename, int *width, int *height, int *channels,
                      int desired_channels)
  {
    return stbi_load(filename, width, height, channels, desired_channels);
  }
  void image_free(void *data) { stbi_image_free(data); }
}
