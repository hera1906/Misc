#include <string>
#include <systemd/sd-journal.h>

using namespace std;

class logtest
{
    public:
        logtest();
        logtest& operator<<(string m);

}; // class logtest

logtest::logtest()
{
} // constructor
logtest& logtest::operator<<(string m)
{
    sd_journal_print(LOG_NOTICE, m.c_str());
} // operator<<

main(int argc, char *argv[])
{
    logtest log;
    string someText = "En eller anden tekst";

    sd_journal_print(LOG_NOTICE, "linie 1");
    sd_journal_send("MESSAGE=linie 2", "PRIORITY=3", "ZONE=MYTEST", 0);

    log << "linie " << "4 " << "fra <<" << "... bemærk at hver ting kommer som separat log udskrift";

    log << "Sometext fra << " << someText;

    sd_journal_print(LOG_WARNING, "Bemærk at sd_journal_print ikke er god med c++ strings:");
    sd_journal_print(LOG_NOTICE, "Sometext fra sd_journal_print: %s", someText);


    sd_journal_print(LOG_NOTICE, "linie 3 SLUT");
}
