find_package(CURL REQUIRED)

include(FetchGit)

FetchGit(magic_enum "https://github.com/Neargye/magic_enum.git")
FetchGit(fmt "https://github.com/fmtlib/fmt.git")

add_library("${PROJECT_NAME}" requests.cpp request.cpp response.cpp error.cpp)
target_include_directories("${PROJECT_NAME}" PRIVATE ${CURL_INCLUDE_DIRS})
target_link_directories("${PROJECT_NAME}" PRIVATE ${CURL_LIBRARY_DIRS})
target_link_libraries("${PROJECT_NAME}" "${PROJECT_NAME}_HEADERS" ${CURL_LIBRARIES} magic_enum fmt)