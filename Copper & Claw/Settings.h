#pragma once

struct CopperAndClawSettings
{
    // Trading Post trend window:
    // 0 = 15m
    // 1 = 30m
    // 2 = 1h
    // 3 = 6h
    // 4 = 24h
    // 5 = 3d
    // 6 = 7d
    // 7 = 30d
    // 8 = 90d
    int tradingPostTrendWindowIndex = 1;
};

extern CopperAndClawSettings g_Settings;

namespace Settings
{
    bool Load(void* moduleHandle);
    bool Save(void* moduleHandle);
}