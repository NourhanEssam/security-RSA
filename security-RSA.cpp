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
    //vector<long long int> NumberInteger;
    bool isNegative;
    int size;
public:
    BigInteger() {}
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

   //  BigInteger operator+(const BigInteger& SecondNumber)
   //  {
   //      BigInteger result;
   //      int carry = 0,i=0,j=0;
   //      while(1)
   //      {
			// if(iterator==NumberInteger.end())
			// {
   //              if(Seconditerator==SecondNumber.NumberInteger.end()) break;
			// 	result.NumberInteger.push_back(*Seconditerator);
   //              Seconditerator++;
			// }
			// else if(Seconditerator==SecondNumber.NumberInteger.end())
			// {
   //              if(iterator==NumberInteger.end()) break;
			// 	result.NumberInteger.push_back(*iterator);
			// 	iterator++;
			// }
   //          else if((*iterator + *Seconditerator+carry)<MAX)
   //          {
   //              result.NumberInteger.push_back(*iterator + *Seconditerator+carry);
   //              carry = 0;
			// 	iterator++;
   //              Seconditerator++;
   //          }
   //          else if((*iterator + *Seconditerator+carry)>=MAX)
   //          {
   //              result.NumberInteger.push_back((*iterator + *Seconditerator+carry)%MAX);
   //              carry = 1;
			// 	iterator++;
   //              Seconditerator++;
   //          }
   //      }
   //      cout<<"Supposed to add" <<endl;
   //      return result;
   //  }

   //  BigInteger operator-(const BigInteger& SecondNumber)
   //  {
   //      BigInteger result;
   //      vector<long long int>::const_iterator iterator = NumberInteger.begin();
   //      vector<long long int>::const_iterator Seconditerator = SecondNumber.NumberInteger.begin();
   //      int carry = 0;
   //      while(1)
   //      {
   //          if(Seconditerator==SecondNumber.NumberInteger.end())
   //          {
   //              if(iterator==NumberInteger.end()) break;
   //              result.NumberInteger.push_back(*iterator);
   //              iterator++;
   //          }
   //          else if((*iterator - *Seconditerator+carry)>=0)
   //          {
   //              result.NumberInteger.push_back(*iterator - *Seconditerator+carry);
   //              carry = 0;
   //              iterator++;
   //              Seconditerator++;
   //          }
   //          else if((*iterator - *Seconditerator+carry)<0)
   //          {
   //              result.NumberInteger.push_back((*iterator - *Seconditerator+carry+MAX));
   //              carry = -1;
   //              iterator++;
   //              Seconditerator++;
   //          }
   //      }
   //      cout<<"Supposed to subtract" <<endl;
   //      return result;
   //  }

   //  BigInteger operator*(const BigInteger& SecondNumber)
   //  {
   //      BigInteger result;
   //      vector<long long int>::const_iterator iterator = NumberInteger.begin();
   //      vector<long long int>::const_iterator Seconditerator = SecondNumber.NumberInteger.begin();
   //      int carry;
   //      for (vector<long long int>::const_iterator iterator=NumberInteger.begin(); iterator < NumberInteger.end(); iterator++)
   //      {
   //          carry = 0;
   //          BigInteger temp;
   //          cout<<"temp fady  ";
   //               temp.ShowContent();
   //          for (vector<long long int>::const_iterator Seconditerator=SecondNumber.NumberInteger.begin(); Seconditerator < SecondNumber.NumberInteger.end(); Seconditerator++)
   //          {
   //              if(((*iterator * *Seconditerator)+carry) >=MAX)
   //              {
   //                  carry = 1;
   //              }
   //          else
   //          {
   //              carry = 0;
   //          }
   //          temp.NumberInteger.push_back(((*iterator * *Seconditerator)+carry)%MAX);
   //               //temp.NumberInteger.push_back(*iterator * *Seconditerator);
   //              // result = result + (*iterator * *Seconditerator);
   //               //result = result + temp + carry;
   //               cout<<"temp  ";
   //               temp.ShowContent();
   //              //temp.NumberInteger.erase(temp.NumberInteger.begin());
   //          }
   //          result = result + temp;
   //          cout<<"result  ";
   //              result.ShowContent();
   //      }
   //      cout<<"Supposed to Multiply" <<endl;
   //      return result;
   //  }
};

int main()
{
    string ii;
    cin>>ii;
    BigInteger i = BigInteger(ii);
    i.ShowContent();
    // cin>>ii;
    // BigInteger i2 = BigInteger(ii);
    // BigInteger i3 = i*i2;
    // i3.ShowContent();
    return 0;
}
