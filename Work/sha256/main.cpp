#include <stdlib.h>
#include <string>
#include <iostream>
#include <locale>

#include <cryptopp/hmac.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/filters.h>
#include <cryptopp/sha.h>
#include <cryptopp/base64.h>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " string" << endl;
        return 1;
    }

    string inputString(argv[1]);
    //string inputString = "a";

    //--- base 64 decode start
    cout << "Expecting input string to be base64encoded" << endl;
    string newString;
    CryptoPP::StringSource ss(inputString, true,
            new CryptoPP::Base64Decoder(
                new CryptoPP::StringSink(newString)));
    inputString = newString;
    //--- base64 decode end
    
    array<unsigned char, 256 / 8> result;
    string keyString = "Not implemented yet!";

    CryptoPP::HMAC<CryptoPP::SHA256> hmac((const byte *)keyString.data(), keyString.size());


    CryptoPP::ArraySource as((const byte *)inputString.data(), inputString.size(), true,
            new CryptoPP::HashFilter(hmac,
                new CryptoPP::ArraySink(result.data(), result.size())));


    for (int i = 0; i < inputString.size(); i++)
        cout << "inputString[" << i << "] = " << hex << (int) inputString[i] << dec << endl;
    cout << endl;
    for (int i = 0; i < keyString.size(); i++)
        cout << "keyString[" << i << "] = " << hex << (int) keyString[i] << dec << endl;
    cout << endl;
    for (int i = 0; i < result.size(); i++)
        cout << "result[" << i << "] = " << hex << (int) result[i] << dec << endl;

    return 0;
}
