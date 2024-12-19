#include "Logs.hpp"

#include <map>
#include <set>

std::vector<std::string_view> Logs::logLines_ = {};
std::map<ActorId, std::string_view> Logs::actorNumIdToRealActorId_ = {};
std::map<std::string_view, ActorId> Logs::realActorIdToActorNumId_ = {};
std::vector<Logs::RealLogLine> Logs::realLogLines_ = {};
std::vector<Logs::ParsedLogLine> Logs::parsedLogLines_ = {};
std::map<std::string_view, std::vector<std::size_t>> Logs::messageToParsedLineInd_ = {};
std::vector<Logs::LogMessage> Logs::logMessages_ = {};
std::map<std::string_view, std::vector<ActorId>> Logs::actorTypeToActorId_ = {};
std::map<ActorId, std::string_view> Logs::actorIdToActorType_ = {};
std::vector<Logs::NewDieLogLine> Logs::newDieLogLines_ = {};
std::map<ActorId, std::pair<Time, Time>> Logs::lifeTime_ = {};
ActorId Logs::maxActorId_ = 0;
Time Logs::oldMinTime_ = 0;

std::ostream& operator<<(std::ostream& os, const Logs::LogMessage& lm) {
  return os << "[" 
    << lm.to << ","
    << lm.from << ","
    << lm.start << ","
    << lm.end << ","
    << lm.message
    << "]";
}