file(GLOB TEST_SOURCES "./unit/*.cpp")

include_directories(.)

add_executable(devcpp_tests
  main.cpp
  ${TEST_SOURCES}
)

target_compile_definitions(devcpp_tests PRIVATE TEST)

target_link_libraries(devcpp_tests
  PUBLIC
    devcpp_log

  PRIVATE
    gmock
    gtest
)