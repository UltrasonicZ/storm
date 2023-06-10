#ifndef __STORM_LOG_H__
#define __STORM_LOG_H__

#include <memory>
#include <string>
#include <stdint.h>
#include <list>
#include <sstream>
#include <fstream>

namespace storm {

//日志事件
class LogEvent
{
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent();
private:
    const char * m_file = nullptr;
    int32_t m_line = 0;
    uint32_t m_elapse = 0;
    uint32_t m_threadId = 0;
    uint32_t m_fiberId = 0;
    uint32_t m_time = 0;
    std::string m_content;  
};

//日志级别
class LogLevel
{
public:
    enum Level {
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };
};

//日志格式器
class LogFormatter {
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    std::string format(LogEvent::ptr event);
private:

};

//日志输出器
class LogAppender {
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender(){}
    virtual void log(LogLevel::Level level, LogEvent::ptr event) = 0;
    void setFormatter(LogFormatter::ptr formatter){ m_formatter = formatter;}
    LogFormatter::ptr getFormatter() const {return m_formatter;}
private:
    LogLevel::Level m_level;
    LogFormatter::ptr m_formatter;
};

//日志器
class Logger {
public:
    typedef std::shared_ptr<Logger> ptr;
    Logger(const std::string& name = "root");
    void log(LogLevel::Level level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    LogLevel::Level getLevel() const { return m_level; }
    void setLevel(LogLevel::Level level) {m_level = level;};
private:
    std::string m_name;
    LogLevel::Level m_level;
    std::list<LogAppender::ptr> m_appenders;
};

//输出到控制台
class StdoutLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    log(LogLevel::Level level, LogEvent::ptr event) override;
};
//输出到文件
class FileLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string & filename);
    log(LogLevel::Level level, LogEvent::ptr event) override;
private:
    std::string m_filename;
    std::ofstream m_filestream;
};
}
#endif