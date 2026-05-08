include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


include(CheckCXXSourceCompiles)


macro(constellation_supports_sanitizers)
  # Emscripten doesn't support sanitizers
  if(EMSCRIPTEN)
    set(SUPPORTS_UBSAN OFF)
    set(SUPPORTS_ASAN OFF)
  elseif((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)

    message(STATUS "Sanity checking UndefinedBehaviorSanitizer, it should be supported on this platform")
    set(TEST_PROGRAM "int main() { return 0; }")

    # Check if UndefinedBehaviorSanitizer works at link time
    set(CMAKE_REQUIRED_FLAGS "-fsanitize=undefined")
    set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=undefined")
    check_cxx_source_compiles("${TEST_PROGRAM}" HAS_UBSAN_LINK_SUPPORT)

    if(HAS_UBSAN_LINK_SUPPORT)
      message(STATUS "UndefinedBehaviorSanitizer is supported at both compile and link time.")
      set(SUPPORTS_UBSAN ON)
    else()
      message(WARNING "UndefinedBehaviorSanitizer is NOT supported at link time.")
      set(SUPPORTS_UBSAN OFF)
    endif()
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    if (NOT WIN32)
      message(STATUS "Sanity checking AddressSanitizer, it should be supported on this platform")
      set(TEST_PROGRAM "int main() { return 0; }")

      # Check if AddressSanitizer works at link time
      set(CMAKE_REQUIRED_FLAGS "-fsanitize=address")
      set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=address")
      check_cxx_source_compiles("${TEST_PROGRAM}" HAS_ASAN_LINK_SUPPORT)

      if(HAS_ASAN_LINK_SUPPORT)
        message(STATUS "AddressSanitizer is supported at both compile and link time.")
        set(SUPPORTS_ASAN ON)
      else()
        message(WARNING "AddressSanitizer is NOT supported at link time.")
        set(SUPPORTS_ASAN OFF)
      endif()
    else()
      set(SUPPORTS_ASAN ON)
    endif()
  endif()
endmacro()

macro(constellation_setup_options)
  option(constellation_ENABLE_HARDENING "Enable hardening" ON)
  option(constellation_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    constellation_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    constellation_ENABLE_HARDENING
    OFF)

  constellation_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR constellation_PACKAGING_MAINTAINER_MODE)
    option(constellation_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(constellation_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(constellation_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(constellation_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(constellation_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(constellation_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(constellation_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(constellation_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(constellation_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(constellation_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(constellation_ENABLE_PCH "Enable precompiled headers" OFF)
    option(constellation_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(constellation_ENABLE_IPO "Enable IPO/LTO" ON)
    option(constellation_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(constellation_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(constellation_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(constellation_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(constellation_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(constellation_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(constellation_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(constellation_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(constellation_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(constellation_ENABLE_PCH "Enable precompiled headers" OFF)
    option(constellation_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      constellation_ENABLE_IPO
      constellation_WARNINGS_AS_ERRORS
      constellation_ENABLE_SANITIZER_ADDRESS
      constellation_ENABLE_SANITIZER_LEAK
      constellation_ENABLE_SANITIZER_UNDEFINED
      constellation_ENABLE_SANITIZER_THREAD
      constellation_ENABLE_SANITIZER_MEMORY
      constellation_ENABLE_UNITY_BUILD
      constellation_ENABLE_CLANG_TIDY
      constellation_ENABLE_CPPCHECK
      constellation_ENABLE_COVERAGE
      constellation_ENABLE_PCH
      constellation_ENABLE_CACHE)
  endif()

  constellation_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (constellation_ENABLE_SANITIZER_ADDRESS OR constellation_ENABLE_SANITIZER_THREAD OR constellation_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(constellation_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(constellation_global_options)
  if(constellation_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    constellation_enable_ipo()
  endif()

  constellation_supports_sanitizers()

  if(constellation_ENABLE_HARDENING AND constellation_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR constellation_ENABLE_SANITIZER_UNDEFINED
       OR constellation_ENABLE_SANITIZER_ADDRESS
       OR constellation_ENABLE_SANITIZER_THREAD
       OR constellation_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${constellation_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${constellation_ENABLE_SANITIZER_UNDEFINED}")
    constellation_enable_hardening(constellation_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(constellation_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(constellation_warnings INTERFACE)
  add_library(constellation_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  constellation_set_project_warnings(
    constellation_warnings
    ${constellation_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  include(cmake/Linker.cmake)
  # Must configure each target with linker options, we're avoiding setting it globally for now

  if(NOT EMSCRIPTEN)
    include(cmake/Sanitizers.cmake)
    constellation_enable_sanitizers(
      constellation_options
      ${constellation_ENABLE_SANITIZER_ADDRESS}
      ${constellation_ENABLE_SANITIZER_LEAK}
      ${constellation_ENABLE_SANITIZER_UNDEFINED}
      ${constellation_ENABLE_SANITIZER_THREAD}
      ${constellation_ENABLE_SANITIZER_MEMORY})
  endif()

  set_target_properties(constellation_options PROPERTIES UNITY_BUILD ${constellation_ENABLE_UNITY_BUILD})

  if(constellation_ENABLE_PCH)
    target_precompile_headers(
      constellation_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(constellation_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    constellation_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(constellation_ENABLE_CLANG_TIDY)
    constellation_enable_clang_tidy(constellation_options ${constellation_WARNINGS_AS_ERRORS})
  endif()

  if(constellation_ENABLE_CPPCHECK)
    constellation_enable_cppcheck(${constellation_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(constellation_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    constellation_enable_coverage(constellation_options)
  endif()

  if(constellation_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(constellation_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(constellation_ENABLE_HARDENING AND NOT constellation_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR constellation_ENABLE_SANITIZER_UNDEFINED
       OR constellation_ENABLE_SANITIZER_ADDRESS
       OR constellation_ENABLE_SANITIZER_THREAD
       OR constellation_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    constellation_enable_hardening(constellation_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
