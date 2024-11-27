include(Catch)

add_executable("UnitTests" "tests.cc")
target_link_libraries("UnitTests" PUBLIC "LibPart")
target_link_libraries("UnitTests" PRIVATE Catch2::Catch2WithMain)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "UnitTests"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

catch_discover_tests("UnitTests")
