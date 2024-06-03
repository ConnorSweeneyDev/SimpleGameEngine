#pragma once

namespace cse::platform
{
  void clear_all_gl_errors();
  void check_gl_error_status(const char *function_name, const char *file_name,
                             const int line_number);

  void sdl_init();
  void glad_init();

#define check_gl(function)                                                                         \
  clear_all_gl_errors();                                                                           \
  function;                                                                                        \
  platform::check_gl_error_status(#function, __FILE__, __LINE__);
}
