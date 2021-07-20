#ifndef CLOCK_H
#define CLOCK_H

#include "../Debug.h"

#include <windows.h>
#include <iostream>

namespace WG
{

enum class TIME_UNIT : int
{
    SEC = 1,
    MILLI = 1000,
    MICRO = 1000000
};

class Clock
{
    public:
        Clock();
        virtual ~Clock();
        bool Start();
        bool Tick();
        bool TogglePause(bool _pause);
        double GetDeltaTime(TIME_UNIT _unit);
        double GetTotalTime(TIME_UNIT _unit);
        double GetGlobalTime(TIME_UNIT _unit);
        double GetActualTime(TIME_UNIT _unit);

    private:
        std::int64_t start;
        std::int64_t tick;
        std::int64_t prevTick;
        std::int64_t sumPauseTime;
        double frequency;
        bool isPaused;
        bool isStart;
};
}

#endif // CLOCK_H
