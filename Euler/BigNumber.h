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
    
    BigNumber& concat(const BigNumber& other) {
        mDigits.insert(mDigits.end(), other.mDigits.begin(), other.mDigits.end());
        mCached.first = false;
        
        return *this;
    }
    
    BigNumber& operator+=(const BigNumber& other) {
        // todo: do it in-place
        mDigits = std::move(add(mDigits, other.mDigits));
        mCached.first = false;
            
        return *this;
    }
            
    BigNumber& operator*=(const BigNumber& other) {
        mDigits = std::move(multiply(mDigits, other.mDigits));
        mCached.first = false;
        
        return *this;
    }
    
    BigNumber& operator/=(const BigNumber& other) {
        assert(!"Unimplemented");
        return *this;
    }
            
    size_t digits() const {
        return mDigits.size();
    }
            
    unsigned long value() const {
        if(!mCached.first) {
            mCached.second = 0;
            for(int i = 0; i < mDigits.size(); ++i) {
                mCached.second += mDigits[i] * powul(10, i);
            }
            mCached.first = true;
        }
        
        return mCached.second;
    }
            
    operator bool() {
        return value() != 0;
    }
            
    friend std::ostream& operator<<(std::ostream& s, const BigNumber& n);
    friend bool operator<(const BigNumber& a, const BigNumber& b);
    friend bool operator>(const BigNumber& a, const BigNumber& b);
    friend bool operator<=(const BigNumber& a, const BigNumber& b);
    friend bool operator>=(const BigNumber& a, const BigNumber& b);
    friend bool operator==(const BigNumber& a, const BigNumber& b);
    friend bool operator!=(const BigNumber& a, const BigNumber& b);
            
private:
    static const std::vector<char> add(const std::vector<char>& a, const std::vector<char>& b) {
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
    
    static const std::vector<char> multiply(const std::vector<char>& a, const std::vector<char>& b) {
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
    
private:
    mutable std::pair<bool, unsigned long> mCached;
    std::vector<char> mDigits;
};
            
inline std::ostream& operator<<(std::ostream& s, const BigNumber& n) {
    for(int i = (int)n.mDigits.size() -1; i >= 0; --i) {
        s << (int)n.mDigits[i];
    }
    
    return s;
};
        
inline bool operator<(const BigNumber& a, const BigNumber& b) {
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

inline bool operator>(const BigNumber& a, const BigNumber& b) {
    return b < a;
}

inline bool operator<=(const BigNumber& a, const BigNumber& b) {
    return !(a > b);
}

inline bool operator>=(const BigNumber& a, const BigNumber& b) {
    return !(a < b);
}

inline bool operator==(const BigNumber& a, const BigNumber& b) {
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

inline bool operator!=(const BigNumber& a, const BigNumber& b) {
    return !(a == b);
}
        
inline BigNumber operator+(const BigNumber& a, const BigNumber& b) {
    BigNumber result{a};
    result += b;
    
    return result;
}
        
inline BigNumber operator*(const BigNumber& a, const BigNumber& b) {
    BigNumber result{a};
    result *= b;
    
    return result;
}

#endif /* defined(__Euler__BigNumber__) */
