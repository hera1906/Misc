#pragma once
#include "Log.hpp"

#define HBKAssert(condition, message) \
    do { \
        if (! (condition)) { \
            Hbk::Log(Hbk::Severity::Error) << "Assertion `" + std::string(#condition ) +"` failed in " + std::string( __FILE__ )\
                      + " line " + std::to_string( __LINE__ ) + ": " + std::string( message ) + "\n"; \
            std::terminate(); \
        } \
    } while (false)
