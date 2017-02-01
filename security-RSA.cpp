//g++ inputfile.cpp -o outputbinary
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define PRECISION 18

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
            if(NumberString.length()<PRECISION-1)
            {
                NumberInteger.push_back(stoll(NumberString));
                break;
            }
            else
            {
                NumberInteger.push_back(stoll(NumberString.substr(NumberString.length()-PRECISION,NumberString.length())));
                NumberString.erase(NumberString.length()-PRECISION,NumberString.length());
            }
        }
    }
        void ShowContent()
        {
            std::vector<long long int>::reverse_iterator iterator;
            for(iterator = NumberInteger.rbegin(); iterator<NumberInteger.rend(); iterator++)
            {
                cout<<*iterator;
            }
            cout<<endl;
        }
};

int main()
{
    string ii;
    cin>>ii;
    BigInteger i = BigInteger(ii);
    i.ShowContent();
    return 0;
}
