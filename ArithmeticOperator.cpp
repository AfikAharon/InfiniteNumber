#include "LargeIntegers.h"
/**
 * The function reverse the string.
 *
 * @param number the given string to swap.
 */
void reverseString(string &number) {
    int i = 0;
    int j = (int)number.length() - 1;
    char temp;
    while (i <= j) {
        temp = number[i];
        number[i] = number[j];
        number[j] = temp;
        i++;
        j--;
    }
}

/**
 * Pre increasement operator
 *
 * @return new number after the operation
 */
InfInt InfInt::operator++() {
    InfInt infi = "1";
    *this = *this + infi;
    return *this;
}

/**
 * Post increasement operator
 *
 * @param notused dummy
 * @return new number after the operation
 */
InfInt InfInt::operator++(int notused) {
    InfInt infi = *this;
    ++*this;
    return infi;
}

/**
 * Pre subtract operator
 *
 * @return new number after the operation
 */
InfInt InfInt::operator--() {
    InfInt infi = "1";
    *this = *this - infi;
    return *this;
}

/**
 * Post subtract operator
 *
 * @param notused dummy
 * @return new number after the operation
 */InfInt InfInt::operator--(int notused) {
    InfInt infi = *this;
    --*this;
    return infi;
}

/**
 * Plus operator
 *
 * @param num the right number
 * @return new number after the operation
 */
InfInt InfInt::operator+(const InfInt &num) const {
    string tempS = "";
    int plus;
    int frac = 0;
    InfInt num1 = *this;
    InfInt num2 = num;
    InfInt maxNum;
    InfInt smalNum;
    int result = compareInfint(num1, num2);
    // check if the left and right number negative.
    if (num1.getSign() && num2.getSign()) {
        num2.setIsNeg(false);
        return num1 - num2;
    } else if (num1.getSign() && !num2.getSign()) {
        num1.setIsNeg(false);
        return num2 - num1;
    } else if (!num1.getSign() && num2.getSign()) {
        num2.setIsNeg(false);
        return num1 - num2;
    }
    if (result == 1) {
        maxNum = num1;
        smalNum = num2;
    } else if (result == -1) {
        maxNum = num2;
        smalNum = num1;
    } else {
        maxNum = num1;
        smalNum = num2;
    }
    int indexMax = (int) maxNum.stringNum.length() - 1;
    int indexSmal = (int) smalNum.stringNum.length() - 1;
    while (indexMax >= 0 || indexSmal >= 0) {
        int digitMaxNum;
        int digitSmalNum;
        // if there is no more digits
        if (indexMax < 0) {
            digitMaxNum = -1;
        } else {
            digitMaxNum = getDigit(maxNum, indexMax);
        }
        // if there is no more digits
        if (indexSmal < 0) {
            digitSmalNum = -1;
        } else {
            digitSmalNum = getDigit(smalNum, indexSmal);
        }
        // if digitSmalNum < 0 avoid the digitSmalNum.
        if (digitSmalNum < 0) {
            plus = digitMaxNum + frac;
        } else if (digitMaxNum < 0) {
            plus = digitSmalNum + frac;
        } else {
            plus = digitSmalNum + digitMaxNum + frac;
        }
        // if plus >= 10 calculate the carry.
        if (plus >= 10) {
            plus = plus - 10;
            frac = 1;
        } else {
            frac = 0;
        }
        tempS.insert(0, intToString(plus));
        indexMax--;
        indexSmal--;
    }
    if (frac == 1) {
        tempS.insert(0, intToString(frac));
    }
    tempS = removeZeroDigit(tempS);
    // if the value number is 0;
    if (tempS == "") {
        tempS.insert(0, "0");
    }
    return InfInt(tempS);
}

/**
 * Plus operator
 *
 * @param num the right number
 * @return new number after the operation
 */
InfInt InfInt::operator+=(const InfInt &num) {
    *this = *this + num;
    return *this;
}

/**
 * The function check the sign number for the Minus function, and call
 * to the correct function.
 *
 * @param num1 the left number
 * @param num2 the right number
 * @param flag indiction for the minus function that the
 *              function do the operation
 * @return the new number after the operation otherwise null
 */
InfInt checkTheSignNumbers(InfInt num1, InfInt num2, bool *flag) {
    // check the signed numbers
    if (num1.getSign() && num2.getSign()) {
        num1.setIsNeg(false);
        num2.setIsNeg(false);
        *flag = true;
        // if the expression is from of (-x - (-y))
        return num2 - num1;
    } else if (num1.getSign() && !num2.getSign()) {
        num1.setIsNeg(false);
        InfInt retuNum = num1 + num2;
        retuNum.setIsNeg(true);
        *flag = true;
        // if the expression is from of (-x - y))
        return retuNum;
    } else if (!num1.getSign() && num2.getSign()) {
        num2.setIsNeg(false);
        *flag = true;
        // if the expression is from of (x - (-y))
        return num1 + num2;
    }
    return InfInt();
}

/**
 * Subtract operator
 *
 * @param num the right number
 * @return new number after the operation
 */
InfInt InfInt::operator-(const InfInt &num) const {
    InfInt num1 = *this, num2 = num, temp, maxNum, smalNum;
    string tempS = "";
    bool flagReturn = false;
    int merge, rest = 0;
    temp = checkTheSignNumbers(num1, num2, &flagReturn);
    // check if  the function checkTheSignNumbers change the operation.
    if (flagReturn) {
        return temp;
    }
    int result = compareInfint(num1, num2);
    if (result == 1) {
        maxNum = num1;
        smalNum = num2;
    } else if (result == -1) {
        maxNum = num2;
        smalNum = num1;
    } else {
        return InfInt("0");
    }
    int indexMax = (int) maxNum.stringNum.length() - 1;
    int indexSmall = (int) smalNum.stringNum.length() - 1;
    bool flagNine = false;
    while (indexMax >= 0 && indexSmall >= 0) {
        merge = getDigit(maxNum, indexMax) -
                getDigit(smalNum, indexSmall) + rest;
        // check if the prev digit is '0' to change the prev digit to 9.
        if ((getDigit(maxNum, indexMax) == 0 && merge != 0) && (indexMax > 0
             && getDigit(maxNum, indexMax - 1) == 0)) {
            // indication for the next conditions
            flagNine = true;
            rest = 9;
            if (merge < 0) {
                merge = merge + 10;
            }
        } else if (merge < 0) {
            rest = -1;
            merge = merge + 10;
        } else if (rest == 9 && merge >= 0 && merge < 10) {
            rest = -1;
        } else {
            rest = 0;
        }
        tempS.insert(0, intToString(merge));
        indexMax--;
        indexSmall--;
    }
    // if there is more digit in the max number
    if (indexMax >= 0 && !flagNine) {
        // check if there is carry and the indexMax point to the first digit
        if (rest == -1 && indexMax == 0) {
            tempS.insert(0, intToString(getDigit(maxNum, 0) + rest));
        } else if (rest == -1 && indexMax > 0) {
            // if there is '0' digits swap the digit to'9'
            if (getDigit(maxNum, indexMax) == 0) {
                while (getDigit(maxNum, indexMax) == 0 && indexMax >= 0) {
                    tempS.insert(0, intToString(9));
                    indexMax--;
                }
            }
            tempS.insert(0, intToString(getDigit(maxNum, indexMax) + rest));
            indexMax--;
            // add the remain digits
            tempS.insert(0, maxNum.stringNum.substr(0, indexMax + 1));
        } else {
            tempS.insert(0, maxNum.stringNum.substr(0, indexMax + 1));
        }
    } else if (indexMax >= 0 && flagNine) {
        while (getDigit(maxNum, indexMax) == 0 && indexMax >= 0) {
            tempS.insert(0, intToString(9));
            indexMax--;
        }
        tempS.insert(0, intToString(getDigit(maxNum, indexMax) - 1));
        indexMax--;
        if (indexMax >= 0) {
            tempS.insert(0, maxNum.stringNum.substr(0, indexMax + 1));
        }
    }
    InfInt infint = InfInt(tempS);
    /**
      * if the right number big than the left number change
      * the number to negative.
     */
    if (result == -1) {
        infint.setIsNeg(true);
    }
    infint.stringNum = removeZeroDigit(infint.stringNum);
    return infint;
}

/**
 * Multiplication operator
 *
 * @param num the right number
 * @return new number after the operation
 */
InfInt InfInt::operator*(const InfInt &num) const {
   int indication = compareInfint(*this, num);
   string smallS;
   string bigS;
   bool flagNeg = false;
   // Check which is bigger.
   if (indication == -1) {
       bigS = num.getStringNumber();
       smallS = this->getStringNumber();
   } else if (indication == 1) {
       bigS = this->getStringNumber();
       smallS = num.getStringNumber();
   } else {
       bigS = this->getStringNumber();
       smallS = num.getStringNumber();
   }
   if ((this->getSign() && ! num.getSign()) || (!this->getSign() && num.getSign())) {
       flagNeg = true;
   }
   reverseString(bigS);
   reverseString(smallS);
   int rest = 0;
   string result;
   InfInt newNumber = InfInt();
   for (int i = 0; i < smallS.length(); ++i) {
       for (int j = 0; j < bigS.length(); ++j) {
           rest = rest + (smallS[i] - '0') * (bigS[j] - '0');
           result += intToString(rest % 10);
           rest = rest / 10;
       }
       if (rest != 0) {
           result += intToString(rest);
           rest = 0;
       }
       reverseString(result);
       int t = i;
       while (t > 0) {
           result += "0";
           t = t - 1;
       }
       while (result[0] == '0' && result.length() > 1) {
           result = result.substr(1, result.length());
       }
       InfInt temp = InfInt(result);
       // plus the result
       newNumber += temp;
       result = "";
   }
   if (flagNeg) {
       newNumber.setIsNeg(true);
   }
   return newNumber;
}

/**
* Division operator
*
* @param num the right number
* @return new number after the operation
*/
InfInt InfInt::operator/(const InfInt &num) const {
    InfInt num1 = *this;
    InfInt num2 = num;
    string numerator = changeToBinary(num1).stringNum;
    string denominator = changeToBinary(num2).stringNum;
    string rest = "0";
    string result = "";
    bool flag = false;
    // If the signs are opposite for change the sign to negative
    if ((num1.getSign() && !num2.getSign()) || (!num1.getSign()
             && num2.getSign())) {
        flag = true;
    }
    num1.setIsNeg(false);
    num2.setIsNeg(false);
    InfInt restInf;
    InfInt denominatorInf;
    if (num2.stringNum == "0") {
        throw "Cannot divide by zero";
    }
    // add zero digit to the result number.
    for (int j = 0; j < numerator.length(); ++j) {
        result += '0';
    }
    // the loop do a long divide.
    for (int i = 0; i < numerator.length(); i++) {
        rest.insert(rest.length(), "0");
        rest[rest.length() - 1] = numerator[i];
        restInf = changeToDecimal(rest);
        denominatorInf = changeToDecimal(denominator);
        if (restInf >= denominatorInf) {
            restInf = restInf - denominatorInf;
            result[i] = '1';
            rest = changeToBinary(restInf).stringNum;
        }
    }
    InfInt finalNum = changeToDecimal(result);
    // check if the number negative and not equal to zero.
    if (flag && !(finalNum.stringNum == "0")) {
        finalNum.setIsNeg(true);
    }
    return finalNum;
}

/**
 * Modulo operator
 *
 * @param num the right number
 * @return new number after the operation
 */
InfInt InfInt::operator%(const InfInt &num) const {
    InfInt tempNum1 = *this;
    InfInt tempNum2 = num;
    bool flagNeg1 = false;
    bool flagNeg2 = false;
    bool flagNeg3 = false;
    if ((tempNum1.getSign() && !tempNum2.getSign())) {
        flagNeg1 = true;
    } else if (tempNum1.getSign() && tempNum2.getSign()) {
        flagNeg2 = true;

    } else if (!tempNum1.getSign() && tempNum2.getSign()) {
        flagNeg3 = true;
    }
    tempNum1.setIsNeg(false);
    tempNum2.setIsNeg(false);
    /* divide the left number with the modulo number after that
     * subtract the left number with the result and we get the rest.
    */
    InfInt rest = tempNum1 / tempNum2;
    rest = rest * tempNum2;
    rest = tempNum1 - rest;
    if (rest.stringNum == "0") {
        return rest;
    }
    // if the left number is negative and the modulo is positive.
    if (flagNeg1) {
        rest.setIsNeg(true);
        return rest;
    }
    // if the modulo is negative number and the left number positive.
    if (flagNeg3) {
        rest = tempNum2 - rest;
        rest.setIsNeg(true);
        return rest;
    }
    // if both numbers are negative.
    if (flagNeg2) {
        rest.setIsNeg(true);
    }
    return rest;
}