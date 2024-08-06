# Variables
BUILD_DIR := build
DOCS_DIR := docs
NUGGET := $(BUILD_DIR)/nugget
CMAKE := cmake
DOXYGEN := doxygen
CLANG_FORMAT := /opt/homebrew/opt/llvm/bin/clang-format
BUILD_TYPE ?= Debug
SOURCES := $(wildcard src/*.c) $(wildcard include/*.h)
TEST_SOURCES := $(wildcard test/*.c)
.DEFAULT_GOAL := all
.PHONY: all build clean docs format run test coverage help

# Default target that builds and runs the project
all: build

# Build the project
build: clean $(NUGGET)

# Build the executable using Ninja
$(NUGGET): $(BUILD_DIR)/build.ninja $(SOURCES)
	@$(CMAKE) --build $(BUILD_DIR) --config $(BUILD_TYPE) --parallel

# Generate the build.ninja file using CMake
$(BUILD_DIR)/build.ninja: CMakeLists.txt $(SOURCES)
	@$(CMAKE) -S . -B $(BUILD_DIR) -GNinja -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

# Clean all build files and directories
clean:
	@$(RM) -r $(BUILD_DIR) $(DOCS_DIR) default.profraw default_*.profraw

# Generate documentation by running Doxygen after cleaning the documentation directory
docs:
	@$(DOXYGEN) Doxyfile

# Build and run the executable
run: clean build
	@$(NUGGET)

# Format the source code using clang-format
format:
	@for file in $(SOURCES); do \
		$(CLANG_FORMAT) -style=file -assume-filename=$(shell pwd)/.clang-format -i $$file; \
	done

# Run tests using ctest
test: clean
	@$(CMAKE) -S . -B $(BUILD_DIR) -GNinja -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DENABLE_TESTS=ON
	@$(CMAKE) --build $(BUILD_DIR) --config $(BUILD_TYPE) --parallel
	@cd $(BUILD_DIR) && ctest --output-on-failure --verbose

# Display help for Makefile targets
help:
	@echo "Makefile targets:"
	@echo "  all      - Build the project"
	@echo "  build    - Build the project"
	@echo "  clean    - Clean all build and documentation files"
	@echo "  docs     - Generate documentation"
	@echo "  format   - Format the source code"
	@echo "  run      - Build and run the executable"
	@echo "  test     - Run tests using ctest"
	@echo "  help     - Display this help message"
