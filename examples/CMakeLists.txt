#the exmaple cmake 
set(HEADERS example1.h example.h example2.h)
set(SOURCES example1.cpp example2.cpp)

add_library(network-example STATIC ${SOURCES} ${HEADERS})



#set_target_properties()

#target_link_libraries(network-example )
