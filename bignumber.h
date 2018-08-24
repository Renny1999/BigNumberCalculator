#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <iostream>

class BigNumber{
private:
    int number[200];
    int start;
    int end;
    bool negative;
public:
    BigNumber();
    BigNumber(std::string str);
    BigNumber(const BigNumber& left);
    ~BigNumber();
    void print();
    void printnumber();
    std::string getValue();
    int getLength();
    int firstNonZero();


    friend std::ostream& operator << (std::ostream& os, const BigNumber& num);


    BigNumber operator + (BigNumber right);
    BigNumber operator - (BigNumber right);
    BigNumber operator * (BigNumber right);
    BigNumber operator / (BigNumber right);



    bool operator < (const BigNumber& right);
    bool operator > (const BigNumber& right);
    bool operator == (const BigNumber& right);
    bool operator <= (const BigNumber& right);
    bool operator >= (const BigNumber& right);

    BigNumber& operator = (const BigNumber& right);
};

#endif // BIGNUMBER_H
