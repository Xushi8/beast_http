add_library(beast_http_http "")

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.c src/*.cpp)
file(GLOB_RECURSE header CONFIGURE_DEPENDS include/*.h include/*.hpp)

target_sources(beast_http_http
PRIVATE
    ${sources}
PUBLIC
    ${header}
)

target_include_directories(beast_http_http 
PUBLIC
./include
)

if(BUILD_SHARED_LIBS OR BEAST_HTTP_INSTALL_STATIC_LIB)
    install(TARGETS beast_http_http)
endif()

install(DIRECTORY ./include/
        DESTINATION include)
