#pragma once

#include "engine/arctic_types.h"

// Time in mileseconds
using Time = arctic::Ui64;

using EventId = arctic::Ui64;
using ActorId = arctic::Ui64;

struct Event {
  Time start;
  Time end;
  ActorId from;
  ActorId to;
  EventId id;
};