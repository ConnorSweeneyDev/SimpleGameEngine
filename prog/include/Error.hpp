#include <iostream>
#include <glad/glad.h>

#pragma once

class Error // Stores functions for #define CheckGL(function)
{
    public:
        void ClearAllGLErrors();
        bool CheckGLErrorStatus(const char* functionName, const char* fileName, int line);
};
extern Error error;
