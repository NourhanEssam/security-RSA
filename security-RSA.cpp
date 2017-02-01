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
            {
                NumberInteger.push_back(stoll(NumberString));
                break;
            }
            else
            {
                NumberInteger.push_back(stoll(NumberString.substr(NumberString.length()-18,NumberString.length())));
                NumberString.erase(NumberString.length()-18,NumberString.length());
            }
        }
    }
        void PrintData()
        {
            std::vector<long long int>::const_iterator it1 = NumberInteger.begin();
            while (it1 != NumberInteger.end())
            {
                cout << *it1<<endl;
                it1++;
            }
        }
};

int main()
{
    string ii;
    cin>>ii;
    BigInteger i = BigInteger(ii);
    i.PrintData();
    return 0;
}
