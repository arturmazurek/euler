//
//  BigNumber.h
//  Euler
//
//  Created by Artur Mazurek on 02/08/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Euler__BigNumber__
#define __Euler__BigNumber__

#include <vector>

class BigNumber {
public:
    template <typename T>
    BigNumber(T value = 0) {
        while(value > 0) {
            mDigits.push_back(value % 10);
            value /= 10;
        }
    }
    
    BigNumber& operator+=(const BigNumber& other) {
        std::vector<char> result;
        
        char overflow = 0;
        
        auto end = std::max(mDigits.size(), other.mDigits.size());
        for(int i = 0; i < end; ++i) {
            overflow += i < mDigits.size() ? mDigits[i] : 0;
            overflow += i < other.mDigits.size() ? other.mDigits[i] : 0;
            
            result.push_back(overflow % 10);
            overflow /= 10;
        }
            
        if(overflow) {
            result.push_back(overflow);
        }
        
        
        mDigits = std::move(result);
            
        return *this;
    }
            
    size_t digits() const {
        return mDigits.size();
    }
            
    operator bool() {
        for(auto digit : mDigits) {
            if(digit != 0) {
                return true;
            }
        }
        
        return false;
    }
            
    friend std::ostream& operator<<(std::ostream& s, const BigNumber& n);
    
private:
    std::vector<char> mDigits;
};
            
inline std::ostream& operator<<(std::ostream& s, const BigNumber& n) {
    for(int i = (int)n.mDigits.size() -1; i >= 0; --i) {
        s << (int)n.mDigits[i];
    }
    
    return s;
};

#endif /* defined(__Euler__BigNumber__) */
