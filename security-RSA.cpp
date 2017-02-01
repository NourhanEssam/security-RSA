//g++ inputfile.cpp -o outputbinary
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class BigInteger
{
private:
    string NumberString;
    std::vector<long long int> NumberInteger;
public:
    BigInteger() {}
    BigInteger(string S)
    {
        NumberString = S;
        while (NumberString.length() > 0) {
            if(NumberString.length()<19)
            {cout<< NumberString; break;}
            else
            {
                string ss = NumberString.substr(NumberString.length()-18,NumberString.length());
                long long int hh = stoll(ss);
                cout << NumberString.substr(NumberString.length()-18,NumberString.length())<<endl;
                NumberString.erase(NumberString.length()-18,NumberString.length());
            }
        }
    }
};

int main()
{
    string ii;
    cin>>ii;
    BigInteger i = BigInteger(ii);
    return 0;
}
