#include "LargeIntegers.h"

/**
 * And operator
 *
 * @param num
 * @return new number after the operation
 */
InfInt InfInt::operator&=(const InfInt &num) {
    *this = *this & num;
    return *this;
}

/**
 * And operator
 *
 * @param num
 * @return new number after the operation
 */
InfInt InfInt::operator&(const InfInt &num) const {
    InfInt num1 = *this;
    InfInt num2 = num;
    // change the number to binary for the binary division.
    string num1S = changeToBinary(num1).stringNum;
    string num2S = changeToBinary(num2).stringNum;
    bool flagNeg = false;
    checkIfToChangeTheBinaryString(num1S, num1.getSign(),
                                  num2S, num2.getSign());
    // check if the numbers are negatives.
    if (num1.getSign() && num2.getSign()) {
        // indication for the next condition.
        flagNeg = true;
    }
    string finalNumber = "";
    int indexNum1 = (int) num1S.length() - 1;
    int indexNum2 = (int) num2S.length() - 1;
    while (indexNum1 >= 0 && indexNum2 >= 0) {
        if (num1S[indexNum1] == num2S[indexNum2] && num1S[indexNum1] == '1') {
            finalNumber = '1' + finalNumber;
        } else {
            finalNumber = '0' + finalNumber;
        }
        indexNum1--;
        indexNum2--;
    }
    InfInt tempInfi = finalNumber;
    if (flagNeg) {
        tempInfi.setIsNeg(true);
    }
    // change the number back to decimal.
    tempInfi = changeToDecimal(tempInfi);
    return tempInfi;
}

/**
 * Xor operator
 *
 * @param num
 * @return new number after the operation
 */
InfInt InfInt::operator^(const InfInt &num) const {
    InfInt num1 = *this;
    InfInt num2 = num;
    string num1S = changeToBinary(num1).stringNum;
    string num2S = changeToBinary(num2).stringNum;
    string finalNumber = "";
    bool flagNeg = false;
    checkIfToChangeTheBinaryString(num1S, num1.getSign(),
            num2S, num2.getSign());
    int indexNum1 = (int) num1S.length() - 1;
    int indexNum2 = (int) num2S.length() - 1;
    // If the signs are opposite for change the sign to negative
    if ((num1.getSign() && !num2.getSign()) ||
        (!num1.getSign() && num2.getSign())) {
        flagNeg = true;
    }
    while (indexNum1 >= 0 && indexNum2 >= 0) {
        if (num1S[indexNum1] == num2S[indexNum2]) {
            finalNumber = '0' + finalNumber;
        } else {
            finalNumber = '1' + finalNumber;
        }
        indexNum1--;
        indexNum2--;
    }
    InfInt tempInfi = finalNumber;
    if (flagNeg) {
        tempInfi.setIsNeg(true);
    }
    tempInfi = changeToDecimal(tempInfi);
    return tempInfi;
}

/**
 * Or operator
 *
 * @param num
 * @return new number after the operation
 */
InfInt InfInt::operator|(const InfInt &num) const {
    InfInt num1 = *this;
    InfInt num2 = num;
    string num1S = changeToBinary(num1).stringNum;
    string num2S = changeToBinary(num2).stringNum;
    string finalNumber = "";
    bool flagNeg = true;
    checkIfToChangeTheBinaryString(num1S, num1.getSign(),
            num2S, num2.getSign());
    // If the signs are negatives for change the sign to negative
    if (!num1.getSign() && !num2.getSign()) {
        flagNeg = false;
    }
    int indexNum1 = (int) num1S.length() - 1;
    int indexNum2 = (int) num2S.length() - 1;
    while (indexNum1 >= 0 && indexNum2 >= 0) {
        if (num1S[indexNum1] == num2S[indexNum2] && num1S[indexNum1] == '0') {
            finalNumber = '0' + finalNumber;
        } else {
            finalNumber = '1' + finalNumber;
        }
        indexNum1--;
        indexNum2--;
    }
    InfInt tempInfi = finalNumber;
    if (flagNeg) {
        tempInfi.setIsNeg(true);
    }
    tempInfi = changeToDecimal(tempInfi);
    return tempInfi;
}