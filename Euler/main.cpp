//
//  main.cpp
//  Euler
//
//  Created by Artur Mazurek on 09/08/2012.
//  Copyright (c) 2012 Artur Mazurek. All rights reserved.
//

#include <cmath>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "unistd.h"

using namespace std;

static const int MILION = 1000000;

inline long toNumber(char c);
inline long toNumber(const vector<int>& digits);
template <typename bidirectional_iterator>
inline long toNumber(bidirectional_iterator begin, bidirectional_iterator end);
inline bool isPrime(unsigned int n);
inline unsigned long lowestDivisor(unsigned long n);
inline long powd(long x, long power);

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(*x))

void problem39();
void problem40();
void problem41();
void problem42();
void problem43();
void problem44();

int main(int argc, const char * argv[])
{
//    char path[1024];
//    getcwd(path, sizeof(path));
//    cout << path << endl;
    
    problem43();
}

inline long toNumber(char c) {
    return c - '0';
}

inline long toNumber(const vector<int>& digits) {
    return toNumber(digits.begin(), digits.end());
}

template <typename bidirectional_iterator>
inline long toNumber(bidirectional_iterator begin, bidirectional_iterator end) {
    unsigned int power = 0;
    long result = 0;
    while(end != begin) {
        --end;
        result += powd(10, power) * (*end);
        ++power;  
    }
    
    return result;
}

inline bool isPrime(unsigned int n) {
    return lowestDivisor(n) == n;
}

// For obvious reasons does not take 1 into account
inline unsigned long lowestDivisor(unsigned long n) {
    if (n <= 1) {
        return n;
    }
    for (unsigned int i = 2; i*i <= n; ++i) {
        if (n % i == 0) {
            return i;
        }
    }
    return n;
}

inline long powd(long x, long power) {
    long temp = x;
    
    if(power == 0) {
        return 1;
    }
    while(--power) {
        temp *= x;
    }
    return temp;
}

void _fillWithTriangles(const int p, map<int, int>& count) {
    if(p == 3) {
        return;
    }
    
    for(int c = p-2; c >= 0; --c) {
        for(int b = p-1-c; b >= 0; --b) {
            int a = p-b-c;
            if(a > b) {
                break;
            }
            if(c*c == a*a + b*b) {
                count[p] += 1;
            }
        }
    }
    
    _fillWithTriangles(p-1, count);
}

void problem39() {
    map<int, int> triangles;
    int P = 1000;
    
    _fillWithTriangles(P, triangles);
    
    int max = numeric_limits<int>::min();
    int maxP = -1;
    for(map<int, int>::iterator it = triangles.begin(); it != triangles.end(); ++it) {
        if(it->second > max) {
            maxP = it->first;
            max = it->second;
        }
    }
    
    cout << maxP << endl;
}

void problem40() {
    string decimal = "."; // to help with indexing from 0
    int i = 1;
    while(decimal.length() <= MILION) {
        stringstream ss;
        ss << i;
        decimal += ss.str();
        ++i;
    }
    
    cout << toNumber(decimal[1]) * toNumber(decimal[10]) * toNumber(decimal[100]) * toNumber(decimal[1000])
            * toNumber(decimal[10000]) * toNumber(decimal[100000]) * toNumber(decimal[1000000]) << endl;
}

bool _isPandigital(int n) {
    vector<int> digits;
    
    while(n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
    
    sort(digits.begin(), digits.end());
    for(int i = 0; i < digits.size(); ++i) {
        if(digits[i] != i+1) {
            return false;
        }
    }
    
    return true;
}

void problem41() {
    for(int N = 9; N >= 1; --N) {
        std::vector<int> digits;
        for(int i = N; i >= 1; --i) {
            digits.push_back(i);
        }
        
        do {
            int value = (int)toNumber(digits);
            if(isPrime(value)) {
                cout << value << endl;
                return;
            }
        } while (prev_permutation(digits.begin(), digits.end()));
    }
}

// This method has an issue - does not load "A" but counts it eventhough. So in the end it gives proper results.
void problem42() {
    ifstream f("words.txt");
    string words;
    f >> words;
    
    size_t start = 0;
    size_t end = 0;
    
    int result = 0;
    const int N = 100000;
    int triangles[N] = {0};
    for(int i = 0; i < N; ++i) {
        triangles[i] = i * (i + 1) / 2;
    }
    
    while(true) {
        start = end;
        end = words.find(string(","), start+1);
        
        if(end == string::npos) {
            break;
        }
        
        string word = words.substr(start+2, end-start-3);
     
        int wordValue = 0;
        for(int i = 0; i < word.size(); ++i) {
            wordValue += word[i] - 'A' + 1; // A is 1
        }
        
        for(int i = 0; i < N; ++i) {
            if(wordValue == triangles[i]) {
                ++result;
            }
        }
    }
    
    cout << result << endl;
}

void problem43() {
    long result = 0;
    
    int digits[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//    1406357289
//    int digits[] = {1, 4, 0, 6, 3, 5, 7, 2, 8, 9};
//    vector<int> digits(_digits, _digits + ARRAY_SIZE(_digits));
    
    do {
        if((toNumber(digits + 1, digits + 4)) % 2 != 0) {
            continue;
        }
        if((toNumber(digits + 2, digits + 5)) % 3 != 0) {
            continue;
        }
        if((toNumber(digits + 3, digits + 6)) % 5 != 0) {
            continue;
        }
        if((toNumber(digits + 4, digits + 7)) % 7 != 0) {
            continue;
        }
        if((toNumber(digits + 5, digits + 8)) % 11 != 0) {
            continue;
        }
        if((toNumber(digits + 6, digits + 9)) % 13 != 0) {
            continue;
        }
        if((toNumber(digits + 7, digits + 10)) % 17 != 0) {
            continue;
        }
        
        unsigned long number = toNumber(digits, digits + ARRAY_SIZE(digits));
        result += number;
    } while (next_permutation(digits, digits + ARRAY_SIZE(digits)));
    
    cout << result << endl;
}
