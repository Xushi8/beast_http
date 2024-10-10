add_subdirectory(common)

# target_link_libraries(common PUBLIC test_lib)


set(BEAST_HTTP_TARGETS
    main
)

foreach(name ${BEAST_HTTP_TARGETS})
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name}
    PUBLIC
        # src
        beast_http_common

        # package
        Threads::Threads
        OpenMP::OpenMP_CXX
        TBB::tbb
        mimalloc


        ${RE2_LIB}

        ${GMP_LIB}
        ${MPFR_LIB}

        ${PQ_LIB}

        # external
    )

endforeach(name ${BEAST_HTTP_TARGETS})

install(TARGETS ${BEAST_HTTP_TARGETS})
