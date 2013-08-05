//
//  BigNumber.cpp
//  Euler
//
//  Created by Artur Mazurek on 05.08.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "BigNumber.h"

#include <ostream>

BigNumber BigNumber::sMax = BigNumber{std::numeric_limits<unsigned long>::max()};
BigNumber BigNumber::sMin = BigNumber{std::numeric_limits<unsigned long>::min()};

BigNumber::BigNumber(ulong value) : mNegative{false} {
    while(value != 0) {
        mDigits.push_back(absT(value % 10));
        value /= 10;
    }
}

BigNumber& BigNumber::concat(const BigNumber& other) {
    mDigits.insert(mDigits.end(), other.mDigits.begin(), other.mDigits.end());
    mCached.first = false;
    
    return *this;
}

BigNumber& BigNumber::operator+=(const BigNumber& other) {
    // todo: do it in-place
    mDigits = std::move(add(mDigits, other.mDigits));
    mCached.first = false;
    
    return *this;
}

BigNumber& BigNumber::operator*=(const BigNumber& other) {
    mNegative = mNegative ^ other.mNegative;
    
    mDigits = std::move(multiply(mDigits, other.mDigits));
    mCached.first = false;
    
    return *this;
}

BigNumber& BigNumber::operator/=(const BigNumber& other) {
    mNegative = mNegative ^ other.mNegative;
    
    assert(!"Unimplemented");
    return *this;
}

size_t BigNumber::digits() const {
    return mDigits.size();
}

unsigned long BigNumber::value() const {
    if(!mCached.first) {
        if(*this > sMax || *this < sMin) {
            throw BigNumberException("Number out of built-in bounds");
        }
        
        mCached.second = 0;
        for(int i = 0; i < mDigits.size(); ++i) {
            mCached.second += mDigits[i] * powT<unsigned long>(10, i);
        }
        mCached.first = true;
    }
    
    return mCached.second;
}

BigNumber::operator bool() const {
    return value() != 0;
}

const std::vector<char> BigNumber::add(const std::vector<char>& a, const std::vector<char>& b) {
    std::vector<char> result;
    
    char overflow = 0;
    
    auto end = std::max(a.size(), b.size());
    for(int i = 0; i < end; ++i) {
        overflow += i < a.size() ? a[i] : 0;
        overflow += i < b.size() ? b[i] : 0;
        
        result.push_back(overflow % 10);
        overflow /= 10;
    }
    
    if(overflow) {
        result.push_back(overflow);
    }
    
    return result;
}

const std::vector<char> BigNumber::multiply(const std::vector<char>& a, const std::vector<char>& b) {
    std::vector<char> result;
    
    for(int i = 0; i < a.size(); ++i) {
        std::vector<char> temp(i, 0);
        char overflow = 0;
        
        for(int j = 0; j < b.size(); ++j) {
            overflow += a[i] * b[j];
            temp.push_back(overflow % 10);
            overflow /= 10;
        }
        
        if(overflow) {
            temp.push_back(overflow);
        }
        
        result = add(result, temp);
    }
    
    return result;
}

// Operators -----------------

std::ostream& operator<<(std::ostream& s, const BigNumber& n) {
    for(int i = (int)n.mDigits.size() -1; i >= 0; --i) {
        s << (int)n.mDigits[i];
    }
    
    return s;
}

bool operator<(const BigNumber& a, const BigNumber& b) {
    if(a.digits() != b.digits()) {
        return a.digits() < b.digits();
    }
    
    for(int i = (int)a.digits()-1; i >= 0; --i) {
        if(a.mDigits[i] != b.mDigits[i]) {
            return a.mDigits[i] < b.mDigits[i];
        }
    }
    
    return false; //equal
}

bool operator>(const BigNumber& a, const BigNumber& b) {
    return b < a;
}

bool operator<=(const BigNumber& a, const BigNumber& b) {
    return !(a > b);
}

bool operator>=(const BigNumber& a, const BigNumber& b) {
    return !(a < b);
}

bool operator==(const BigNumber& a, const BigNumber& b) {
    if(a.digits() != b.digits()) {
        return false;
    }
    
    for(size_t i = 0; i < a.digits(); ++i) {
        if(a.mDigits[i] != b.mDigits[i]) {
            return false;
        }
    }
    
    return true;
}

bool operator!=(const BigNumber& a, const BigNumber& b) {
    return !(a == b);
}

BigNumber operator+(const BigNumber& a, const BigNumber& b) {
    BigNumber result{a};
    result += b;
    
    return result;
}

BigNumber operator*(const BigNumber& a, const BigNumber& b) {
    BigNumber result{a};
    result *= b;
    
    return result;
}
