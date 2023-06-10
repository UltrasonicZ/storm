 #include "log.h"

namespace storm {
Logger(const std::string& name)
    : m_name(name) {

}        
void Logger::addAppender(LogAppender::ptr appender){
    m_appenders.push_back(appender);
}
void Logger::delAppender(LogAppender::ptr appender){
    for(auto it = m_appenders.begin(); it != m_appenders.end(); ++it){
        if(*it == appender){
            m_appenders.erase(it);
            break;
        }
    }
}
void Logger::log(LogLevel::Level level, LogEvent::ptr event){
    if (level >= m_level) {
        for(auto i : m_appenders){
            i->log(level, event);
        }
    }
}

void Logger::debug(LogEvent::ptr event){
    log(LogEvent::DEBUG, event);
}
void Logger::info(LogEvent::ptr event){
    log(LogEvent::INFO, event);
}
void Logger::warn(LogEvent::ptr event){
    log(LogEvent::WARN, event);
}
void Logger::error(LogEvent::ptr event){
    log(LogEvent::ERROR, event);
}
void Logger::fatal(LogEvent::ptr event){
    log(LogEvent::FATAL, event);
}


FileLogAppender::FileLogAppender(const std::string & filename){

}
FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event){

}
StdoutLogAppender::log(LogLevel::Level level, LogEvent::ptr event){

}
}