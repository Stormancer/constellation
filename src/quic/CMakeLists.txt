include(GenerateExportHeader)


add_library(quic peer.cpp)



add_library(constellation::quic ALIAS quic)

target_link_libraries(quic PRIVATE constellation_options constellation_warnings)

target_include_directories(quic ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/main>
                                                        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/backends/${BACKEND}>
                                                        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
                                                       )

if (constellation_BUILD_FUZZ_TESTS)
  target_link_libraries(quic PRIVATE -fsanitize=fuzzer-no-link)
  target_compile_options(quic PRIVATE -fsanitize=fuzzer-no-link)
endif()

target_compile_features(quic PUBLIC cxx_std_${CMAKE_CXX_STANDARD})

constellation_configure_linker(sample_library)

set_target_properties(
  quic
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(quic EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/quic/quic_export.hpp)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(quic PUBLIC SAMPLE_LIBRARY_STATIC_DEFINE)
endif()
