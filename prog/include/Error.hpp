#include <iostream>
#include <glad/glad.h>

#pragma once

class Error
{
    public:
        void ClearAllGLErrors();
        bool CheckGLErrorStatus(const char* functionName, const char* fileName, int line);
};
extern Error error;
