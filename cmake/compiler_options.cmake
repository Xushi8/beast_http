if(WIN32)
    add_compile_options(-finput-charset=utf-8 -fexec-charset=utf-8)
    add_link_options(-finput-charset=utf-8 -fexec-charset=utf-8)

    add_definitions(-DNOMINMAX)
    add_definitions(-DUNICODE)
    add_definitions(-D_UNICODE)
endif()


if(BEAST_HTTP_ENABLE_SSE4)
    add_compile_options(-march=core2)
    add_link_options(-march=core2)
endif()

if(BEAST_HTTP_ENABLE_AVX)
    add_compile_options(-march=sandybridge)
    add_link_options(-march=sandybridge)
endif()

if(BEAST_HTTP_ENABLE_AVX2)
    add_compile_options(-march=haswell)
    add_link_options(-march=haswell)
endif()

if(NOT BEAST_HTTP_AUTHOR)
    add_compile_options(-march=native)
    add_link_options(-march=native)
endif()

add_compile_options(-fdiagnostics-color=always)
add_link_options(-fdiagnostics-color=always)


# warnings
add_compile_options(-Wall -Wextra -pedantic -Wshadow -Wcast-qual -Wfloat-equal -Wredundant-decls -Wundef -Wpointer-arith -Werror=return-type -Wimplicit-fallthrough)
add_link_options(-Wall -Wextra -pedantic -Wshadow -Wcast-qual -Wfloat-equal -Wredundant-decls -Wundef -Wpointer-arith -Werror=return-type -Wimplicit-fallthrough)
add_compile_options(-Wconversion -Wsign-conversion)
add_link_options(-Wconversion -Wsign-conversion)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
    # add_compile_options(-fsanitize=address)
    # add_link_options(-fsanitize=address)
    # add_compile_options(-fsanitize=thread)
    # add_link_options(-fsanitize=thread)

    add_compile_options(-ggdb3 -fno-omit-frame-pointer)
    add_link_options(-ggdb3 -fno-omit-frame-pointer)
endif()

if(BEAST_HTTP_ENABLE_MOLD)
    add_link_options(-fuse-ld=mold)
endif()

if(BEAST_HTTP_STATIC_LIBCXX)
    add_link_options(-static-libstdc++)
endif()
