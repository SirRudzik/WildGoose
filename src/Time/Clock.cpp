#include "../Time/Clock.h"

WG::Clock::Clock():
    start(0),
    tick(0),
    prevTick(0),
    sumPauseTime(0),
    frequency(0),
    isPaused(false),
    isStart(false)
{
    #ifdef WG_DEBUG
    std::cout << "Clock::Konstruktor \n";
    #endif
}

WG::Clock::~Clock()
{
    #ifdef WG_DEBUG
    std::cout << "Clock::Destruktor \n";
    #endif
}

bool WG::Clock::Start()
{
    #ifdef WG_DEBUG
    std::cout << "Clock::Start \n";
    #endif
    if(isStart)
        return false;

    LARGE_INTEGER li;
    QueryPerformanceFrequency(&li);
    frequency = li.QuadPart;

    QueryPerformanceCounter(&li);
    start = li.QuadPart;
    tick = start;
    prevTick = tick;
    isStart = true;
    isPaused = false;
    #ifdef WG_DEBUG
    std::cout << "Clock::Start - return true \n";
    #endif
    return true;
}

bool WG::Clock::Tick()
{
    #ifdef WG_DEBUG
    std::cout << "Clock::Tick \n";
    #endif

    if(!isStart)
        return false;

    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    prevTick = tick;
    tick = li.QuadPart;

    if(isPaused)
        sumPauseTime += tick - prevTick;

    #ifdef WG_DEBUG
    std::cout << "Clock::Tick - return true \n";
    #endif

    return true;
}

bool WG::Clock::TogglePause(bool _pause)
{
    #ifdef WG_DEBUG
    std::cout << "Clock::TogglePause \n";
    #endif
    if(!isStart)
        return false;
    isPaused = _pause;
    return true;
}

double WG::Clock::GetDeltaTime(TIME_UNIT _unit)
{
    #ifdef WG_DEBUG
    std::cout << "Clock::DeltaTime \n";
    #endif
    if(!isStart || isPaused)
        return 0.0f;
    else
        return((tick - prevTick) / (frequency / static_cast<int>( _unit)));

}

double WG::Clock::GetTotalTime(TIME_UNIT _unit)
{
    #ifdef WG_DEBUG
    std::cout << "Clock::TotalTime \n";
    #endif

    if(!isStart)
        return 0.0f;
    else
        return((tick - start - sumPauseTime) / (frequency / static_cast<int>( _unit)));
}

double WG::Clock::GetGlobalTime(TIME_UNIT _unit)
{
    #ifdef WG_DEBUG
    std::cout << "Clock::GlobalTime \n";
    #endif

    if(!isStart)
        return 0.0f;
    else
        return((tick - start) / (frequency / static_cast<int>( _unit)));
}

double WG::Clock::GetActualTime(TIME_UNIT _unit)
{
    #ifdef WG_DEBUG
    std::cout << "Clock::GlobalTime \n";
    #endif

    if(!isStart)
        return 0.0f;
    else
    {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        return((li.QuadPart - start) / (frequency / static_cast<int>( _unit)));
    }
}
