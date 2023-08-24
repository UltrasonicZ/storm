#include "../storm/log.h"
#include <iostream>

int main() {
    storm::Logger::ptr logger(new storm::Logger);
    
    // logger->addAppender(storm::LogAppender::ptr(new storm::FileLogAppender("log.log")));

    logger->addAppender(storm::LogAppender::ptr(new storm::StdoutLogAppender));
    

    // storm::LogEvent::ptr event(new storm::LogEvent(__FILE__, __LINE__, 0, 1, 2, time(0)));
    storm::LogEvent::ptr event(new storm::LogEvent(logger, storm::LogLevel::DEBUG, \
                        __FILE__, __LINE__, 0, 12345,\
                54321, time(0), "I'm the king"));

    event->getSS() << "hello storm log"; 
    logger->log(storm::LogLevel::DEBUG, event);
    return 0;
}