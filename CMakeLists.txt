cmake_minimum_required(VERSION 3.15)
project(ctp_data_get)

set(CXX_STANDARD 17)

set(PROJECT_HEADER_DIR ${PROJECT_SOURCE_DIR}/include)
set(EXE_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIB_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CTP_HEADER_DIR ${PROJECT_SOURCE_DIR}/CTP_HEADER)

add_subdirectory(Test)
add_subdirectory(src)
