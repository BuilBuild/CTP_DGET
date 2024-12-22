cmake_minimum_required(VERSION 3.15)
project(ctp_data_get)

set(CXX_STANDARD 17)

set(PROJECT_HEADER_DIR ${PROJECT_SOURCE_DIR}/include)
list(APPEND PROJECT_HEADER_DIR ${PROJECT_SOURCE_DIR}/CTPAPI)

set(EXE_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIB_PATH ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(Test)
add_subdirectory(CTPAPI)
add_subdirectory(src)
