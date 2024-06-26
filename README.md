# gbenchmark-example

the example of [Google Benchmark](https://github.com/google/benchmark).

## About Google Benchmark

### Resources

- [Repository](https://github.com/google/benchmark?tab=readme-ov-file)

  - [User Guide](https://github.com/google/benchmark/blob/main/docs/user_guide.md)
  - [Additional Documents (/docs)](https://github.com/google/benchmark/tree/main/docs)
  - [Sample Code (/test)](https://github.com/google/benchmark/tree/main/test)

## Install Benchmark

see [/tool/cmake/install_gbenchmark.cmake](/tool/cmake/install_gbenchmark.cmake).

## Running Benchmark

To run the benchmark, compile and link against the benchmark library.
The compiled executable will run all benchmarks by default.

### Options

To list the options, execute the built benchmark with `--help` flag.
[User Guide](https://github.com/google/benchmark/blob/main/docs/user_guide.md) lists most of the options, but some others are in the `/docs` directory.

- Output

  - `--benchmark_format=<console|json|csv>`
  - `--benchmark_out_format=<json|console|csv>`
  - `--benchmark_out=<filename>`
  - `--benchmark_context=<key>=<value>,...`
  - `--benchmark_list_tests={true|false}`
  - `--benchmark_report_aggregates_only={true|false}`
  - `--benchmark_display_aggregates_only={true|false}`
  - `--benchmark_color={auto|true|false}`
  - `--benchmark_counters_tabular={true|false}`
  - `--benchmark_time_unit={ns|us|ms|s}`
  - `--v=<verbosity>`

- Running

  - `--benchmark_filter=<regex>`
  - `--benchmark_min_warmup_time=<min_warmup_time>`
  - `--benchmark_repetitions=<num_repetitions>`
  - `--benchmark_enable_random_interleaving={true|false}`
    - [Random Interleaving](https://github.com/google/benchmark/blob/main/docs/random_interleaving.md)
  - `--benchmark_min_time=<integer>xOR<float>s`
  - `--benchmark_perf_counters=<counter>,...`
    - [User-Requested Performance Counters](https://github.com/google/benchmark/blob/main/docs/perf_counters.md)

### Result Comparision

See [Additional Tooling Documentation](https://github.com/google/benchmark/blob/main/docs/tools.md)

## About the template

A template for C++ projects using CMake.
This repository includes settings for the following tools:

- [CMake](https://cmake.org/)
- [Google Test](https://github.com/google/googletest)
- [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
- [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
- [VSCode](https://code.visualstudio.com/)
  - [clangd (VSCode Extension)](https://clangd.llvm.org/)
  - [CMake Tools (VSCode Extension)](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
  - [C/C++ Include Guard (VSCode Extension)](https://marketplace.visualstudio.com/items?itemName=akiramiyakoda.cppincludeguard)

## Directoris

The directory structure is based on [The Pitchfork Layout (PFL)](https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs).
(but there are some differences.)

- `include/` : Contains public header files for users.
- `src/` : Contains source files (including private header files and cmake scripts).
- `test/` : Contains test files.
- `examples/` : Contains example files.
- `external/` : Contains source files and libraries from external projects.
- `data/` : Contains not explicitly code files.
- `tool/` : Contains scripts and tools.
  - `cmake/` : Contains CMake scripts.
- `doc/` : Contains documents.

The following directories are not included in the repository, but these names are reserved.

- `build/` : Temporary build directory.
- `install/` : Temporary install directory.

If you want to add submodule projects, you need to add the following directories.

- `lib/` : the root directory of the submodule projects.
- `extra/` : the root directory of the submodule projects with some dependencies.
