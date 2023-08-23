#include "../storm/log.h"
#include <iostream>

int main() {
    storm::Logger::ptr logger(new storm::Logger);
    logger->addAppender(storm::LogAppender::ptr(new storm::StdoutLogAppender));

    // logger->debug("Hello, World!");
    storm::LogEvent::ptr event(new storm::LogEvent(__FILE__, __LINE__, 0, 1, 2, time(0)));
    std::cout << "event init success" << std::endl;
    event->getSS() << "hello storm log"; 
    logger->log(storm::LogLevel::DEBUG, event);
    
    std::string nstr;
    nstr.append(1, '%');
    std::cout << nstr << std::endl;
    std::cout << "Hello storm log" << std::endl;
    return 0;
}