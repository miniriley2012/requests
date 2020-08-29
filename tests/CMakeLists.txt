enable_testing()
include(BuildTest)

add_build_test(get get.cpp)
target_link_libraries(get "${PROJECT_NAME}")

add_custom_target(test DEPENDS build_tests_command)