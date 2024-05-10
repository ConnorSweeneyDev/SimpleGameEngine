#pragma once

namespace cse::platform
{
    void clear_all_gl_errors();
    void check_gl_error_status(const char* function_name, const char* file_name, int line);

    void sdl_init();
    void glad_init();
}

#define check_gl(function) cse::platform::clear_all_gl_errors(); function; cse::platform::check_gl_error_status(#function, __FILE__, __LINE__);
