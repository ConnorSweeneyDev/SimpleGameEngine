include make/platform.mk
include make/flags.mk
include make/files.mk

build: $(OUTPUT_FILE)
prepare: directories $(RESOURCE_SOURCE_FILES)
utility: compile_commands clang-format clangd
clean: delete

include make/build.mk
include make/utility.mk
