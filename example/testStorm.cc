#include "../storm/log.h"
#include <iostream>

int main() {
    sylar::Logger::ptr logger(new sylar::Logger);
    logger->addAppender(sylar::LogAppender::ptr(new sylar::StdoutLogAppender));

    // logger->debug("Hello, World!");
    sylar::LogEvent::ptr event(new sylar::LogEvent(logger,sylar::LogLevel::DEBUG, 
    __FILE__, __LINE__, 0, 1, 2, time(0), "wangbing"));

    
    // LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level
    //         ,const char* file, int32_t line, uint32_t elapse
    //         ,uint32_t thread_id, uint32_t fiber_id, uint64_t time
    //         ,const std::string& thread_name);
    event->getSS() << "hello storm log"; 
    logger->log(sylar::LogLevel::DEBUG, event);

    return 0;
}