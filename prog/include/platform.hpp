#pragma once

namespace cse
{
    class Platform
    {
        public:
            void display_open_gl_version_info() const;
            void clear_all_gl_errors();
            void check_gl_error_status(const char* function_name, const char* file_name, int line) const;

            void sdl_init();
            void glad_init();
    };
    extern Platform platform;
}

#define check_gl(function) cse::platform.clear_all_gl_errors(); function; cse::platform.check_gl_error_status(#function, __FILE__, __LINE__);
