add_subdirectory(log_reader)

set(OUT_PATH ../../)

add_executable(test_logs
    LogsTest.cpp 
    ${OUT_PATH}src/log/Logs.cpp
    ${OUT_PATH}src/log/log_reader/LogReader.cpp)
target_link_libraries(test_logs PRIVATE Catch2::Catch2WithMain)

catch_discover_tests(test_logs)