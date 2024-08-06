# Nugget

![build](https://github.com/wonbyte/nugget/actions/workflows/build.yml/badge.svg)

<p align="left">
  <img width="400" height="400" src="">
</p>

## Building

### Prerequisites
To build Nugget, ensure that the following tools are installed on your system:
- CMake (version 3.30 or higher)
- Ninja (version 1.12 or higher)
- Clang (version 15.0 or higher)

### Building in Debug Mode
By default, Nugget is built in debug mode:

```bash
make
```

This command generates the build files, compiles the source code, and produces the debug executable file.

### Building in Release Mode

To build Nugget in release mode for blazingly fast speed, use the following command:
```bash
make BUILD_TYPE=Release
```

This command generates the build files, compiles the source code with optimizations, and produces the release executable file.

### Clean Up
To clean the build files and artifacts, use the following command:
```bash
make clean
```

This command cleans the `build` directory and all its contents.

## Running

### Running the Build
To run Nugget, use the following command:

```bash
make run
```

### Running in Release mode
To run Nugget in release mode make sure to first [build the release executable](#building-in-release-mode).

Run the following command:

```bash
./build/nugget
```

## Additional Commands

### Running Tests

To run the tests for Nugget, use the following command:

```bash
make test
```

### Documentation

To generate the documentation for Nugget, use the following command:

```bash
make docs
```

This command generates the documentation using Doxygen and stores it in the `docs` directory.

### Code Formatting

To format the source code according to the project's style guidelines, use the following command:

```bash
make format
```

This command formats the source code using clang-format.
