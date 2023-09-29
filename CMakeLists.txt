
cmake_minimum_required (VERSION 3.0)
project (logx)

add_library (logx
    Logging.cc
    LogLayout.cc
    LogAppender.cc
    RecentHistoryAppender.cc
    system_error.cc
  )

target_include_directories (logx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(logx log4cpp)

