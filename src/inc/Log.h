#pragma once
#include <iostream>

class Log{
    public:
    enum Level{LevelError, LevelWarn, LevelInfo};
    private:
    Level m_logLevel = LevelInfo;
    public:
    void setLevel(Level level);
    void INFO(const char* message);
    void WARN(const char* message);
    void ERROR(const char* message);
};