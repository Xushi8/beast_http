add_subdirectory(common)
add_subdirectory(http)

set(BEAST_HTTP_TARGETS
    main
)

foreach(name ${BEAST_HTTP_TARGETS})
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name}
    PUBLIC
        # src
        beast_http_common
        beast_http_http

        # package
        Threads::Threads

        Boost::headers

        # external
    )

endforeach(name ${BEAST_HTTP_TARGETS})

install(TARGETS ${BEAST_HTTP_TARGETS})
