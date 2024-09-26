directories:
	@if [ ! -d $(BINARY_DIRECTORY) ]; then mkdir -p $(BINARY_DIRECTORY); $(ECHO) "Write | $(BINARY_DIRECTORY)"; fi
	@if [ ! -d $(OBJECT_DIRECTORY) ]; then mkdir -p $(OBJECT_DIRECTORY); $(ECHO) "Write | $(OBJECT_DIRECTORY)"; fi
	@if [ ! -d $(TARGET_PLATFORM_DIRECTORY) ]; then mkdir -p $(TARGET_PLATFORM_DIRECTORY); $(ECHO) "Write | $(TARGET_PLATFORM_DIRECTORY)"; fi

$(RESOURCE_SOURCE_FILES): $(SHADER_SOURCE_FILES)
	@./$(RESOURCE_LOADER) _resource $^ $@
	@$(ECHO) "Load  | $@"

$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(EXTERNAL_SOURCE_DIRECTORY)/%.c
	@$(CC) $(CC_FLAGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CC    | $@"
-include $(DEPENDENCY_FILES)

$(OUTPUT_FILE): $(OBJECT_FILES)
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) $^ $(LIBRARIES) -o $@
	@$(ECHO) "Link  | $^ -> $@"

delete:
	@if [ -d $(OBJECT_DIRECTORY) ]; then rm -r $(OBJECT_DIRECTORY); $(ECHO) "RM    | $(OBJECT_DIRECTORY)"; fi
	@if [ -f $(OUTPUT_FILE) ]; then rm -r $(OUTPUT_FILE); $(ECHO) "RM    | $(OUTPUT_FILE)"; fi
	@if [ $(DELETE_RESOURCE_SOURCE_FILES) = 1 ]; then for file in $(RESOURCE_SOURCE_FILES); do if [ -f $$file ]; then rm -r $$file; $(ECHO) "RM    | $$file"; fi; done; fi
