cmake_minimum_required(VERSION 3.21)

# Enable exporting of compile commands for external tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the project name and the programming language
project(nugget LANGUAGES C)

# Set the C standard to C17
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

# Enable colorized output during build
set(CMAKE_COLOR_MAKEFILE ON)

# Directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

# Function to find and set Clang and clang-tidy
function(find_and_set_tools)
    find_program(CLANG_TIDY "/opt/homebrew/opt/llvm/bin/clang-tidy")
    if(CLANG_TIDY)
        set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY}")
    else()
        message(WARNING "clang-tidy not found")
    endif()

    find_program(CLANG_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
    if(CLANG_COMPILER)
        set(CMAKE_C_COMPILER ${CLANG_COMPILER})
    else()
        message(WARNING "Clang compiler not found")
    endif()
endfunction()

find_and_set_tools()

# Common compile options
set(COMMON_COMPILE_OPTIONS
    -Wall                # Enable all common warnings
    -Wextra              # Enable additional warnings
    -Wpedantic           # Enable strict ISO C and ISO C++ standards conformance
    -Wconversion         # Enable warnings for implicit type conversions
    -Wformat             # Enable warnings for format string vulnerabilities
    -Wshadow             # Enable warnings for shadowed variables
    -Wstrict-aliasing    # Enable warnings for potential aliasing issues
    -Wstrict-overflow    # Enable warnings for potential overflow issues
    -Wvla                # Enable warnings for variable-length arrays
)

# Debug build type-specific compile options
set(DEBUG_COMPILE_OPTIONS
    -g                        # Enable debug information
    -fsanitize=undefined      # Enable undefined behavior sanitizer for runtime checks
    -fstack-protector-all     # Enable stack protector for detecting stack overflows
    -fno-omit-frame-pointer   # Ensure frame pointer is not omitted
    -fno-optimize-sibling-calls # Disable tail call optimizations
    -fprofile-instr-generate  # Enable generation of instrumentation for profiling
    -fcoverage-mapping        # Enable coverage mapping for code coverage analysis
)

# Debug build type-specific linker flags
set(DEBUG_LINKER_OPTIONS
    -fsanitize=undefined
    -fprofile-instr-generate  # Enable generation of instrumentation for profiling
    -fcoverage-mapping        # Enable coverage mapping for code coverage analysis
)

# Release build type-specific compile options
set(RELEASE_COMPILE_OPTIONS
    -O3                   # Optimization level 3
    -DNDEBUG              # Disable debug information and assertions
    -flto                 # Link-Time Optimization
    -fprofile-generate    # Enable Profile-Guided Optimization (first compile)
    -march=native         # Optimize for the host architecture
    -funroll-loops        # Unroll loops where possible
    -finline-functions    # Inline functions where possible
)

# Release build type-specific linker flags
set(RELEASE_LINKER_OPTIONS
    -flto                 # Link-Time Optimization
    -fprofile-generate    # Enable Profile-Guided Optimization (first compile)
    -Wl,-O3               # Optimization level 3 for linker
)

# Function to apply compile and link options based on build type
function(apply_build_type_options target)
    target_compile_options(${target} PRIVATE
        ${COMMON_COMPILE_OPTIONS}
        $<$<CONFIG:Debug>:${DEBUG_COMPILE_OPTIONS}>
        $<$<CONFIG:Release>:${RELEASE_COMPILE_OPTIONS}>
    )
    target_link_options(${target} PRIVATE
        $<$<CONFIG:Debug>:${DEBUG_LINKER_OPTIONS}>
        $<$<CONFIG:Release>:${RELEASE_LINKER_OPTIONS}>
    )
endfunction()

# Add the source files excluding main.c
file(GLOB SRC_FILES ${SRC_DIR}/*.c)
list(REMOVE_ITEM SRC_FILES ${SRC_DIR}/main.c)

# Generate the nugget library
add_library(nugget_lib ${SRC_FILES})
target_include_directories(nugget_lib PRIVATE ${INCLUDE_DIR})
apply_build_type_options(nugget_lib)

# Create the executable target with main.c
add_executable(nugget ${SRC_DIR}/main.c)
target_link_libraries(nugget PRIVATE nugget_lib)
target_include_directories(nugget PRIVATE ${INCLUDE_DIR})
apply_build_type_options(nugget)

# Ensure specific C standard features
target_compile_features(nugget PRIVATE c_std_17)

if(ENABLE_TESTS)
    enable_testing()

    # Add tests
    file(GLOB TEST_FILES ${TEST_DIR}/*.c)
    foreach(test_file ${TEST_FILES})
        get_filename_component(test_name ${test_file} NAME_WE)
        add_executable(${test_name} ${test_file})
        target_link_libraries(${test_name} PRIVATE nugget_lib)
        target_include_directories(${test_name} PRIVATE ${INCLUDE_DIR})
        apply_build_type_options(${test_name})
        add_test(NAME ${test_name} COMMAND ${test_name})
    endforeach()
endif()
