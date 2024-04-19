#pragma once

#include <memory>

#define check_gl(function) system_util.clear_all_gl_errors(); function; system_util.check_gl_error_status(#function, __FILE__, __LINE__);

class SystemUtil
{
    public:
        void get_open_gl_version_info() const;
        template <typename Type> std::shared_ptr<Type> get_object_by_name(const std::string& name) const;
 
        void clear_all_gl_errors();
        void check_gl_error_status(const char* functionName, const char* fileName, int line) const;

        void sdl_init();
        void glad_init();
        void sdl_cleanup();
};
extern SystemUtil system_util;

#include "system_util.tpl.hpp"
