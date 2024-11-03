CXX := g++
CC := gcc
ifeq ($(DEBUG), 1)
  CXX_FLAGS := -ggdb3 -MD -MP -O2 -std=c++17 -DDEBUG -D_FORTIFY_SOURCE=2 -fno-common -fstack-protector-strong
  CC_FLAGS := -ggdb3 -MD -MP -O2 -DDEBUG -D_FORTIFY_SOURCE=2 -fno-common -fstack-protector-strong
else
  CXX_FLAGS := -s -O3 -std=c++17 -DNDEBUG -fno-common -fstack-protector-strong -ffunction-sections -fdata-sections -flto=auto -Wl,--gc-sections
  CC_FLAGS := -s -O3 -DNDEBUG -fno-common -fstack-protector-strong -ffunction-sections -fdata-sections -flto=auto -Wl,--gc-sections
endif

WARNINGS := -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wundef -Wclobbered -Wdeprecated -Wmultichar -Wuninitialized -Wunreachable-code -Wstrict-aliasing -Wreturn-type -Wtype-limits -Wformat-security -Wpointer-arith -Wmaybe-uninitialized -Wempty-body -Wdouble-promotion -Wcast-qual -Wcast-align -Wfloat-equal -Wlogical-op -Wduplicated-cond -Wshift-overflow=2 -Wformat=2
INCLUDES := -Iprogram/include
ifeq ($(UNAME), Windows)
  SYSTEM_INCLUDES := -isystemexternal/include -isystemexternal/include/glad -isystemexternal/include/glm -isystemexternal/include/khr -isystemexternal/include/sdl2/windows
  LIBRARIES := -Lexternal/library/sdl2/windows -static -Wl,-Bstatic -lgcc -lstdc++ -lssp -lwinpthread -Wl,-Bdynamic -lSDL2
else ifeq ($(UNAME), Linux)
  SYSTEM_INCLUDES := -isystemexternal/include -isystemexternal/include/glad -isystemexternal/include/glm -isystemexternal/include/khr -isystemexternal/include/sdl2/linux
  LIBRARIES := -Lexternal/library/sdl2/linux -static-libgcc -static-libstdc++ -ldl -lpthread -lSDL2 -Wl,-rpath,'$$ORIGIN'
endif
