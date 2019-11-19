#CMakeLists.txt
set(SERVER_SOURCES server.cpp)
add_executable(server ${SERVER_SOURCES})

set(CLIENT_SOURCES client.cpp)
add_executable(client ${CLIENT_SOURCES})

#configure_file(example.h.in example.h)
#target_include_directories(example PUBLIC "${PROJECT_BINARY_DIR}")
#message("the source dir: ${PROJECT_SOURCE_DIR}")
#target_include_directories(example ${PROJECT_SOURCE_DIR})
include_directories("${PROJECT_SOURCE_DIR}/examples/")
target_link_libraries(server network-example)
target_link_libraries(client network-example)
