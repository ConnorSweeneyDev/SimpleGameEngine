directories:
	@if [ ! -d $(BINARY_DIRECTORY) ]; then mkdir -p $(BINARY_DIRECTORY); echo "WRT | $(BINARY_DIRECTORY)"; fi
	@if [ ! -d $(BINARY_OBJECT_DIRECTORY) ]; then mkdir -p $(BINARY_OBJECT_DIRECTORY); echo "WRT | $(BINARY_OBJECT_DIRECTORY)"; fi
	@if [ ! -d $(BINARY_PLATFORM_DIRECTORY) ]; then mkdir -p $(BINARY_PLATFORM_DIRECTORY); echo "WRT | $(BINARY_PLATFORM_DIRECTORY)"; fi

$(RESOURCE_SOURCE_FILES): $(ASSET_SOURCE_FILES)
	@./$(RESOURCE_GENERATOR) $(GENERATOR_PREFIXES) $^ $@
	@echo "GEN | $@"

$(BINARY_OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@echo "CXX | $@"
$(BINARY_OBJECT_DIRECTORY)/%.o: $(EXTERNAL_SOURCE_DIRECTORY)/%.c
	@$(CC) $(CC_FLAGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@echo "CCO | $@"
-include $(DEPENDENCY_FILES)

$(OUTPUT_FILE): $(OBJECT_FILES)
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) $^ $(LIBRARIES) -o $@
	@echo "LNK | $@"

delete:
	@if [ -d $(BINARY_OBJECT_DIRECTORY) ]; then rm -r $(BINARY_OBJECT_DIRECTORY); echo "DEL | $(BINARY_OBJECT_DIRECTORY)"; fi
	@if [ -f $(OUTPUT_FILE) ]; then rm -r $(OUTPUT_FILE); echo "DEL | $(OUTPUT_FILE)"; fi
	@if [ $(CLEAN_RESOURCE_SOURCE_FILES) = 1 ]; then for file in $(RESOURCE_SOURCE_FILES); do if [ -f $$file ]; then rm -r $$file; echo "DEL | $$file"; fi; done; fi
