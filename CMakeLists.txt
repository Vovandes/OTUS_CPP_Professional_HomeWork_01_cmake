cmake_minimum_required(VERSION 3.23)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VERSION})

option(WITH_GTEST "Whether to build Google test" ON)

configure_file(version.hpp.in version.hpp)

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)

set_target_properties(helloworld_cli helloworld PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(helloworld_cli PRIVATE
    helloworld
)

# if(WITH_BOOST_TEST)
#     enable_testing()
#     find_package(Boost COMPONENTS unit_test_framework REQUIRED)
#     add_executable(btest_version btest_version.cpp)
#     set_target_properties(btest_version PROPERTIES
#         CXX_STANDARD 17
#         CXX_STANDARD_REQUIRED ON
#     )
#     target_link_libraries(btest_version
#         Boost::unit_test_framework
#         helloworld
#     )
#     add_test(Boost_test.test_version btest_version)
# endif()

if(WITH_GTEST)
    find_package(GTest REQUIRED)
    enable_testing()

    add_executable(test_version_gtest test_version_gtest.cpp)

    set_target_properties(test_version_gtest PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(test_version_gtest
	GTest::gtest_main
        helloworld
    )

    gtest_discover_tests(test_version_gtest)
endif()


if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(helloworld_cli PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(helloworld_cli PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)