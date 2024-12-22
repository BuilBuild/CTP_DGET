
include_directories(${PROJECT_HEADER_DIR})

link_directories(${LIB_PATH})
link_libraries(CTPApi thostmduserapi_se)

set(EXECUTABLE_OUTPUT_PATH ${EXE_PATH})

add_executable(src_main main.cpp)