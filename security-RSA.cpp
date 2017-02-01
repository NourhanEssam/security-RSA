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
    vector<long long int> NumberInteger;
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
            vector<long long int>::reverse_iterator iterator;
            for(iterator = NumberInteger.rbegin(); iterator<NumberInteger.rend(); iterator++)
            {
                cout<<*iterator;
            }
            cout<<endl;
    }
    BigInteger operator+(const BigInteger& SecondNumber)
    {
        bool carry = 0;
        BigInteger result;
        vector<long long int>::const_iterator iterator = NumberInteger.begin();
        vector<long long int>::const_iterator Seconditerator = SecondNumber.NumberInteger.begin();
        while(iterator!=NumberInteger.end() || Seconditerator!=SecondNumber.NumberInteger.end())
        {
            result.NumberInteger.push_back(*iterator + *Seconditerator);
            iterator++;
            Seconditerator++;
        }
        cout<<"Supposed to add" <<endl;
        return result;
    }
};

int main()
{
    string ii;
    cin>>ii;
    BigInteger i = BigInteger(ii);
    cin>>ii;
    BigInteger i2 = BigInteger(ii);
    BigInteger i3 = i+i2;
    i3.ShowContent();
    return 0;
}
