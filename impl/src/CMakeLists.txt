add_library(devcpp_log
  log/journal.cpp
)

target_link_libraries(devcpp_log
  PRIVATE
    pthread
)