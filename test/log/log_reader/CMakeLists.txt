set(OUT_PATH ../../../)

add_executable(test_log_reader 
    LogReaderTest.cpp 
    ${OUT_PATH}src/log/log_reader/LogReader.cpp)
target_link_libraries(test_log_reader PRIVATE Catch2::Catch2WithMain)

catch_discover_tests(test_log_reader)