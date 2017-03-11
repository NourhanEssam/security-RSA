//g++ -std=c++11 security-RSA.cpp -o rsa
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define PRECISION 18
#define MAX_Mul 1000000000000000000
#define MAX 1000000000
#define capacity 100

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

    BigInteger(int i)
    {
        NumberInteger[capacity-1] = i;
        size = 1;
    }

    void ShowContent()
    {
        cout<<NumberInteger[0];
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
                result.NumberInteger[capacity-1-result.size++] = SecondNumber.NumberInteger[capacity-1-j++]+carry;
                carry = 0;
            }
            else if(j==SecondNumber.size)
            {
                if(i==size) break;
                result.NumberInteger[capacity-1-result.size++] = NumberInteger[capacity-1-i++]+carry;
                carry = 0;
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
        return result;
    }

    BigInteger operator-(const BigInteger& SecondNumber)
    {
        BigInteger result;
        int carry=0,i=0,j=0;
        while(1)
        {
            if((size == SecondNumber.size && NumberInteger[capacity-1]<SecondNumber.NumberInteger[capacity-1]) || (size<SecondNumber.size))
            {
                result.isNegative = true;
                if(j==size)
                {
                    if(i==SecondNumber.size) break;
                    result.NumberInteger[capacity-1-result.size++] = SecondNumber.NumberInteger[capacity-1-i++]+carry;
                    carry = 0;
                }
                else if((SecondNumber.NumberInteger[capacity-1-i] - NumberInteger[capacity-1-j]+carry)>=0)
                {
                    result.NumberInteger[capacity-1-result.size++] = SecondNumber.NumberInteger[capacity-1-i++] - NumberInteger[capacity-1-j++]+carry;
                    carry = 0;
                }
                else if((SecondNumber.NumberInteger[capacity-1-i] - NumberInteger[capacity-1-j]+carry)<0)
                {
                    result.NumberInteger[capacity-1-result.size++] = SecondNumber.NumberInteger[capacity-1-i++] - NumberInteger[capacity-1-j++]+carry+MAX;
                    carry = -1;
                }
            }
            else{
                result.isNegative = false;
                if(j==SecondNumber.size)
                {
                    if(i==size) break;
                    result.NumberInteger[capacity-1-result.size++] = NumberInteger[capacity-1-i++]+carry;
                    carry = 0;
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
        }
        return result;
    }
    BigInteger operator*(const BigInteger& SecondNumber)
    {
        BigInteger result;
        int carry;

        if(isNegative == SecondNumber.isNegative) result.isNegative = false;
        else if(isNegative != SecondNumber.isNegative) result.isNegative = true;

        for (int i=capacity-1; i>=capacity-size; i--)
        {
            carry = 0;
            for (int j=capacity-1; j>=capacity-SecondNumber.size; j--)
            {
                BigInteger temp;
                temp.NumberInteger[-(capacity-1-i-j)] = ((NumberInteger[i] * SecondNumber.NumberInteger[j])+carry)%MAX;
                temp.size = capacity+(capacity-1-i-j);
                carry = ((NumberInteger[i] * SecondNumber.NumberInteger[j])+carry)/MAX;
                result = result + temp;
                if(j==capacity-SecondNumber.size)
                {
                    BigInteger temp2;
                    temp2.NumberInteger[-(capacity-1-i-j+1)] = carry;
                    temp2.size = capacity+(capacity-1-i-j+1);
                    result = result + temp2;
                }
            }
        }
        if(result.NumberInteger[capacity-result.size]==0) result.size--;
        return result;
    }

    void operator=(const BigInteger& SecondNumber)
    {
        this->size = SecondNumber.size;
        for(int i=0;i<capacity;i++)
        {
            this->NumberInteger[i] = SecondNumber.NumberInteger[i];
        }
        this->isNegative = SecondNumber.isNegative;
    }

    bool GreaterorEqual(BigInteger& x,BigInteger& y)
    {
        if(x.size>y.size) return true;
        else if (y.size>x.size) return false;
        else {
            for(int i=capacity-x.size;i<capacity;i++)
            {
                if(x.NumberInteger[i]>y.NumberInteger[i]) return true;
                else if (y.NumberInteger[i]>x.NumberInteger[i]) return false;
            }
            return true;
        }
    }

    bool GreaterOrEqual_part(BigInteger& x,BigInteger& y,int till)
    {
        if(till>y.size) return true;
        int j = capacity-y.size;
        for(int i=capacity-x.size;i<capacity-x.size+till;i++)
        {
            if(x.NumberInteger[i]>y.NumberInteger[j]) return true;
            else if(x.NumberInteger[i]<y.NumberInteger[j]) return false;
            j++;
        }
        return true;
    }

    BigInteger divide(BigInteger dividor)
    {
        BigInteger rem = *this ,qou = 0;
        BigInteger dividor_multiples[100];
        int part_size;

        for (int i=0 ; i<100 ; i++)
        {
            dividor_multiples[i] = dividor * BigInteger(2*(i+1));
        }

        while(GreaterorEqual(rem,dividor))
        {
            BigInteger newDiv;

            if(!GreaterOrEqual_part(rem,dividor,dividor.size)) part_size = dividor.size + 1;
            else part_size = dividor.size;

            int count_multiples = 99;
            if(GreaterOrEqual_part(rem,dividor_multiples[count_multiples],part_size))
            {
                BigInteger temp = dividor_multiples[count_multiples];
                while(GreaterOrEqual_part(rem,temp,part_size))
                {
                    newDiv = temp;
                    temp = temp * BigInteger(2);
                    count_multiples ++;
                }
            }
            else
            {
                while(!GreaterOrEqual_part(rem,dividor_multiples[count_multiples],part_size))
                {
                    count_multiples --;
                }
                newDiv = dividor_multiples[count_multiples];
            }
            BigInteger dividor_multiple = newDiv * BigInteger(to_string(pow(10,rem.size-part_size)));;
            rem = rem-dividor_multiple;
            qou = qou + (BigInteger((count_multiples+1)*2) * BigInteger(to_string(pow(10,rem.size-part_size))));
        }
        return rem;
    }
};

int main()
{
    //string ii = "12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871";
    //string ii = "121233111221212123344556434343654344444221";
    //string ii = "111";
    string ii = "199999999999991119990000003232";
    //cin>>ii;
    BigInteger i = BigInteger(ii);
    //ii = "2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473";
    //ii = "121222222222222222121212";
    //ii = "76508367834915852";
    ii = "19999992123211111";
    //cin>>ii;
    BigInteger i2 = BigInteger(ii);
    //BigInteger i3 = i*i2;
    BigInteger i3 = i.divide(i2);
    i3.ShowContent();
    return 0;
}
