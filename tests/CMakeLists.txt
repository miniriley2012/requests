enable_testing()
include(BuildTest)

add_build_test(get get.cpp)
set_tests_properties(get_test PROPERTIES COMMAND "get https://httpbin.org/status/200")
target_link_libraries(get "${PROJECT_NAME}")

add_custom_target(test DEPENDS build_tests_command)