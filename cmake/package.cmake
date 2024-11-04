find_package(Threads REQUIRED)
find_package(OpenMP REQUIRED)
find_package(mimalloc CONFIG REQUIRED)

if(BEAST_HTTP_STATIC_EXTERNAL_LIB)
    set(Boost_USE_STATIC_LIBS ON)
endif()
find_package(Boost 1.81.0 REQUIRED)
