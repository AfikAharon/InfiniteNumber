#include "LargeIntegers.h"

/**
 * The function check if the left number smaller than the right number.
 *
 * @param num the right number
 * @return true or false
 */
bool InfInt::operator<(const InfInt &num) const {
    if (compareInfint(*this, num) == -1) {
        return true;
    } else {
        return false;
    }
}

/**
 * The function check if the left number equal to the right number.
 *
 * @param num the right number
 * @return true or false
 */
bool InfInt::operator==(InfInt &num) const {
    if (compareInfint(*this, num) == 0) {
        return true;
    } else {
        return false;
    }
}

/**
 * The function check if the left number smaller
 * or equal than the right number.
 *
 * @param num the right number
 * @return true or false
 */
bool InfInt::operator<=(const InfInt &num) const {
    if (compareInfint(*this, num) == -1 || compareInfint(*this, num) == 0) {
        return true;
    } else {
        return false;
    }
}

/**
 * The function check if the left number bigger than the right number.
 *
 * @param num the right number
 * @return true or false
 */
bool InfInt::operator>(const InfInt &num) const {
    if (compareInfint(*this, num) == 1) {
        return true;
    } else {
        return false;
    }
}

/**
 * The function check if the left number bigger or equal than the right number.
 *
 * @param num the right number
 * @return true or false
 */
bool InfInt::operator>=(const InfInt &num) const {
    if (compareInfint(*this, num) == 1 || compareInfint(*this, num) == 0) {
        return true;
    } else {
        return false;
    }
}