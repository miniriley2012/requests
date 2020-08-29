include(BuildTest)

add_build_test(get get.cpp)
target_link_libraries(get "${PROJECT_NAME}")