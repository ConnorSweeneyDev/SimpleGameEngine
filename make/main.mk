include make/platform.mk
include make/flags.mk
include make/files.mk
include make/utility.mk

build: $(OUTPUT_FILE)
prepare: directories $(RESOURCE_SOURCE_FILE) $(RESOURCE_INCLUDE_FILE)
utility: compile_commands clang-format clangd
clean: delete

include make/build.mk
