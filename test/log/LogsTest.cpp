#include "catch2/catch_test_macros.hpp"
#include <log/log_reader/LogReader.hpp>
#include <log/Logs.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <fstream>

std::vector<std::string> realLines = 
    {"Receive [1:7442281890455496321:7] [1:7442281890455496468:4111] 0x00001423FFDDAC50 2024-11-28T10:54:42.847489Z TABLET_BOOTSTRAPPER",
        "Send [1:7442281890455496306:1] [0:0:0] 0x00001423FFDDAC50 2024-11-28T10:54:42.847509Z",
        "Receive [1:7442281890455496306:1] [0:0:0] 0x00001423FFDF21A0 2024-11-28T10:54:42.847502Z LOG_ACTOR",
        "Send [1:7442281890455496490:4114] [1:7442281890455496490:4114] 0x00001423FFDEFFF0 2024-11-28T10:54:42.847523Z",
        "Receive [1:7442281890455496322:8] [1:7442281890455496469:4111] 0x00001423FFDD8520 2024-11-28T10:54:42.847537Z TABLET_BOOTSTRAPPER",
        "Send [1:7442281890455496306:1] [0:0:0] 0x00001423FFDD8520 2024-11-28T10:54:42.847557Z",
        "Send [1:7442281890455496491:4115] [1:7442281890455496491:4115] 0x00001423FFDF00A0 2024-11-28T10:54:42.847573Z",
        "Receive [1:7442281890455496327:11] [1:7442281890455496470:4111] 0x00001423FFDDB960 2024-11-28T10:54:42.847594Z TABLET_BOOTSTRAPPER",
        "Receive [1:7442281890455496306:1] [0:0:0] 0x00001423FFDDAF10 2024-11-28T10:54:42.847585Z LOG_ACTOR"};

void prepareFile() {
    Logs::Clear();

    std::ofstream out("abacaba", std::ios::out | std::ios::trunc);

    std::string realLinesAll;
    for (auto line : realLines) {
        realLinesAll += line + '\n';
    }

    out.write(realLinesAll.c_str(), realLinesAll.size());
    out.close();
}

TEST_CASE("Тест Logs", "[common]") {
    prepareFile();

    Logs::ReadLogs("abacaba");
    const std::vector<std::string_view>& readLogLines_ = Logs::GetLogLines();

    REQUIRE(readLogLines_.size() == realLines.size());
    for (size_t lineInd = 0; lineInd < readLogLines_.size(); ++lineInd) {
        REQUIRE(realLines[lineInd] == readLogLines_[lineInd]);
    }
}

TEST_CASE("Тест Logs", "[test Receive line parse]") {
    prepareFile();

    Logs::ReadLogs("abacaba");
    const std::vector<Logs::RealLogLine>& realLogLines = Logs::GetRealLogLines();

    Logs::RealLogLine expected = Logs::RealLogLine(
        "Receive",
        "[1:7442281890455496321:7]",
        "[1:7442281890455496468:4111]",
        "0x00001423FFDDAC50",
        "2024-11-28T10:54:42.847489Z",
        "TABLET_BOOTSTRAPPER"
    );

    REQUIRE(realLines.size() == realLogLines.size());

    REQUIRE(expected.type == realLogLines[0].type);
    REQUIRE(expected.from == realLogLines[0].from);
    REQUIRE(expected.to == realLogLines[0].to);
    REQUIRE(expected.message == realLogLines[0].message);
    REQUIRE(expected.time == realLogLines[0].time);
    REQUIRE(expected.actorType == realLogLines[0].actorType);
}

TEST_CASE("Тест Logs", "[test Send line parse]") {
    prepareFile();

    Logs::ReadLogs("abacaba");
    const std::vector<Logs::RealLogLine>& realLogLines = Logs::GetRealLogLines();

    Logs::RealLogLine expected = Logs::RealLogLine(
        "Send",
        "[1:7442281890455496306:1]",
        "[0:0:0]",
        "0x00001423FFDDAC50",
        "2024-11-28T10:54:42.847509Z"
    );

    REQUIRE(realLines.size() == realLogLines.size());

    REQUIRE(expected.type == realLogLines[1].type);
    REQUIRE(expected.from == realLogLines[1].from);
    REQUIRE(expected.to == realLogLines[1].to);
    REQUIRE(expected.message == realLogLines[1].message);
    REQUIRE(expected.time == realLogLines[1].time);
}

TEST_CASE("Тест Logs", "[test Parsed lines]") {
    prepareFile();

    Logs::ReadLogs("abacaba");
    const std::vector<Logs::ParsedLogLine>& parsedLogLines = Logs::GetParsedLogLines();


    Logs::ParsedLogLine expected = Logs::ParsedLogLine(
        "Receive",
        1,
        2,
        "0x00001423FFDDAC50",
        1732777200847489,
        "TABLET_BOOTSTRAPPER"
    );

    REQUIRE(realLines.size() == parsedLogLines.size());

    REQUIRE(expected.type == parsedLogLines[0].type);
    REQUIRE(expected.from == parsedLogLines[0].from);
    REQUIRE(expected.to == parsedLogLines[0].to);
    REQUIRE(expected.message == parsedLogLines[0].message);
    REQUIRE(expected.time == parsedLogLines[0].time);    
    REQUIRE(expected.actorType == parsedLogLines[0].actorType);
}

TEST_CASE("Test Logs", "[test SetMessageToParsedLineInd]") {
    prepareFile();

    Logs::ReadLogs("abacaba");
    const std::map<std::string_view, std::vector<size_t>>& messageToParsedLineInd = Logs::GetMessageToParsedLineInd();

    REQUIRE(messageToParsedLineInd.at("0x00001423FFDDAC50") == std::vector<size_t>{0, 1});
}

TEST_CASE("Test Logs", "[test CreateLogMessages + Normalize]") {
    Logs::Clear();

    std::ofstream out("abacaba", std::ios::out | std::ios::trunc);

    std::string realLinesAll =
        "Send [1:7442281890455496490:4114] [1:7442281890455496490:4114] 0x00001423FFDEFFF0 2024-11-28T10:54:42.847523Z\n"
        "Receive [1:7442281890455496490:4114] [1:7442281890455496490:4114] 0x00001423FFDEFFF0 2024-11-28T10:54:42.947523Z FOO\n"
        "Send [1:7442281890455496490:411] [1:7442281890455496490:4114] 0x00001423FFDEFFF0 2024-11-28T10:54:42.747523Z\n"
        "Receive [1:7442281890455496490:4114] [1:7442281890455496490:411] 0x00001423FFDEFFF0 2024-11-28T10:54:42.947524Z FOO\n";

    out.write(realLinesAll.c_str(), realLinesAll.size());
    out.close();

    Logs::ReadLogs("abacaba");
    const std::vector<Logs::LogMessage>& logMessages = Logs::GetLogMessages();

    std::vector<Logs::LogMessage> expected = {
        Logs::LogMessage(1, 1, 0, 100000, "0x00001423FFDEFFF0")
    };

    REQUIRE(logMessages == expected);
}