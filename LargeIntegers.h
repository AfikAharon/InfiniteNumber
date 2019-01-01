#ifndef LARGEINTEGERS_H
#define LARGEINTEGERS_H
using namespace std;

#include <string>

/**
 * Infint class - is a infint number represented on string.
 */
class InfInt {
private:
    string stringNum;
    bool isNeg;

public:
    /****constructors*****/
    InfInt();
    InfInt(const string numS);
    InfInt(const char num[]);
    InfInt(const long num);
    InfInt(const int num);
    InfInt(const InfInt &infInt);


    friend ostream &operator<<(ostream &stream, const InfInt &num);
    friend istream &operator>>(istream &stream, InfInt &num);
    operator int();
    InfInt operator>>(int shifts);
    InfInt operator>>=(int shifts);
    InfInt operator<<(int shifts);

    /****Compare operators*****/
    bool operator<(const InfInt &num) const;
    bool operator<=(const InfInt &num) const;
    bool operator>(const InfInt &num) const;
    bool operator>=(const InfInt &num) const;
    bool operator==(InfInt &num) const;

    /****Arithmetic operators*****/
    InfInt operator+(const InfInt &num) const;
    InfInt operator+=(const InfInt &num);
    InfInt operator*(const InfInt &num) const;
    InfInt operator/(const InfInt &num) const;
    // post
    InfInt operator++();
    InfInt operator--();
    // pre
    InfInt operator++(int notused);
    InfInt operator--(int notused);
    InfInt operator-(const InfInt &num) const;

    /****Logical operators*****/
    InfInt operator|(const InfInt &num) const;
    InfInt operator%(const InfInt &num) const;
    InfInt operator&(const InfInt &num) const;
    InfInt operator&=(const InfInt &num);
    InfInt operator^(const InfInt &num) const;

    /*******useful functions*******/
    void checkInput(const string& str);
    int getDigit(InfInt num, int index) const;
    string changeBitToNot(string binariNum) const;
    string twoComplement(string binary) const;
    string addDigit(string number, char digit, int amount) const;
    void checkIfToChangeTheBinaryString(string &binaryOne, bool boolOne,
            string &binaryTow, bool boolTow) const;
    string removeZeroDigit(string num) const;
    InfInt changeToDecimal(InfInt num) const;
    InfInt divideWithTwo(InfInt& num) const;
    InfInt changeToBinary(InfInt &num) const;
    int compareInfint(const InfInt num1, const InfInt num2) const;
    string intToString(const long int x) const;

    void setIsNeg(bool indication) {
        isNeg = indication;
    }

    bool getSign() const {
        return isNeg;
    }

    int getLengthString() const {
        return (int)this->stringNum.length();
    }

    string getStringNumber() const {
        return  this->stringNum;
    }

    void setStringNum(string num) {
        this->stringNum = num;
    }
};

#endif //EX1TT_INFINT_H
