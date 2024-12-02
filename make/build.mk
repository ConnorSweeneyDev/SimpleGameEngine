directories:
	@if [ ! -d $(BINARY_DIRECTORY) ]; then mkdir -p $(BINARY_DIRECTORY); $(ECHO) "WRITE | $(BINARY_DIRECTORY)"; fi
	@if [ ! -d $(BINARY_OBJECT_DIRECTORY) ]; then mkdir -p $(BINARY_OBJECT_DIRECTORY); $(ECHO) "WRITE | $(BINARY_OBJECT_DIRECTORY)"; fi
	@if [ ! -d $(BINARY_PLATFORM_DIRECTORY) ]; then mkdir -p $(BINARY_PLATFORM_DIRECTORY); $(ECHO) "WRITE | $(BINARY_PLATFORM_DIRECTORY)"; fi

$(RESOURCE_SOURCE_FILES): $(ASSET_SOURCE_FILES)
	@./$(RESOURCE_GENERATOR) $(GENERATOR_PREFIXES) $^ $@
	@$(ECHO) "GEN   | $@"

$(BINARY_OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(BINARY_OBJECT_DIRECTORY)/%.o: $(EXTERNAL_SOURCE_DIRECTORY)/%.c
	@$(CC) $(CC_FLAGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CC    | $@"
-include $(DEPENDENCY_FILES)

$(OUTPUT_FILE): $(OBJECT_FILES)
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) $^ $(LIBRARIES) -o $@
	@$(ECHO) "LINK  | $@"

delete:
	@if [ -d $(BINARY_OBJECT_DIRECTORY) ]; then rm -r $(BINARY_OBJECT_DIRECTORY); $(ECHO) "RM    | $(BINARY_OBJECT_DIRECTORY)"; fi
	@if [ -f $(OUTPUT_FILE) ]; then rm -r $(OUTPUT_FILE); $(ECHO) "RM    | $(OUTPUT_FILE)"; fi
	@if [ $(CLEAN_RESOURCE_SOURCE_FILES) = 1 ]; then for file in $(RESOURCE_SOURCE_FILES); do if [ -f $$file ]; then rm -r $$file; $(ECHO) "RM    | $$file"; fi; done; fi
