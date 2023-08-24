#ifndef __STORM_LOG_H__
#define __STORM_LOG_H__

#include <memory>
#include <string>
#include <stdint.h>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>

namespace storm {

class Logger;

//日志级别
class LogLevel
{
public:
    enum Level {
        UNKOWN = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };
    static const char * toString(LogLevel::Level level);
};

//日志事件
class LogEvent
{
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level
        ,const char* file, int32_t line, uint32_t elapse
        ,uint32_t thread_id, uint32_t fiber_id, uint64_t time
        ,const std::string& thread_name);

    const char * getFile() const {return m_file;}
    uint32_t getLine() const {return m_line;}
    uint32_t getElapse() const {return m_elapse;}
    uint32_t getThreadId() const {return m_threadId;}
    uint32_t getFiberId() const {return m_fiberId;}
    uint64_t getTime() const {return m_time;}
    const std::string& getThreadName() const { return m_threadName;}
    const std::string getContent() const {return m_ss.str();}
    std::shared_ptr<Logger> getLogger() const { return m_logger;}
    LogLevel::Level getLevel() const { return m_level;}

    std::stringstream &getSS() {return m_ss;}

private:
    const char * m_file = nullptr;
    int32_t m_line = 0;
    uint32_t m_elapse = 0;
    uint32_t m_threadId = 0;
    uint32_t m_fiberId = 0;
    uint64_t m_time = 0;
    std::string m_threadName;
    std::stringstream m_ss;  
    std::shared_ptr<Logger> m_logger;
    LogLevel::Level m_level;
};

//日志格式器
class LogFormatter {
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    /**
    * @brief 构造函数
    * @param[in] pattern 格式模板
    * @details 
    *  %m 消息
    *  %p 日志级别
    *  %r 累计毫秒数
    *  %c 日志名称
    *  %t 线程id
    *  %n 换行
    *  %d 时间
    *  %f 文件名
    *  %l 行号
    *  %T 制表符
    *  %F 协程id
    *  %N 线程名称
    *
    *  默认格式 "%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"
    */
    LogFormatter(const std::string &pattern);
    std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
    std::ostream &format(std::ostream &ofs, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);

public:
    class FormatItem {
    public:
        typedef std::shared_ptr<FormatItem> ptr;
        virtual ~FormatItem() {}
        virtual void format(std::ostream &os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
    };

    void init();
private:
    std::vector<FormatItem::ptr> m_items;
    std::string m_pattern;
};

//日志输出器
class LogAppender {
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender(){}
    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
    void setFormatter(LogFormatter::ptr formatter){ m_formatter = formatter;}
    LogFormatter::ptr getFormatter() const {return m_formatter;}
protected:
    LogLevel::Level m_level = LogLevel::DEBUG;
    LogFormatter::ptr m_formatter;
};

//日志器
class Logger : public std::enable_shared_from_this<Logger> {
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
    void setLevel(LogLevel::Level level) {m_level = level;}
    const std::string & getName() const {return m_name;}
private:
    std::string m_name;
    LogLevel::Level m_level;
    std::list<LogAppender::ptr> m_appenders;
    LogFormatter::ptr m_formatter_logger;
};

//输出到控制台
class StdoutLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;
};
//输出到文件
class FileLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string &filename);
    void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;
    bool reopen();
private:
    std::string m_filename;
    std::ofstream m_filestream;
};

} // storm end

#endif