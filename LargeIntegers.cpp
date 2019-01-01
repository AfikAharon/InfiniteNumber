#include <iostream>
#include <sstream>
#include "LargeIntegers.h"
#include "string.h"

using namespace std;

// copy constructor
InfInt::InfInt(const InfInt &infInt) {
    this->stringNum = infInt.stringNum;
    this->isNeg = infInt.isNeg;
}

// constructors
InfInt::InfInt() {
    stringNum = new char[1];
    stringNum = "0";
    isNeg = false;
}

InfInt::InfInt(const char num[]) {
    stringNum = num;
    // check the given input
    checkInput(stringNum);
    if (num[0] == '-') {
        isNeg = true;
        stringNum.erase(0, 1);
    } else {
        stringNum = num;
        isNeg = false;
    }
}

InfInt::InfInt(const long num) {
    stringNum = intToString(num);
    if (num < 0) {
        isNeg = true;
        stringNum.erase(0, 1);
    } else {
        isNeg = false;
    }
}

InfInt::InfInt(const int num) {
    stringNum = intToString(num);
    if (num < 0) {
        isNeg = true;
        stringNum.erase(0, 1);
    } else {
        isNeg = false;
    }
}

InfInt::InfInt(const string numS) {
    stringNum = numS;
    // check the given input
    checkInput(numS);
    if (numS[0] == '-') {
        isNeg = true;
        stringNum.erase(0, 1);
    } else {
        isNeg = false;
    }
}

/**
 * The function cast int to string.
 *
 * @param x the given int
 * @return string number
 */
string InfInt::intToString(const long int x) const {
    ostringstream cast;
    cast << x;
    return cast.str();
}

/**
 *  The function check if the given number is legal
 *
 * @param str  the given str
 */
void InfInt::checkInput(const string &str) {
    long i = 0;
    if (((str[0]) == '-') || ((str[0]) == '+')) {
        i++;
    }
    for (long j = i; j < str.size(); ++j) {
        if ((str[j] > '9') || (str[j] < '0')) {
            throw "something wrong with the input";
        }
    }
}

/**
 * The function change the bits to not.
 *
 * @param binariNum the binary num
 * @return the new number
 */
string InfInt::changeBitToNot(string binariNum) const {
    string temp = binariNum;
    for (int i = 0; i < temp.length(); ++i) {
        if (temp[i] == '0') {
            temp[i] = '1';
        } else {
            temp[i] = '0';
        }
    }
    return temp;
}

/**
 * The function change the binary number use the two's complement method.
 *
 * @param binary the binary number
 * @return the new representation.
 */
string InfInt::twoComplement(string binary) const {
    string tempBinari = changeBitToNot(binary);
    string finallNum = "";
    int sum = 1;
    int i = tempBinari.length() - 1;
    int carry = 0;
    while (i >= 0) {
        sum += tempBinari[i] - '0' + carry;
        if (sum == 0) {
            finallNum.insert(0, "0");
            carry = 0;
        } else if (sum == 1) {
            finallNum.insert(0, "1");
            carry = 0;
        } else if (sum == 2) {
            finallNum.insert(0, "0");
            carry = 1;
        } else if (sum == 3) {
            finallNum.insert(0, "1");
            carry = 1;
        }
        sum = 0;
        i--;
    }
    // if the msb change to 0 insert 1.
    if (finallNum[0] == '0') {
        finallNum.insert(0, "1");
    }
    return finallNum;
}

/**
 * The function add digits to the string.
 *
 * @param number
 * @param digit to add
 * @param amount the amount digit to add the string
 * @return teh new string
 */
string InfInt::addDigit(string number, char digit, int amount) const {
    string temp = number;
    for (int i = 0; i < amount; ++i) {
        temp = digit + temp;
    }
    return temp;
}

/**
 * the function check if the binary number is negative and call
 * the function twoComplement to change the binary string.
 *
 * @param binaryOne the first binary number
 * @param boolOne the sign  number
 * @param binaryTow the seconde binary number
 * @param boolTow the sign  number
 */
void InfInt::checkIfToChangeTheBinaryString(string &binaryOne, bool boolOne,
                                    string &binaryTow, bool boolTow) const {
    // if the 2 number negatives.
    if (boolOne && boolTow) {
        binaryOne = twoComplement(binaryOne);
        binaryTow = twoComplement(binaryTow);
    } else if (boolOne) {
        binaryOne = twoComplement(binaryOne);
    } else if (boolTow) {
        binaryTow = twoComplement(binaryTow);
    }
    if (binaryOne.length() > binaryTow.length()) {
        char digit = '0';
        if (boolTow) {
            digit = '1';
        }
        /**
         * if the length of the number 1 big than the number 2
         * add '0' or '1' to the string.
         */
        binaryTow = addDigit(binaryTow, digit, (int) (binaryOne.length()
                             - binaryTow.length()));
    } else if (binaryOne.length() < binaryTow.length()) {
        char digit = '0';
        if (boolOne) {
            digit = '1';
        }
        binaryOne = addDigit(binaryOne, digit, (int) (binaryTow.length()
                             - binaryOne.length()));
    }
}

/**
 * the function remove prefix '0' from the sting.
 *
 * @param num the given string
 * @return the new string
 */
string InfInt::removeZeroDigit(string num) const {
    string temp = num;
    for (int j = 0; j < num.length(); ++j) {
        if (temp[0] == '0') {
            temp = temp.substr(1, temp.length());
        }
    }
    // if the all string have a zero digit
    if (temp == "") {
        temp = "0";
    }
    return temp;
}

/**
 * the function change from binary to decimal.
 *
 * @param num the binary number
 * @return the decimal number
 */
InfInt InfInt::changeToDecimal(InfInt num) const {
    InfInt pow = InfInt("1");
    InfInt tempPow = InfInt("2");
    InfInt sum = InfInt("0");
    InfInt mult;
    for (int i = num.getLengthString() - 1; i >= 0; i--) {
        mult = InfInt(num.getStringNumber()[i] - '0');
        mult = mult * pow;
        sum = sum + mult;
        pow = pow * tempPow;
    }
    // if the number is negative subtract the last pow from the loop.
    if (num.getSign()) {
        sum = sum - pow;
    }
    string temp = removeZeroDigit(sum.getStringNumber());
    sum.setStringNum(temp);
    return sum;
}

/**
 * The function return the given digit.
 *
 * @param num
 * @param index the given number
 * @return the digit in the given position.
 */
int InfInt::getDigit(InfInt num, int index) const {
    return (int) num.getStringNumber()[index] - 48;
}

/**
 * the function divide string number with the number '2'.
 *
 * @param num the given number
 * @return the new number after the operation
 */
InfInt InfInt::divideWithTwo(InfInt &num) const {
    string resualt = "";
    int i = 0;
    int div = 2;
    int temp = getDigit(num, i);
    while (temp < div) {
        i++;
        if (i < num.getLengthString()) {
            temp = temp * 10 + getDigit(num, i);
        } else {
            break;
        }
    }
    while (num.getLengthString() > i) {
        // Store result in answer
        resualt += (temp / div) + '0';

        // Take next digit of number
        temp = (temp % div) * 10 + getDigit(num, ++i);
    }
    if (resualt.length() == 0)
        return InfInt();
    return InfInt(resualt);
}

/**
 * The function change decimal number to binary.
 *
 * @param num the decimal number
 * @return the binary number
 */
InfInt InfInt::changeToBinary(InfInt &num) const {
    InfInt tempNum = num;
    string binari = "";
    while (tempNum.getStringNumber() != "0") {
        int digit = getDigit(tempNum, tempNum.getLengthString() - 1);
        if (digit % 2 != 0 && digit != 0) {
            binari = '1' + binari;
        } else {
            binari = '0' + binari;
        }
        tempNum = divideWithTwo(tempNum);
    }
    if (binari == "") {
        return InfInt();
    }
    return InfInt(binari);
}

/**
 * the function compare two infint numbers.
 *
 * @param num1 the left number.
 * @param num2 the right number.
 * @return 1 if the left bigger than the right -1 if the left smaller than
 *          the right 0 if the left and the right equal.
 */
int InfInt::compareInfint(const InfInt num1, const InfInt num2) const {
    int lenNum1 = num1.getLengthString();
    int lenNum2 = num2.getLengthString();
    int digit;
    bool flagNeg = false;
    // the loop subtract length to avoid prefix zero.
    for (int j = 0; j < num1.getLengthString(); ++j) {
        digit = getDigit(num1, j);
        if (digit == 0) {
            lenNum1--;
        } else {
            break;
        }
    }
    for (int i = 0; i < num2.getLengthString(); ++i) {
        digit = getDigit(num2, i);
        if (digit == 0) {
            lenNum2--;
        } else {
            break;
        }
    }
    // check if the left are negative and the right positive.
    if (num1.getSign() && !num2.getSign()) {
        return -1;
        // check if the right are negative and the left positive.
    } else if (!num1.getSign() && num2.getSign()) {
        return 1;
        // check if the the two numbers are positive.
    } else if (lenNum1 > lenNum2 && !num1.getSign() && !num2.getSign()) {
        return 1;
    } else if (lenNum1 < lenNum2 && !num1.getSign() && !num2.getSign()) {
        return -1;
        // check if the two number are negative..
    } else if (num1.getSign() && num2.getSign()) {
        flagNeg = true;
    }
    int i = 0;
    // the loop compare the digits to know which is bigger
    while (i < num1.getLengthString()) {
        if (num1.getStringNumber()[i] > num2.getStringNumber()[i]) {
            if (flagNeg) {
                return -1;
            }
            return 1;
        } else if (num2.getStringNumber()[i] > num1.getStringNumber()[i]) {
            if (flagNeg) {
                return 1;
            }
            return -1;
        }
        i++;
    }
    return 0;
}

/**
 * The function cast decimal number to integer
 * number, by cut the 32 bits from right.
 *
 * @return The integer number
 */
InfInt::operator int() {
    string num = changeToBinary(*this).stringNum;
    int sum = 0;
    int pow = 1;
    int sizeInt = sizeof(int);
    // check if the size of the string bigger than 32 bits.
    if (num.length() > sizeof(int) * 8) {
        num = num.substr(num.length() - (sizeInt * 8), num.length() - 1);
    }
    // calculate the decimal number.
    for (int i = (int) num.length() - 1; i >= 0; --i) {
        sum = sum + (num[i] - '0') * pow;
        // if the number of the bit is 32 stop on the 31 bit.
        if ((int) num.length() == 32 && i == 0) {
            break;
        }
        pow *= 2;
    }
    // if the number is negative add the msb;
    if (this->isNeg) {
        sum = sum + pow;
    }
    return sum;
}

/**
 * The function print the infinit number.
 *
 * @param stream
 * @param num
 * @return
 */
ostream &operator<<(ostream &stream, const InfInt &num) {
    if (num.isNeg) {
        stream << '-' + num.stringNum;
    } else {
        stream << num.stringNum;
    }
    return stream;
}

/**
 * The function placement a number in a given Infinit.
 *
 * @param stream
 * @param num
 * @return
 */
istream &operator>>(istream &stream, InfInt &num) {
    string str;
    stream >> str;
    InfInt tempNum = str;
    num = tempNum;
    return stream;
}

/**
 * Shift left operator.
 *
 * @param shifts the amount shifts
 * @return the new number after the operation.
 */
InfInt InfInt::operator>>=(int shifts) {
    *this = *this >> shifts;
    return *this;
}

/**
 * Shift left operator.
 *
 * @param shifts the amount shifts
 * @return the new number after the operation.
 */
InfInt InfInt::operator<<(int shifts) {
    if (shifts == 0) {
        return *this;
    }
    InfInt temp = changeToBinary(*this);
    string binary = temp.getStringNumber();
    for (int i = 0; i < shifts; ++i) {
        binary = binary + '0';
    }
    temp.setStringNum(binary);
    temp = changeToDecimal(temp);
    temp.setIsNeg(this->getSign());
    return temp;
}

/**
 * Shift right operator.
 *
 * @param shifts the amount shifts
 * @return the new number after the operation.
 */
InfInt InfInt::operator>>(int shifts) {
    if (shifts == 0) {
        return *this;
    }
    InfInt temp = changeToBinary(*this);
    string binary = temp.getStringNumber();;
    for (int i = 0; i < shifts; ++i) {
        binary.erase(binary.length() - 1, binary.length());
        if (binary.length() == 0) {
            return InfInt();
        }
    }
    temp.setStringNum(binary);
    temp = changeToDecimal(temp);
    temp.setIsNeg(this->getSign());
    return temp;
}

