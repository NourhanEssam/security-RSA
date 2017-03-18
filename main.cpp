//g++ -O3 -std=c++11 security-RSA.cpp -o rsa
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
    //******************** Constructors and Printing functions ***************************//
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

    //******************** Basic Operations ***************************//

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
        if(carry){
            result.NumberInteger[capacity-1-result.size] = result.NumberInteger[capacity-1-result.size]+carry;
            result.size++;
        }
        if(result.size != 0)
            while(result.NumberInteger[capacity-result.size]==0 && result.size != 0)
                result.size--;
        return result;
    }

    BigInteger operator-(const BigInteger& SecondNumber)
    {
        BigInteger result;
        if((isNegative && !SecondNumber.isNegative) || (!isNegative && SecondNumber.isNegative)) {result = *this + SecondNumber; result.isNegative = isNegative; return result;}
        int carry=0,i=0,j=0;
        while(1)
        {
            //if((size == SecondNumber.size && NumberInteger[capacity-size]<SecondNumber.NumberInteger[capacity-SecondNumber.size]) || (size<SecondNumber.size))
            if(!GreaterorEqual(*this,SecondNumber))
            {
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

                if(!isNegative && !SecondNumber.isNegative) result.isNegative = true;
                else result.isNegative = isNegative;
            }
            else{
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
                if(!isNegative && !SecondNumber.isNegative) result.isNegative = false;
                else result.isNegative = SecondNumber.isNegative;
            }
        }
        if(result.size != 0)
            while(result.NumberInteger[capacity-result.size]==0 && result.size != 0) result.size--;
        return result;
    }

    BigInteger operator*(const BigInteger& SecondNumber)
    {
        BigInteger result;
        int carry;
        bool sign;

        if(isNegative == SecondNumber.isNegative) sign = false;
        else if(isNegative != SecondNumber.isNegative) sign = true;

        //if(size == 1 && SecondNumber.size == 1) return BigInteger((NumberInteger[capacity-1]*SecondNumber.NumberInteger[capacity-1]));

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
        if(result.size != 0)
            while(result.NumberInteger[capacity-result.size]==0 && result.size != 0) result.size--;
        result.isNegative = sign;
        return result;
    }

    BigInteger divide(BigInteger dividor)
    {
        BigInteger rem = *this ,qou = 0;
        BigInteger dividor_multiples[100];
        int part_size;

        if(isNegative == dividor.isNegative) qou.isNegative = false;
        else if(isNegative != dividor.isNegative) qou.isNegative = true;

        if(isEqual(rem,dividor)) return BigInteger(1);
        if(!GreaterorEqual(rem,dividor)) return BigInteger(0);
        if(rem.size == 1 && dividor.size == 1) return BigInteger((rem.NumberInteger[capacity-1]/dividor.NumberInteger[capacity-1]));

        dividor_multiples[0] = dividor;

        for (int i=1 ; i<100 ; i++)
        {
            dividor_multiples[i] = dividor_multiples[i-1] * BigInteger(2);
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
                count_multiples -- ;;
            }
            else
            {
                while(!GreaterOrEqual_part(rem,dividor_multiples[count_multiples],part_size))
                {
                    count_multiples = count_multiples/2;
                }
                newDiv = dividor_multiples[count_multiples];
            }

            BigInteger dividor_multiple ;
            BigInteger qou_part(pow(2,count_multiples));
            int j = capacity-newDiv.size;
            for(int i=capacity-newDiv.size-(rem.size-part_size);i<capacity;i++)
            {
                if(j>=capacity) break;
                dividor_multiple.NumberInteger[i] = newDiv.NumberInteger[j];
                j++;
            }
            dividor_multiple.size = newDiv.size+(rem.size-part_size);

            BigInteger qou_processed ;
            j = capacity-qou_part.size;
            for(int i=capacity-qou_part.size-(rem.size-part_size);i<capacity;i++)
            {
                if(j>=capacity) break;
                qou_processed.NumberInteger[i] = qou_part.NumberInteger[j];
                j++;
            }
            qou_processed.size = qou_part.size+(rem.size-part_size);
            rem = rem-dividor_multiple;
            qou = qou + qou_processed;
        }
        if(qou.size != 0)
            while(qou.NumberInteger[capacity-qou.size]==0 && qou.size != 0) qou.size--;
        return qou;
    }

    BigInteger rem(BigInteger dividor)
    {
        BigInteger rem = *this;
        int staticsize = 20;
        BigInteger dividor_multiples[staticsize];
        int part_size;

        if(isNegative == dividor.isNegative) rem.isNegative = false;
        else if(isNegative != dividor.isNegative) rem.isNegative = true;

        dividor_multiples[0] = dividor;

        for (int i=1 ; i<staticsize ; i++)
        {
            dividor_multiples[i] = dividor_multiples[i-1] * BigInteger(2);
        }

        while(GreaterorEqual(rem,dividor))
        {
            BigInteger newDiv;

            if(!GreaterOrEqual_part(rem,dividor,dividor.size)) part_size = dividor.size + 1;
            else part_size = dividor.size;

            int count_multiples = staticsize-1;
            if(GreaterOrEqual_part(rem,dividor_multiples[count_multiples],part_size))
            {
                BigInteger temp = dividor_multiples[count_multiples];
                while(GreaterOrEqual_part(rem,temp,part_size))
                {
                    newDiv = temp;
                    temp = temp * BigInteger(8);
                    count_multiples ++;
                }
                count_multiples -- ;;
            }
            else
            {
                while(!GreaterOrEqual_part(rem,dividor_multiples[count_multiples],part_size))
                {
                    count_multiples = count_multiples/2;
                }
                newDiv = dividor_multiples[count_multiples];
            }

            BigInteger dividor_multiple ;
            int j = capacity-newDiv.size;
            for(int i=capacity-newDiv.size-(rem.size-part_size);i<capacity;i++)
            {
                if(j>=capacity) break;
                dividor_multiple.NumberInteger[i] = newDiv.NumberInteger[j];
                j++;
            }
            dividor_multiple.size = newDiv.size+(rem.size-part_size);
            rem = rem-dividor_multiple;
        }
        if(rem.size != 0)
            while(rem.NumberInteger[capacity-rem.size]==0 && rem.size != 0) rem.size--;
        return rem;
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

    //******************** Helping Functions ***************************//
    bool GreaterorEqual(const BigInteger& x,const BigInteger& y)
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

    bool GreaterOrEqual_part(const BigInteger& x,const BigInteger& y,int till)
    {
        if(till>y.size) return true;
        if(till<y.size) return false;
        int j = capacity-y.size;
        for(int i=capacity-x.size;i<capacity-x.size+till;i++)
        {
            if(x.NumberInteger[i]>y.NumberInteger[j]) return true;
            else if(x.NumberInteger[i]<y.NumberInteger[j]) return false;
            j++;
        }
        return true;
    }

    bool isEqual(const BigInteger& x,const BigInteger& y)
    {
        if(x.size!=y.size) return false;
        bool equal = true;
        int j = capacity-y.size;
        for(int i=capacity-x.size;i<capacity;i++)
        {
            if(x.NumberInteger[i] != y.NumberInteger[j]) equal = false;
            j++;
        }
        return equal;
    }

    BigInteger divideByTwo()
    {
        BigInteger quo;
        long long int temp=0;
        for(int i=capacity-size; i<capacity ; i++)
        {
            temp = (temp%2) * MAX + NumberInteger[i];
            quo.NumberInteger[i] = temp/2;
            quo.size ++;
        }
        if(quo.NumberInteger[capacity-quo.size]==0) quo.size--;
        return quo;
    }

    long long int RemFromTwo()
    {
        long long int temp=0;
        for(int i=capacity-size; i<capacity ; i++)
        {
            temp = (temp%2) * MAX + NumberInteger[i];
        }
        return (temp%2);
    }

    //******************** Encryption Basic Functions ***************************//

    BigInteger powerModular(BigInteger power, BigInteger mod)
    {
        BigInteger base = *this;
        BigInteger result (1);
        BigInteger zero (0);

        while(GreaterorEqual(power,zero))
        {
            if(power.RemFromTwo())
            {
                result = result*base;
                result = result.rem(mod);
            }
            base = base*base;
            base = base.rem(mod);
            power = power.divideByTwo();
        }
        return result;
    }

    bool MillerRabinPrimalityTest()
    {
        BigInteger n_1 = *this-BigInteger(1);
        BigInteger q = *this-BigInteger(1);
        int k = 0;
        while(q.RemFromTwo() == 0)
        {
            q = q.divideByTwo();
            k++;
        }
        BigInteger a(2);

        BigInteger apowq = a.powerModular(q,*this);
        if(isEqual(apowq,BigInteger(1)))
            return true;
        if(isEqual(apowq,n_1))
            return true;

        for(int j=1; j<k; j++)
        {
            BigInteger apowjq_needmod = apowq * apowq;
            BigInteger apowjq = apowjq_needmod.rem(*this);
            if(isEqual(apowjq,n_1))
                return true;
        }
        return false;
    }

    BigInteger ExtendedEculidInverse(BigInteger m)
    {
        BigInteger A2("0"),A3=m,B2("1"),B3=*this,Q;
        BigInteger temp2,temp3;
        BigInteger temp5,temp6;

        while (!isEqual(B3,BigInteger(1))) {
            Q = A3.divide(B3);

            temp2 = A2;
            temp3 = A3;

            A2 = B2;
            A3 = B3;

            temp5 = Q*A2;
            temp6 = Q*A3;

            B2 = temp2-temp5;
            B3 = temp3-temp6;
        }
        if(B2.isNegative) {B2.isNegative = false; B2 = m - B2;}
        return B2;
    }
    //******************** Encryption ***************************//
};

int main()
{
    //    //string ii = "12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871";
    //    //string ii = "1236998110188786567180";
    //    //string ii = "1530164324610629353625736427547608653152400";
    //    //string ii = "121233111221212123344556434343654344444221";
    //    //string ii = "111";
    //    //string ii = "199999999999991119990000003232";
    //    //cin>>ii;
    //    BigInteger P ("12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871");
    //    //BigInteger i ("14");
    //    //BigInteger i ("1");
    //    //ii = "2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473";
    //    //ii = "121222222222222222121212";
    //    //ii = "76508367834915852";
    //    //ii = "19999992123211111";
    //    //ii = "20650";
    //    //ii = "20650";
    //    //ii = "11292929";
    //    //cin>>ii;
    //    //BigInteger i2 ("12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871");
    //    //BigInteger i4 ("11292929");
    //    //BigInteger i2 ("12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871");
    //    BigInteger Q ("2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473");
    //    BigInteger E ("65537");
    //    //BigInteger i3 = i.ExtendedEculidInverse(i2);

//            BigInteger Q("2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473");
//                    cout<<Q.MillerRabinPrimalityTest();


        string P_str;
        cout << "P = "<<endl;
        //cin>>P_str;
        //BigInteger P(P_str);
        BigInteger P("12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871");

        string Q_str;
        cout << "Q = "<<endl;
        //cin>>Q_str;
        //BigInteger Q(Q_str);
        BigInteger Q("2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473");

        string E_str;
        cout << "E = "<<endl;
        //cin>>E_str;
        //BigInteger E(E_str);
        BigInteger E("65537");

        clock_t begin = clock();

        cout << "is P prime"<<endl;
        if(P.MillerRabinPrimalityTest()) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;

        cout << "is Q prime"<<endl;
        if(Q.MillerRabinPrimalityTest()) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;

        cout << "N = "<<endl;
        BigInteger N = P*Q;
        N.ShowContent();
        BigInteger phiN_p = P-BigInteger(1);
        BigInteger phiN_q = Q-BigInteger(1);
        BigInteger phiN = phiN_p * phiN_q;
        cout << "Phi(N) = "<<endl;
        phiN.ShowContent();
        BigInteger D = E.ExtendedEculidInverse(phiN);
        cout << "D = "<<endl;
        D.ShowContent();

        BigInteger msg ("1976620216402300889624482718775150");
        cout << "msg = "<<endl;
        msg.ShowContent();
        BigInteger Enc_msg = msg.powerModular(E,N);
        cout << "Encrypted message = "<<endl;
        Enc_msg.ShowContent();
        BigInteger Dec_msg = Enc_msg.powerModular(D,N);
        cout << "Decrypted message = "<<endl;
        Dec_msg.ShowContent();
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout << "total time: " << elapsed_secs <<"\n";

    return 0;
}
