//
//  BigNumber.h
//  Euler
//
//  Created by Artur Mazurek on 02/08/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Euler__BigNumber__
#define __Euler__BigNumber__

#include <algorithm>
#include <cassert>  
#include <limits>
#include <vector>

#include "util.h"

class BigNumber {
public:
    template <typename T>
    explicit BigNumber(T value = 0) {
        while(value > 0) {
            mDigits.push_back(value % 10);
            value /= 10;
        }
    }
    
    BigNumber& concat(const BigNumber& other);
    
    BigNumber& operator+=(const BigNumber& other);
    BigNumber& operator*=(const BigNumber& other);
    BigNumber& operator/=(const BigNumber& other);
            
    size_t digits() const;
            
    unsigned long value() const;
            
    explicit operator bool() const;
            
    friend std::ostream& operator<<(std::ostream& s, const BigNumber& n);
    friend bool operator<(const BigNumber& a, const BigNumber& b);
    friend bool operator>(const BigNumber& a, const BigNumber& b);
    friend bool operator<=(const BigNumber& a, const BigNumber& b);
    friend bool operator>=(const BigNumber& a, const BigNumber& b);
    friend bool operator==(const BigNumber& a, const BigNumber& b);
    friend bool operator!=(const BigNumber& a, const BigNumber& b);
    
    friend BigNumber operator+(const BigNumber& a, const BigNumber& b);
    friend BigNumber operator*(const BigNumber& a, const BigNumber& b);
            
private:
    static const std::vector<char> add(const std::vector<char>& a, const std::vector<char>& b);
    static const std::vector<char> multiply(const std::vector<char>& a, const std::vector<char>& b);
    
private:
    static BigNumber sMax;
    
    mutable std::pair<bool, unsigned long> mCached;
    std::vector<char> mDigits;
    bool mSign;
};

#endif /* defined(__Euler__BigNumber__) */
