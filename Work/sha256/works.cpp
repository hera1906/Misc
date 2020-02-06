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

    array<unsigned char, 256 / 8> result;
    string keyString = "Not implemented yet!";

    CryptoPP::HMAC<CryptoPP::SHA256> hmac((const byte *)keyString.data(), keyString.size());

    array<unsigned char, 1> input = {'a'};
    string stringInput = "a";

    CryptoPP::ArraySource as(input.data(), input.size(), true,
            new CryptoPP::HashFilter(hmac,
                new CryptoPP::ArraySink(result.data(), result.size())));


    for (int i = 0; i < input.size(); i++)
        cout << "input[" << i << "] = " << hex << (int) input[i] << dec << endl;
    cout << endl;
    for (int i = 0; i < keyString.size(); i++)
        cout << "keyString[" << i << "] = " << hex << (int) keyString[i] << dec << endl;
    cout << endl;
    for (int i = 0; i < result.size(); i++)
        cout << "result[" << i << "] = " << hex << (int) result[i] << dec << endl;

    return 0;
}
