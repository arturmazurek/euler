//
//  util.h
//  Euler
//
//  Created by Artur Mazurek on 05/08/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Euler_util_h
#define Euler_util_h

typedef unsigned long ulong;

template <typename T>
static inline long powT(const T& x, T power) {
    T temp = x;
    
    if(power == 0) {
        return 1;
    }
    while(--power) {
        temp *= x;
    }
    return temp;
}

template <typename T>
static inline long absT(const T& x) {
    return x > 0 ? x : -x;
}

#endif
