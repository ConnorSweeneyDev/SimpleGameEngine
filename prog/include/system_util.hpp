#pragma once

#include <memory>

#define check_gl(function) system_util.clear_all_gl_errors(); function; system_util.check_gl_error_status(#function, __FILE__, __LINE__);

class System_util
{
    public:
        template <typename Type> std::shared_ptr<Type> get_object_by_name(const std::string& name) const;
 
        void display_open_gl_version_info() const;
        void clear_all_gl_errors();
        void check_gl_error_status(const char* function_name, const char* file_name, int line) const;

        void sdl_init();
        void glad_init();
        void sdl_cleanup();
};
extern System_util system_util;

#include "system_util.tpl.hpp"
