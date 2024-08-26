CXX := g++
CC := gcc
ifeq ($(DEBUG), 1)
  CXX_FLAGS := -g3 -MD -MP -O2 -std=c++17 -DDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong
  CC_FLAGS := -g3 -MD -MP -O2 -DDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong
else
  CXX_FLAGS := -s -O3 -std=c++17 -DNDEBUG -fstack-protector-strong -ffunction-sections -fdata-sections -flto=auto -Wl,--gc-sections
  CC_FLAGS := -s -O3 -DNDEBUG -fstack-protector-strong -ffunction-sections -fdata-sections -flto=auto -Wl,--gc-sections
endif

WARNINGS := -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wundef -Wdouble-promotion -fno-common -Wcast-qual -Wcast-align -Wfloat-equal -Wlogical-op -Wduplicated-cond -Wshift-overflow=2 -Wformat=2
INCLUDES := -Iprogram/include
ifeq ($(UNAME), Windows)
  SYSTEM_INCLUDES := -isystemexternal/include -isystemexternal/include/glad -isystemexternal/include/glm -isystemexternal/include/khr -isystemexternal/include/sdl2/windows -isystemexternal/include/stb
  LIBRARIES := -Lexternal/library/sdl2/windows -static -Wl,-Bstatic -lgcc -lstdc++ -lssp -lwinpthread -Wl,-Bdynamic -lSDL2
else ifeq ($(UNAME), Linux)
  SYSTEM_INCLUDES := -isystemexternal/include -isystemexternal/include/glad -isystemexternal/include/glm -isystemexternal/include/khr -isystemexternal/include/sdl2/linux -isystemexternal/include/stb
  LIBRARIES := -Lexternal/library/sdl2/linux -static-libgcc -static-libstdc++ -ldl -lpthread -lSDL2 -Wl,-rpath,'$$ORIGIN'
endif
