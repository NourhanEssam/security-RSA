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
        cout<<"Supposed to subtract" <<endl;
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
        return result;
    }


    BigInteger divide(BigInteger dividor)
    {
        BigInteger result;
        BigInteger rem ,qou;
        BigInteger dividor_multiples[6];

        for (int i=0 ; i<6 ; i++)
        {
            dividor_multiples[i] = dividor * BigInteger(2*(i+1));
        }

//        while(1)
//        {

//        }

        return result;
    }


    //    BigInteger divide(BigInteger SecondNumber)
    //    {
    //        BigInteger result;
    //        long long int power = 0;
    //        BigInteger MultiplyingNumbers;
    //        bool LessThan;

    //        while (1) {
    //            // ageeb power value lel rakam
    //            BigInteger powerValue (to_string(pow(2,power)));

    //            //adrabo fe secondNumber
    //            MultiplyingNumbers = SecondNumber * powerValue;


    //            //a3ml check bel size lw ana mn l awel 5ales w ashof l asly.size l7ad 3dadhom lw akbar
    //            //mn capacity-size ha3ml check b loop hwa akbar wla as3'ar
    //            for(int i=0; i<MultiplyingNumbers.size; i++)
    //            {
    //                if(NumberInteger[capacity-size-i] < MultiplyingNumbers[capacity-MultiplyingNumbers.size-i])
    //                {
    //                    break;
    //                }
    //            }

    //            //a3ml minus w a3ml add lel power value 3al result w a5aly power be zero tany w a3adel l rakam l asly be dah minus dah

    //            //lw as3'ar hzawed l power value tany w agrab fe nafs l loop


    //        }

    ////        while (1) {
    ////               if()


    ////            //if(SecondNumber.size > size || (SecondNumber.size == size && NumberInteger[capacity-size] < SecondNumber.NumberInteger[capacity-size]))
    ////        }
    //        return result;
    //    }

    //    BigInteger operator/(const BigInteger& SecondNumber)
    //    {
    //        BigInteger result;
    //        //int power = 0;
    //        BigInteger x("1");
    //        x.ShowContent();
    //        SecondNumber * x;
    //        while (1) {
    ////               if()


    ////            //if(SecondNumber.size > size || (SecondNumber.size == size && NumberInteger[capacity-size] < SecondNumber.NumberInteger[capacity-size]))
    ////        }
    //        return result;
    //    }
};

int main()
{
    //string ii = "12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871";
    //string ii = "121233111221212123344556434343654344444221";
    //string ii = "111";
    string ii = "1";
    //cin>>ii;
    BigInteger i = BigInteger(ii);
    //ii = "2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473";
    //ii = "121222222222222222121212";
    //ii = "76508367834915852";
    ii = "9";
    //cin>>ii;
    BigInteger i2 = BigInteger(ii);
    //BigInteger i3 = i*i2;
    BigInteger i3 = i.divide(i2);
    i3.ShowContent();
    return 0;
}
