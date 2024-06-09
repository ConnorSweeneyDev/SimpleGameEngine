#pragma once

#include <SDL_events.h>
#include <glad.h>
#include <glm.hpp>

namespace sdl
{
  using Uint8 = uint8_t;
  using Uint32 = uint32_t;
  using Uint64 = uint64_t;
  using Bool = SDL_bool;
  using Rect = SDL_Rect;
  using Window = SDL_Window;
  using Display_mode = SDL_DisplayMode;
  using Event = SDL_Event;
  using Gl_context = SDL_GLContext;
  using Gl_attr = SDL_GLattr;

  const char *SDLCALL get_error(void);
  void set_main_ready(void);
  int init(Uint32 flags);
  int get_num_video_displays(void);
  int get_display_bounds(int display_index, Rect *rect);
  int get_desktop_display_mode(int display_index, Display_mode *mode);
  Window *create_window(const char *title, int x, int y, int w, int h, Uint32 flags);
  void destroy_window(Window *window);
  int set_window_fullscreen(Window *window, Uint32 flags);
  void set_window_bordered(Window *window, Bool bordered);
  void set_window_resizable(Window *window, Bool resizable);
  void set_window_size(Window *window, int w, int h);
  void set_window_position(Window *window, int x, int y);
  void get_window_position(Window *window, int *x, int *y);
  int get_window_display_index(Window *window);
  void quit(void);
  int poll_event(Event *event);
  const Uint8 *get_keyboard_state(int *num_keys);
  Uint64 get_ticks_64(void);
  Gl_context gl_create_context(Window *window);
  int gl_set_attribute(Gl_attr attr, int value);
  int gl_set_swap_interval(int interval);
  void gl_swap_window(Window *window);
  void gl_delete_context(Gl_context context);
  void *SDLCALL gl_get_proc_address(const char *proc);
}

namespace glad
{
  using Glad_load_proc = GLADloadproc;

  GLAPI int load_gl_loader(Glad_load_proc load);
}

namespace gl
{
  using Void = GLvoid;
  using Int = GLint;
  using Uint = GLuint;
  using Float = GLfloat;
  using Size_i = GLsizei;
  using Enum = GLenum;

  Enum get_error(void);
  void enable(Enum cap);
  void disable(Enum cap);
  void blend_func(Enum sfactor, Enum dfactor);
  void viewport(Int x, Int y, Size_i width, Size_i height);
  void clear_color(Float red, Float green, Float blue, Float alpha);
  void clear(Enum mask);
  Uint create_shader(Enum type);
  void shader_source(Uint shader, int count, const char **string, const int *length);
  void compile_shader(Uint shader);
  void get_shaderiv(Uint shader, Enum pname, int *params);
  void get_shader_info_log(Uint shader, int max_length, int *length, char *info_log);
  void delete_shader(Uint shader);
  Uint create_program();
  void attach_shader(Uint program, Uint shader);
  void link_program(Uint program);
  void validate_program(Uint program);
  void gen_vertex_arrays(Size_i n, Uint *arrays);
  void bind_vertex_array(Uint array);
  void gen_buffers(Size_i n, Uint *buffers);
  void bind_buffer(Enum target, Uint buffer);
  void buffer_data(Enum target, Size_i size, const void *data, Enum usage);
  void vertex_attrib_pointer(Uint index, int size, Enum type, bool normalized, Size_i stride,
                             const void *pointer);
  void enable_vertex_attrib_array(Uint index);
  void gen_textures(Size_i n, Uint *textures);
  void bind_texture(Enum target, Uint texture);
  void tex_parameter_i(Enum target, Enum name, int param);
  void tex_image_2d(Enum target, Int level, Int internal_format, Size_i width, Size_i height,
                    Int border, Enum format, Enum type, const Void *pixels);
  void use_program(Uint program);
  Int get_uniform_location(Uint program, const char *name);
  void uniform_matrix_4fv(Int location, Size_i count, bool transpose, const Float *value);
  void draw_elements(Enum mode, Size_i count, Enum type, const Void *indices);
  void delete_vertex_arrays(Size_i n, const Uint *arrays);
  void disable_vertex_attrib_array(Uint index);
  void delete_buffers(Size_i n, const Uint *buffers);
  void delete_textures(Size_i n, const Uint *textures);
  void delete_program(Uint program);
}

namespace glm
{
  using Vec3 = vec3;
  using Mat4 = mat4;

  Mat4 look_at(Vec3 eye, Vec3 center, Vec3 up);
}

namespace stbi
{
  void set_flip_vertically_on_load(int flag);
  unsigned char *load(const char *filename, int *width, int *height, int *channels,
                      int desired_channels);
  void image_free(void *data);
}
