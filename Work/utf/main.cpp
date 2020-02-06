#include <string>
#include <iostream>
#include <locale>
#include <codecvt>

//#include <boost/locale.hpp>
//#include <boost/algorithm/string.hpp>

using namespace std;

int main(int argc, char* argv[])
{
    string str = "Hello World æøå";

    cout << "String: \"" << str  << "\" length: " << str.length() << endl;

    for (int i = 0; i < str.length(); i++)
    {
        cout << "str[" << i << "] : '" << str[i] << "', "
            <<  "value " << hex << (((int) str[i]) & 0xff) << dec << endl;
    }

    //wstring wstr = boost::locale::conv::utf_to_utf<wchar_t>(str);
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    wstring wstr = converter.from_bytes(str);


    wcout << "Wide String: \"" << wstr  << "\" length: " << wstr.length() << endl;

    for (int i = 0; i < wstr.length(); i++)
    {
        wcout << "wstr[" << i << "] : '" << wstr[i] << "', "
            <<  "value " << hex << (int) wstr[i] << " " << (char) ((((int) wstr[i])  & 0xff00)>> 8) <<  dec << endl;
    }
    wcout << "===== DONE ====" << endl;

    return 0;
}
