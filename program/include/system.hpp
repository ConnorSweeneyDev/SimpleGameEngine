#pragma once

namespace cse::system
{
  void clear_all_gl_errors();
  void check_gl_error_status(const char *function_name, const char *file_name,
                             const int line_number);

  void sdl_init();
  void glad_init();
  void cleanup();

#define check_gl(function)                                                                         \
  clear_all_gl_errors();                                                                           \
  function;                                                                                        \
  system::check_gl_error_status(#function, __FILE__, __LINE__);
}
