#pragma once

#include <string>
#include <iostream>
#include <systemd/sd-journal.h>

namespace Hbk
{

    //! \enum Severity
    //! \brief The severity of a message. The enum is also used to set the debug level
    enum class Severity
    {
        Emergency    = LOG_EMERG,   //!< 0: System is unusable
        Alert        = LOG_ALERT,   //!< 1: Action must be taken immediatelyAction must be taken immediately
        Critical     = LOG_CRIT,    //!< 2: Critical conditions
        Error        = LOG_ERR,     //!< 3: Error conditions
        Warning      = LOG_WARNING, //!< 4: Warning conditions
        Notice       = LOG_NOTICE,  //!< 5: Normal but significant condition
        Info         = LOG_INFO,    //!< 6: Informational
        Debug        = LOG_DEBUG,   //!< 7: Debug-level message
        None         = -1,          //! for error return, not a real severity
        Default      = Notice       //< The default for debug log level
    }; // Severity


    std::string SeverityToString(Severity severity);
    std::ostream& operator<<(std::ostream& os, Severity v);
    Severity StringToSeverity(const std::string& severityString);

    // General logger class:
    // Examples:
    //     Log() << "Sometext"";
    //     Log() << Severity::Alert << "Alert text";
    //     Log(Severity::Warning) << "Warning";
    //     Log(true); // Enables output to stdout (Does nothing on device)
    //     Log(false); // Disables output to stdout (default)
    class Log
    {
    private:
        Severity    m_severity;
        std::string m_message;
        const char *m_file = "(unknown)";
        int         m_line = 0;
        static bool s_stdoutEnabled; //!< Will log messages be written to stdout as well (doesn't work on device)
        static Severity m_SeverityLevel;

    public:
        explicit Log(Severity severity = Severity::Default) :
            m_severity(severity),
            m_message("")
        {
        };
        explicit Log(bool stdoutEnabled) :
            m_severity(Severity::Default),
            m_message("")
        {
            s_stdoutEnabled = stdoutEnabled;
        };

        Log& SetFileLine(const char *file, int line)
        {
            m_file = file;
            m_line = line;
            return *this;
        }

        ~Log()
        {
            Flush();
        };
        void Flush();
        void EnableStdout(bool enable) { s_stdoutEnabled = enable; }
        void SetSeverityLevel(Severity value) { m_SeverityLevel = value; }
        Log& operator<<(Severity severity);
        Log& operator<<(std::string message);
        Log& operator<<(int8_t value);
        Log& operator<<(uint8_t value);
        Log& operator<<(int16_t value);
        Log& operator<<(uint16_t value);
        Log& operator<<(int32_t value);
        Log& operator<<(uint32_t value);
        Log& operator<<(int64_t value);
        Log& operator<<(uint64_t value);
        Log& operator<<(float value);
        Log& operator<<(double value);

    };

    // Compile-time implementation of "strrchr(s, '/') + 1"
    // Used here to extract the file name (without the full path) from the __FILE__ macro.
    // Note this only returns a pointer to the file name; the full path is still included
    // in the binary. But we avoid a call to strrchr every time we log something.
    static constexpr const char* BaseName(const char* path, const char* baseName)
    {
        return
            *path == '\0' ? baseName :
            *path == '/'  ? BaseName(path + 1, path + 1) :
                            BaseName(path + 1, baseName);
    }

#define Log(param) Log(param).SetFileLine(Hbk::BaseName(__FILE__, __FILE__), __LINE__)
} // namespace
