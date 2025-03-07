if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-D_GLIBCXX_DEBUG)
    add_definitions(-D_GLIBCXX_DEBUG_PEDANTIC)
endif()

add_definitions(-DFMT_HEADER_ONLY)
add_definitions(-DSPDLOG_FMT_EXTERNAL)
add_definitions(-DVCL_NAMESPACE=vectorclass)

if(WIN32)
    add_definitions(-DNOMINMAX)
    add_definitions(-D_USE_MATH_DEFINES)
endif()

if(BUILD_SHARED_LIBS)
    add_definitions(-DBEAST_HTTP_LIBRARY_SHARED)
else()
    add_definitions(-DBEAST_HTTP_LIBRARY_STATIC)
endif()
