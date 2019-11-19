#the exmaple cmake 
set(HEADERS example1.h example.h)
set(SOURCES example1.cpp)

add_library(network-example STATIC ${SOURCES} ${HEADERS})



#set_target_properties()

#target_link_libraries(network-example )
