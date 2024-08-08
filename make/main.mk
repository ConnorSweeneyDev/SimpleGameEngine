include make/platform.mk
include make/flags.mk
include make/files.mk
include make/clang.mk

build: $(OUTPUT_FILE)
prepare: compile_commands clang-format clangd directories $(RESOURCE_SOURCE_FILE) $(RESOURCE_INCLUDE_FILE)
clean: delete

include make/build.mk
