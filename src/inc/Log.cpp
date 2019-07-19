#include "Log.h"

void Log::setLevel(Level level){
    m_logLevel = level;
}

void Log::INFO(const char* message){
    if (m_logLevel >= LevelInfo) std::cout << "[INFO]: " << message << std::endl;
}
void Log::WARN(const char* message){
    if (m_logLevel >= LevelWarn) std::cout << "[WARN]: " << message << std::endl;
}
void Log::ERROR(const char* message){
    if (m_logLevel >= LevelError) std::cout << "[ERROR]: " << message << std::endl;
}