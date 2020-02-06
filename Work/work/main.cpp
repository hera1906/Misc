#include <stdlib.h>
#include <string>
#include <iostream>
#include <locale>


using namespace std;
string EscapeForPrint(const string& str)
{
    return str;
    string result;

    for (auto it = str.cbegin(); it != str.cend(); ++it)
    {
        if (*it ==  '\\')
            result += '\\'; 
        result += *it;
    }
    return result;

}
int main(int argc, char* argv[])
{
    cout << EscapeForPrint("'S' = '\\'") << endl;
    cout << EscapeForPrint("'SS' = '\\\\'") << endl;
    cout << EscapeForPrint("'SSS' = '\\\\\\'") << endl;
    cout << EscapeForPrint("'SSSS' = '\\\\\\\\'") << endl;
    cout << EscapeForPrint("'Sn' = '\\n'") << endl;
    cout << EscapeForPrint("'SSn' = '\\\\n'") << endl;
    cout << EscapeForPrint("'SSSn' = '\\\\\\n'") << endl;
    cout << EscapeForPrint("'SSSSn' = '\\\\\\\\n'") << endl;

    return 0;
}
