set(LIBRARY_SOURCES "null.cpp")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/parte_1.h" "${CMAKE_CURRENT_SOURCE_DIR}/parte_2.h" "${CMAKE_CURRENT_SOURCE_DIR}/parte_3.h" "${CMAKE_CURRENT_SOURCE_DIR}/parte_4.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibPart" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibPart" PUBLIC ${LIBRARY_INCLUDES})

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibPart"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibPart"
        ENABLE
        ON)
endif()
