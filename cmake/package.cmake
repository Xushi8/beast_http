find_package(Threads REQUIRED)

if(BEAST_HTTP_STATIC_EXTERNAL_LIB)
    set(Boost_USE_STATIC_LIBS ON)
endif()
find_package(Boost 1.81.0 REQUIRED COMPONENTS headers)
