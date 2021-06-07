#include <iostream>
#include <sstream>
#include <string>


#define SD_JOURNAL_SUPPRESS_LOCATION
#include <systemd/sd-journal.h>

#include "Log.hpp"

using namespace std;
namespace Hbk
{
    //! Convert a severity to a text string (consisting of only one character)
    //! \param severity Convert this severity to a string
    //! \returns The severity as a one-character string
    string SeverityToString(Severity severity)
    {
        switch (severity)
        {
        case Severity::Emergency:
            return "Emergency";
        case Severity::Alert:
            return "Alert";
        case Severity::Critical:
            return "Critical";
        case Severity::Error:
            return "Error";
        case Severity::Warning:
            return "Warning";
        case Severity::Notice:
            return "Notice";
        case Severity::Info:
            return "Info";
        case Severity::Debug:
            return "Debug";
        default:
            return "?";
        } // switch

    } // SeverityToString

    std::ostream& operator<<(ostream& os, Severity v)
    {
        os << SeverityToString(v);
        return os;
    } // operator<<

    // Initialization of the static global Log instance
    bool Log::s_stdoutEnabled = false;
    Severity Log::m_SeverityLevel = Severity::Debug;

    //! \brief Output what currently is in the buffer
    void Log::Flush()
    {
        if (m_message.size() == 0)
            return;
        if (m_severity <= m_SeverityLevel)
        {
            sd_journal_print(static_cast<int>(m_severity), "%s (%s(%d))", m_message.c_str(), m_file, m_line);
#ifndef REAL_HW
            if (s_stdoutEnabled)
                cout << "Log(" << m_severity << "): " << m_message << " (" << m_file << "(" << to_string(m_line) << "))" << std::endl;
#endif
        }
        m_message = "";
    } // Flush()

    //! \brief Log a string
    Log& Log::operator<<(Severity severity)
    {
        Flush();
        m_severity = severity;
        return *this;
    } // operator<<(severity ..)


    //! \brief Log a string
    Log& Log::operator<<(string text)
    {
        if (m_severity <= m_SeverityLevel)
        {
            m_message.append(text);

            size_t nlPos = m_message.find_first_of('\n');

            while (nlPos != string::npos)
            {
                if (nlPos > 0)
                {
                    string part = m_message.substr(0, nlPos);
                    sd_journal_print(static_cast<int>(m_severity), "%s (%s(%d))", part.c_str(), m_file, m_line);
#ifndef REAL_HW
                    if (s_stdoutEnabled)
                        cout << "Log(" << m_severity << "): " << part << " (" << m_file << "(" << to_string(m_line) << "))" << std::endl;
#endif
                }
                if (nlPos < m_message.size())
                    m_message = m_message.substr(nlPos+1);
                else
                    m_message = "";
                nlPos = m_message.find_first_of('\n');
            } // while

            // Check if string is getting too long (happens if newline isnt encountered
            if (m_message.length() > 250)
                Flush();
        }
        return *this;
    } // operator<<(string ..)

    //! \brief Log a int8_t
    Log& Log::operator<<(int8_t value)
    {
        m_message.append(to_string(value));
        return *this;
    } // operator<<(int8_t ..)

    //! \brief Log a uint8_t
    Log& Log::operator<<(uint8_t value)
    {
        m_message.append(to_string(value));
        return *this;
    } // operator<<(uint8_t ..)

    //! \brief Log a int16_t
    Log& Log::operator<<(int16_t value)
    {
        m_message.append(to_string(value));
        return *this;
    } // operator<<(int16_t ..)

    //! \brief Log a uint16_t
    Log& Log::operator<<(uint16_t value)
    {
        m_message.append(to_string(value));
        return *this;
    } // operator<<(uint16_t ..)

    //! \brief Log a int32_t
    Log& Log::operator<<(int32_t value)
    {
        m_message.append(to_string(value));
        return *this;
    } // operator<<(int32_t ..)

    //! \brief Log a uint32_t
    Log& Log::operator<<(uint32_t value)
    {
        m_message.append(to_string(value));
        return *this;
    } // operator<<(uint32_t ..)

    //! \brief Log a int64_t
    Log& Log::operator<<(int64_t value)
    {
        m_message.append(to_string(value));
        return *this;
    } // operator<<(int64_t ..)

    //! \brief Log a uint64_t
    Log& Log::operator<<(uint64_t value)
    {
        m_message.append(to_string(value));
        return *this;
    } // operator<<(uint64_t ..)

    //! \brief Log a float
    Log& Log::operator<<(float value)
    {
        m_message.append(to_string(value));
        return *this;
    } // operator<<(float ..)

    //! \brief Log a double
    Log& Log::operator<<(double value)
    {
        m_message.append(to_string(value));
        return *this;
    } // operator<<(double ..)

} // namespace
