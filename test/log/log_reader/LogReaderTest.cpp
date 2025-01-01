#include "catch2/catch_test_macros.hpp"
#include <log/log_reader/LogReader.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <fstream>

TEST_CASE("Тест LogReaderTest", "[common read file]") {
    std::ofstream out("abacaba", std::ios::out | std::ios::trunc);
    out.write("foo", 3);
    out.close();

    LogReader logReader;
    logReader.ReadFile("abacaba");
    
    const std::vector<uint8_t>& data = logReader.GetData();

    REQUIRE(data == std::vector<uint8_t>{'f', 'o', 'o'});
}

TEST_CASE("Тест LogReaderTest", "[line parsing]") {
    std::ofstream out("abacaba", std::ios::out | std::ios::trunc);
    std::vector<std::string> realLines = 
        {"Send [1:7438967153140868719:4097] [0:0:0] 0x0000577A6A524700 2024-11-19T12:42:38.320735Z",
        "Receive SELF_PING_ACTOR [1:7438967153140868716:4102] 0x0000577A772547F0 2024-11-19T12:42:38.320833Z",
        "Receive SELF_PING_ACTOR [1:7438967153140868719:4097] 0x0000577A6A524700 2024-11-19T12:42:38.320905Z",
        "Send [1:7438967161730804213:4160] [0:0:0] 0x0000577A6FC5F060 2024-11-19T12:42:38.326663Z",
        "Send [1:7438967153140868718:4090] [0:0:0] 0x0000577A7726DB80 2024-11-19T12:42:38.328825Z",
        "Send [1:7438967153140868715:23] [0:0:0] 0x0000577A6A51E4B0 2024-11-19T12:42:38.328904Z",
        "Receive SELF_PING_ACTOR [1:7438967153140868718:4090] 0x0000577A7726DB80 2024-11-19T12:42:38.329045Z",
        "Receive SELF_PING_ACTOR [1:7438967153140868715:23] 0x0000577A6A51E4B0 2024-11-19T12:42:38.329259Z"};

    std::string realLinesAll;
    for (auto line : realLines) {
        realLinesAll += line + '\n';
    }

    out.write(realLinesAll.c_str(), realLinesAll.size());
    out.close();

    LogReader logReader;
    logReader.ReadFile("abacaba");

    const std::vector<std::string_view>& readLines = logReader.GetLogLines();
    REQUIRE(readLines.size() == realLines.size());

    for (size_t lineNum = 0; lineNum < realLines.size(); ++lineNum) {
        REQUIRE(realLines[lineNum] == readLines[lineNum]);
    }
}

TEST_CASE("Тест LogReaderTest", "[line parsing with bad lines]") {
    std::ofstream out("abacaba", std::ios::out | std::ios::trunc);
    std::vector<std::string> realLines = 
        {"Send [1:7438967153140868719:4097] [0:0:0] 0x0000577A6A524700 2024-11-19T12:42:38.320735Z",
        "Receive SELF_PING_ACTOR [1:7438967153140868716:4102] 0x0000577A772547F0 2024-11-19T12:42:38.320833Z",
        "sdfdsfsdfsd",
        "Send [1:7438967161730804213:4160] [0:0:0] 0x0000577A6FC5F060 2024-11-19T12:42:38.326663Z",
        "Send [1:7438967153140868718:4090] [0:0:0] 0x0000577A7726DB80 2024-11-19T12:42:38.328825Z",
        "Send [1:7438967153140868715:23] [0:0:0] 0x0000577A6A51E4B0 2024-11-19T12:42:38.328904Z",
        "Receive SELF_PING_ACTOR [1:7438967153140868718:4090] 0x0000577A7726DB80 2024-11-19T12:42:38.329045Z",
        "Receive SELF_PING_ACTOR [1:7438967153140868715:23] 0x0000577A6A51E4B0 2024-11-19T12:42:38.329259Z"};

    std::string realLinesAll;
    for (auto line : realLines) {
        realLinesAll += line + '\n';
    }

    out.write(realLinesAll.c_str(), realLinesAll.size());
    out.close();

    LogReader logReader;
    logReader.ReadFile("abacaba");

    const std::vector<std::string_view>& readLines = logReader.GetLogLines();
    REQUIRE(readLines.size() == realLines.size() - 1);

    for (size_t lineNum = 0; lineNum < realLines.size(); ++lineNum) {
        if (lineNum == 2) {
            continue;
        }
        REQUIRE(realLines[lineNum] == readLines[lineNum - (lineNum > 2)]);
    }
}

