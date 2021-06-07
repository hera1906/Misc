#include <iostream>
#include <sstream>
#include <string>

#include "Log.hpp"
#include "HBKAssert.hpp"

int main(int argc, char* argv[])
{
    std::cout << "Logexample start" << std::endl;

    Hbk::Log() << "Log example started";
    Hbk::Log() << "Outputting different stuff at LOG_INFO";
    Hbk::Log(Hbk::Severity::Info) << "The number is: " << 17 << " output at severity " << Hbk::Severity::Info;
    Hbk::Log(true); // Now also write to stdout
    Hbk::Log() << "This line should also appear on stdout.... Testing " << 1 << " " << 2 << " " << 3;

    Hbk::Log(Hbk::Severity::Warning) << "Finally trying HBKAssert:";
    HBKAssert(false, "Expected to fail");

    Hbk::Log(Hbk::Severity::Alert) << "This should never be written to the log";

    return 0;
}
