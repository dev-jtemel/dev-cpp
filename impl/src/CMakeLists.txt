add_library(devcpp_log
  log/Journal.cpp
)

target_link_libraries(devcpp_log
  PRIVATE
    pthread
)

add_executable(devcpp
  main.cpp
)

target_link_libraries(devcpp
  PRIVATE
    devcpp_log
)