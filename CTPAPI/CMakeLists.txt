include_directories(${PROJECT_HEADER_DIR})
message(${PROJECT_HEADER_DIR})

# 搜索源文件
aux_source_directory(./ SRC)
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})

add_library(CTPApi STATIC ${SRC})