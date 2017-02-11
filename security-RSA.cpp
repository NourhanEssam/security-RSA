//g++ inputfile.cpp -o outputbinary
//g++ -std=c++11 security-RSA.cpp -o rsa
//12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871
//2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#define PRECISION 18
#define MAX_Mul 1000000000000000000
#define MAX 1000000000
#define capacity 40

class BigInteger
{
private:
    string NumberString;
    long long int NumberInteger[capacity] = {0};
    bool isNegative = false;
    int size;
public:
    BigInteger() {size=0;}
    BigInteger(string S)
    {
        size = 0;
        NumberString = S;
        while (NumberString.length() > 0) {
            if(NumberString.length()<=(PRECISION/2)-1)
            {
                NumberInteger[capacity-1-size++] = stoll(NumberString);
                break;
            }
            else
            {
                NumberInteger[capacity-1-size++] = stoll(NumberString.substr(NumberString.length()-PRECISION/2,NumberString.length()));
                NumberString.erase(NumberString.length()-PRECISION/2,NumberString.length());
            }
        }
    }
    void ShowContent()
    {
        for(int i=capacity-size;i<capacity;i++)
        {
            cout.fill( '0' );
            cout.width( PRECISION/2 );
            cout<<NumberInteger[i];
        }
        cout<<endl;
    }

    BigInteger operator+(const BigInteger& SecondNumber)
    {
        BigInteger result;
        int carry=0,i=0,j=0;
        while(1)
        {
            if(i==size)
            {
                if(j==SecondNumber.size) break;
                result.NumberInteger[capacity-1-result.size++] = SecondNumber.NumberInteger[capacity-1-j++];
            }
            else if(j==SecondNumber.size)
            {
                if(i==size) break;
                result.NumberInteger[capacity-1-result.size++] = NumberInteger[capacity-1-i++];
            }
            else if((NumberInteger[capacity-1-i] + SecondNumber.NumberInteger[capacity-1-j]+carry)<MAX)
            {
                result.NumberInteger[capacity-1-result.size++] = NumberInteger[capacity-1-i++] + SecondNumber.NumberInteger[capacity-1-j++]+carry;
                carry = 0;
            }
            else if((NumberInteger[capacity-1-i] + SecondNumber.NumberInteger[capacity-1-j]+carry)>=MAX)
            {
                result.NumberInteger[capacity-1-result.size++] = (NumberInteger[capacity-1-i++] + SecondNumber.NumberInteger[capacity-1-j++]+carry)%MAX;
                carry = 1;
            }
        }
        cout<<"Supposed to add" <<endl;
        return result;
    }

     BigInteger operator-(const BigInteger& SecondNumber)
     {
         BigInteger result;
         int carry=0,i=0,j=0;
         while(1)
         {
            if(size == SecondNumber.size)
            {
                if(NumberInteger[capacity-1]<SecondNumber.NumberInteger[capacity-1])
                {
                    result.isNegative = true;
                    //swap
                    cout <<"swap";
                }
            }
            else if(size<SecondNumber.size)
            {
                result.isNegative = true;
                //swap
                cout<<"swap";
            }
        
          // if(i==size)
          //   {
          //       if(j==SecondNumber.size) break;
          //       result.NumberInteger[capacity-1-result.size++] = SecondNumber.NumberInteger[capacity-1-j++];
          //   }
            if(j==SecondNumber.size)
            {
                if(i==size) break;
                result.NumberInteger[capacity-1-result.size++] = NumberInteger[capacity-1-i++];
            }
            else if((NumberInteger[capacity-1-i] - SecondNumber.NumberInteger[capacity-1-j]+carry)>=0)
            {
                result.NumberInteger[capacity-1-result.size++] = NumberInteger[capacity-1-i++] - SecondNumber.NumberInteger[capacity-1-j++]+carry;
                carry = 0;
            }
            else if((NumberInteger[capacity-1-i] - SecondNumber.NumberInteger[capacity-1-j]+carry)<0)
            {
                result.NumberInteger[capacity-1-result.size++] = NumberInteger[capacity-1-i++] - SecondNumber.NumberInteger[capacity-1-j++]+carry+MAX;
                carry = -1;
            }
}
         cout<<"Supposed to subtract" <<endl;
         return result;
 }
};

int main()
{
    string ii = "12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871";
    //string ii = "12111";
    //cin>>ii;
    BigInteger i = BigInteger(ii);
    ii = "2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473";
    //ii = "1201";
    //cin>>ii;
    BigInteger i2 = BigInteger(ii);
    BigInteger i3 = i-i2;
    i3.ShowContent();
    return 0;
}
