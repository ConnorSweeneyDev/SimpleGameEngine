directories:
	@if [ ! -d $(OBJECT_DIRECTORY) ]; then mkdir -p $(OBJECT_DIRECTORY); $(ECHO) "Write | $(OBJECT_DIRECTORY)"; fi

$(RESOURCE_FILES): $(SHADER_FILES)
	@./$(RESOURCE_LOADER) _resource $^ $@
	@$(ECHO) "Load  | $@"

$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.hpp $(PROGRAM_INCLUDE_DIRECTORY)/%.tpl.hpp $(PROGRAM_INCLUDE_DIRECTORY)/%.inl.hpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.hpp $(PROGRAM_INCLUDE_DIRECTORY)/%.tpl.hpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.hpp $(PROGRAM_INCLUDE_DIRECTORY)/%.inl.hpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.tpl.hpp $(PROGRAM_INCLUDE_DIRECTORY)/%.inl.hpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.hpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.tpl.hpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.inl.hpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(EXTERNAL_SOURCE_DIRECTORY)/%.c | directories
	@$(CC) $(CC_FLAGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CC    | $@"
-include $(DEPENDENCY_FILES)

$(OUTPUT_FILE): $(OBJECT_FILES) | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) $^ $(LIBRARIES) -o $@
	@$(ECHO) "Link  | $^ -> $@"

delete:
	@if [ -d $(OBJECT_DIRECTORY) ]; then rm -r $(OBJECT_DIRECTORY); $(ECHO) "RM    | $(OBJECT_DIRECTORY)"; fi
	@if [ -f $(OUTPUT_FILE) ]; then rm -r $(OUTPUT_FILE); $(ECHO) "RM    | $(OUTPUT_FILE)"; fi
