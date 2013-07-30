//
//  main.cpp
//  Euler
//
//  Created by Artur Mazurek on 09/08/2012.
//  Copyright (c) 2012 Artur Mazurek. All rights reserved.
//

#include <cmath>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "unistd.h"

using namespace std;

static const int MILION = 1000000;

typedef unsigned long ulong;

inline long toNumber(char c);
inline long toNumber(const vector<int>& digits);
template <typename bidirectional_iterator>
inline long toNumber(bidirectional_iterator begin, bidirectional_iterator end);
inline bool isPrime(ulong n);
inline unsigned long lowestDivisor(unsigned long n);
static inline long powd(long x, long power);

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(*x))

void problem39();
void problem40();
void problem41();
void problem42();
void problem43();
void problem44();
void problem45();
void problem46();
void problem47();
void problem48();
void problem49();
void problem50();
void problem51();
void problem52();
void problem53();
void problem54();

int main(int argc, const char * argv[])
{
//    char path[1024];
//    getcwd(path, sizeof(path));
//    cout << path << endl;
    
    problem54();
}

inline long toNumber(char c) {
    return c - '0';
}

template <class ContainerT>
inline long toNumber(ContainerT& digits) {
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

std::vector<char> toDigits(ulong number) {
    std::vector<char> result;
    
    while(number) {
        result.push_back(number % 10);
        number /= 10;
    }
    
    return result;
}

inline bool isPrime(ulong n) {
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

static inline long powd(long x, long power) {
    long temp = x;
    
    if(power == 0) {
        return 1;
    }
    while(--power) {
        temp *= x;
    }
    return temp;
}

static inline long powul(ulong x, ulong power) {
    ulong temp = x;
    
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
            ulong value = toNumber(digits);
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

ulong _getPolygonalNumber(ulong n) {
    return n * (3*n - 1) / 2;
}

void problem44() {
    int N = 10000;
    ulong polygons[N];
    set<ulong> polygonsSet;
    
    for(int i = 0; i < N; ++i) {
        polygons[i] = _getPolygonalNumber(i+1);
        polygonsSet.insert(polygons[i]);
    }
    
    // Two polygonal numbers pk and pj create pn
    // suppose pk is smaller. Then pj-pk == D
    // Then pj == pk + D
    // 2pk + D == pn
    // since we want the smallest D we can  iterate from it
    
    for(int i = 0; i < N; ++i) {
        unsigned long d = polygons[i];
        for(int k = 0; k < N; ++k) {
            ulong pk = polygons[k];
            
            ulong pn = 2 * pk + d;
            if(polygonsSet.count(pn)) {
                if(polygonsSet.count(d + pk)) {
                    cout << d << endl;
                    return;
                }
            }
        }
    }
    
    cout << "Not found" << endl;
}

ulong _getTriangleNumber(ulong n) {
    return n * (n + 1) / 2;
}

ulong _getHexagonalNumber(ulong n) {
    return n * (2*n - 1);
}

ulong _getPentagonalNumber(ulong n) {
    return n * (3*n - 1) / 2;
}

void problem45() {
    set<ulong> triangle;
    set<ulong> pentagon;
    vector<ulong> hexagon;
    
    int N = 100000;
    for(int i = 0; i < N; ++i) {
        triangle.insert(_getTriangleNumber(i));
        pentagon.insert(_getPentagonalNumber(i));
        hexagon.push_back(_getHexagonalNumber(i));
    }
    
    for(int i = 144; i < hexagon.size(); ++i) { // we start from 144
        ulong number = hexagon[i];
        if(number == 40755)  {
            continue; // the number given as example in the problem
        }
        if(triangle.count(number) && pentagon.count(number)) {
            cout << number << endl;
            return;
        }
    }
    
    cout << "Not found" << endl;
}

bool _canBeWrittenAsPrimeAndTwiceASquare(ulong n) {
    for(int i = 1; 2*i*i < n; ++i) {
        ulong possiblePrime = n - 2*i*i;
        if(isPrime(possiblePrime)) {
            return true;
        }
    }
    return false;
}

void problem46() {
    ulong i =5;
    while(true) {
        if(!_canBeWrittenAsPrimeAndTwiceASquare(i)) {
            if(!isPrime(i)) {
                cout << i << endl;
                return;
            }
        }
        i+=2;
    }
}

void _getPrimeFactors(ulong n, set<int>& digits) {
    if(n == 1) {
        return;
    }
    for(int i = 2; i <= n/2+1; ++i) {
        if(n % i == 0) {
            digits.insert(i);
            _getPrimeFactors(n/i, digits);
            return;
        }
    }
    digits.insert((int)n);
    return;
}

void problem47() {
    set<int> digits1;
    set<int> digits2;
    set<int> digits3;
    set<int> digits4;
    
    int N = 4;
    
    ulong i = 1;
    while(++i) {
        if(digits1.empty()) {
            _getPrimeFactors(i, digits1);
        }
        if(digits1.size() != N) {
            digits1.clear();
            continue;
        }
        if(digits2.empty()) {
            _getPrimeFactors(i+1, digits2);
        }
        if(digits1 == digits2) {
            digits1 = digits2;
            digits2.clear();
            ++i;
            continue;
        }
        
        if(digits3.empty()) {
            _getPrimeFactors(i+2, digits3);
        }
        if(digits3 == digits2) {
            digits1 = digits3;
            digits2.clear();
            digits3.clear();
            i+=2;
            continue;
        }
            
        if(digits4.empty()) {
            _getPrimeFactors(i+3, digits4);
        }
        if(digits4 == digits3) {
            digits1 = digits4;
            digits2.clear();
            digits3.clear();
            digits4.clear();
            i+=3;
            continue;
        }
        
        if(digits1.size() == N && digits2.size() == N && digits3.size() == N && digits4.size() == N) {
            cout << i << endl;
            return;
        }
        
        digits1.clear();
        digits2.clear();
        digits3.clear();
        digits4.clear();
    }
}

template <int N>
void add(const int a[N], const int b[N], int res[N]) {
    int over = 0;
    for(int i = N-1; i >=0; --i) {
        res[i] = a[i] + b[i] + over;
        over = res[i] / 10;
        res[i] %= 10;
    }
}

template <int N>
void multiply(const int a[N], const int b[N], int res[N]) {    
    for(int i = N-1; i >= 0; --i) {
        int temp[N];
        memset(temp, 0, sizeof(temp));
        
        int over = 0;
        for(int j = N-1; j >= 0; --j) {
            int index = j - (N-i-1);
            if(index < 0) {
                break;
            }
            
            temp[index] = b[i] * a[j] + over;
            over = temp[index] / 10;
            temp[index] %= 10;
        }
        add<N>(temp, res, res);
    }
}

void problem48() {
    constexpr int N = 10;
    int n = 1000;
    
    int sum[N];
    memset(sum, 0, sizeof(sum));
    for(int i = 1; i <= n; ++i) {
        int a[N];
        int temp = i;
        for(int j = N-1; j >= 0; --j) {
            a[j] = temp % 10;
            temp /= 10;
        }
        
        int b[N];
        memcpy(b, a, sizeof(b));
        
        int res[N];
        for(int j = 1; j < i; ++j) {
            memset(res, 0, sizeof(res));
            multiply<N>(a, b, res);
            memcpy(a, res, sizeof(a));
        }
        
        add<N>(a, sum, sum);
    }
    for(int i = 0; i < N; ++i) {
        std::cout << sum[i];
    }
}

template <int N>
bool isPerm(int a, int b) {
    int arrA[N];
    for(int i = N-1; i >= 0; --i) {
        arrA[i] = a % 10;
        a /= 10;
    }
    
    int arrB[N];
    for(int i = N-1; i >= 0; --i) {
        arrB[i] = b % 10;
        b /= 10;
    }
    
    sort(arrA, arrA + N);
    sort(arrB, arrB + N);
    
    return memcmp(arrA, arrB, sizeof(arrA)) == 0;
}

void problem49() {
    for(int i = 1000; i <= 9999; ++i) {
        int a = i;
        
        if(!isPrime(a)) {
            continue;
        }
        
        for(int j = 1000; j <= 9999; ++j) {
            int b = a + j;
            int c = a + 2*j;
            
            if(a > 9999 || b > 9999 || c > 9999) {
                break;
            }
            
            if(!(isPrime(b) && isPrime(c))) {
                continue;
            }
            
            if(!isPerm<4>(a, b) || !isPerm<4>(a, c)) {
                continue;
            }
            
            cout << a << " " << b << " " << c << " (" << j << ")" << endl;
        }
    }
}

static vector<int> _getPrimes(int upTo) {
    vector<int> result;
    for(int i = 2; i <= upTo; ++i) {
        if(isPrime(i)) {
            result.push_back(i);
        }
    }
    return result;
}

void problem50() {
    vector<int> primes = _getPrimes(MILION);
    
    int maxLen = numeric_limits<int>::min();
    int maxNumber = numeric_limits<int>::min();
    
    for(int i = 0; i < primes.size(); ++i) {
        int sum = primes[i];
        int j = i + 1;
        for(; j < primes.size(); ++j) {
            sum += primes[j];
            if(sum > MILION) {
                break;
            }
            
            if(isPrime(sum)) {
                if(j - i > maxLen) {
                    maxLen = j - i;
                    maxNumber = sum;
                }
            }
        }
    }
    
    cout << maxNumber;
}

static ulong _factorial(ulong n) {
    ulong result = 1;
    while(n > 1) {
        result *= n;
        --n;
    }
    return result;
}

static ulong _newtonSymbol(ulong n, ulong k) {
    return (_factorial(n) / (_factorial(k)*_factorial(n-k)));
}

// returns true if more permutations available, false otherwise
bool _nextPerm(vector<bool>& wildcards) {
    unsigned overflow = 0;
    
    for(int i = (int)wildcards.size() - 1; i >= 0; --i) {
        if(wildcards[i]) {
            if(i < wildcards.size() - 1 - overflow) {
                wildcards[i] = false;
                ++overflow;
                for(int j = 1; j <= overflow; ++j) {
                    wildcards[i+j] = true;
                }

                return true;
            } else {
                ++overflow;
                wildcards[i] = false;
            }
        }
        
        
    }
    
    if(overflow) {
        return false;
    } else {
        return true;
    }
}

ulong _createNumber(ulong nonWildcards, const std::vector<bool>& wildcards, int wildcardNumber) {
    ulong result = 0;
    
    for(ulong i = 0; i < wildcards.size(); ++i) {
        if(wildcards[i]) {
            result += powul(10, i) * wildcardNumber;
        } else {
            ulong digit = nonWildcards % 10;
            nonWildcards /= 10;
            
            result += powul(10, i) * digit;
        }
    }
    
    return result;
}

void problem51() {    
    static const ulong N = 6;
    for(int wildcardsCount = 1; wildcardsCount <= N-1; ++wildcardsCount) {
        const int digits = N - wildcardsCount;
        
        const ulong start = powul(10, digits-1);
        const ulong end = powul(10, digits);
        
        for(ulong i = start; i < end; ++i) {
            vector<bool> wildcards(N, false);
            for(int j = 0; j < wildcardsCount; ++j) {
                wildcards[j] = true;
            }
            
            do {
                int primeCount = 0;
                for(int newDigit = 0; newDigit <= 9; ++newDigit) {
                    if(newDigit == 0 && wildcards[wildcards.size()-1]) {
                        continue;
                    }
                    
                    if(isPrime(_createNumber(i, wildcards, newDigit))) {
                        ++primeCount;
                    }
                }

                if(primeCount == 8) {
                    int newDigit = wildcards[wildcards.size()-1] ? 1 : 0;
                    std::cout << "Found answer: " << _createNumber(i, wildcards, newDigit);
                    return;
                }
            
            } while(_nextPerm(wildcards));
        }
    }
    
    std::cout << "No answer" << std::endl;
}

void problem52() {
    int digitsCount = 2;
    while(true) {
        ulong start = powul(10, digitsCount-1);
        ulong end = powul(10, digitsCount) / 6 + 1;
    
        for(ulong i = start; i <= end; ++i) {
            auto digits = toDigits(i);
            std::sort(digits.begin(), digits.end());
            
            for(int mult = 2; mult <= 6; ++mult) {
                ulong newNumber = i * mult;
                auto newDigits = toDigits(newNumber);
                std::sort(newDigits.begin(), newDigits.end());
                
                if(newDigits != digits) {
                    break;
                } else {
                    if(mult == 6) {
                        std::cout << "Found: " << i << std::endl;
                        return;
                    }
                }
            }
        }
        
        ++digitsCount;
    }
}

void problem53() {
    ulong total = 0;
    
    for(int n = 23; n <= 100; ++n) {
        for(int k = 1; k < n; ++k) {
            
            ulong sum = 1;
            for(int i = 1; i <= k; ++i) {
                sum *= (n - (k - i));
                sum /= i;
                if(sum > MILION) {
                    ++total;
                    break;
                }
            }
        }
    }
    
    std::cout << "Result: " << total << std::endl;
}

struct Card {
    char value;
    char color;
    
    static bool compare(const Card& l, const Card& r) {
        return l.value < r.value;
    }
};

struct Hand {
    static const int CARDS = 5;
    static const int MAX_VALUE = 12;
    
    enum Values {
        ONE_PAIR        = 1 << 0,
        TWO_PAIRS       = 1 << 1,
        THREE_OF_KIND   = 1 << 2,
        STRAIGHT        = 1 << 3,
        FLUSH           = 1 << 4,
        FULL_HOUSE      = 1 << 5,
        FOUR_OF_KIND    = 1 << 6,
        STRAIGHT_FLUSH  = 1 << 7,
        ROYAL_FLUSH     = 1 << 8
    };
    
    Card cards[CARDS];
    int value;
    
    void buildValue() {
        value = 0;
        checkRepeats();
        checkStraight();
        checkFlush();
        checkStraightFlush();
        checkRoyalFlush();
    }
    
    void checkRepeats() {
        char previousValue = cards[0].value;
        int count = 1;
        
        for(int i = 1; i < CARDS; ++i) {
            if(cards[i].value == previousValue) {
                ++count;
            } else {
                count = 1;
                previousValue = cards[i].value;
                continue;
            }
            
            if(count == 2) {
                if(value & THREE_OF_KIND) {
                    value &= !THREE_OF_KIND;
                    value |= FULL_HOUSE;
                } else if(value & ONE_PAIR) {
                    // kind of a look-ahead
                    if(i != CARDS && cards[i+1].value != previousValue) {
                        value &= !ONE_PAIR;
                        value |= TWO_PAIRS;
                    }
                } else {
                    if(i != CARDS && cards[i+1].value != previousValue) {
                        value |= ONE_PAIR;
                    }
                }
            } else if(count == 3) {
                if(value & ONE_PAIR) {
                    value &= !ONE_PAIR;
                    value |= FULL_HOUSE;
                } else {
                    value |= THREE_OF_KIND;
                }
            } else if(count == 4) {
                value |= FOUR_OF_KIND;
            }
        }
    }
    
    void checkStraight() {
        for(int i = 1; i < CARDS; ++i) {
            if(cards[i].value != (cards[i-1].value + 1)) {
                return;
            }
        }
        
        value |= STRAIGHT;
    }
    
    void checkFlush() {
        char color = cards[0].color;
        for(int i = 1; i < CARDS; ++i) {
            if(cards[i].color != color) {
                return;
            }
        }
        
        value |= FLUSH;
    }
    
    void checkStraightFlush() {
        if((value & STRAIGHT) && (value && FLUSH)) {
            value |= STRAIGHT_FLUSH;
            value |= !STRAIGHT;
            value |= !FLUSH;
        }
    }
    
    void checkRoyalFlush() {
        if(!(value & FLUSH)) {
            return;
        }
        
        if(cards[CARDS - 1].value == MAX_VALUE) {
            value &= !FLUSH;
            value |= ROYAL_FLUSH;
        }
    }
};

static Card createCard(const std::string& cardStr) {
    Card result;
    
    static std::map<char, char> valuesMap {
        {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3}, {'6', 4},
        {'7', 5}, {'8', 6}, {'9', 7}, {'T', 8}, {'J', 9},
        {'Q', 10}, {'K', 11}, {'A', 12}
    };
    result.value = valuesMap[cardStr[0]];
    result.color = cardStr[1];
    
    return result;
}

static Hand createHand(Card* cards) {
    Hand result;
    
    memcpy(result.cards, cards, Hand::CARDS * sizeof(Card));
    std::sort(result.cards, result.cards + Hand::CARDS, Card::compare);

    result.buildValue();
    
    return result;
}

void problem54() {
    std::string test = "5H 5C 6S 7S KD 2C 3S 8S 8D TD";
    test = "5D 8C 9S JS AC 2C 5C 7D 8S QH";
    test = "2D 9C AS AH AC 3D 6D 7D TD QD";
    test = "4D 6S 9H QH QC 3D 6D 7H QD QS";
    test = "2H 2D 4C 4D 4S 3C 3D 3S 9S 9D";
    std::stringstream ss(test);
    
    Hand h1;
    Hand h2;
    
    Card cards[Hand::CARDS];
    for(int i = 0; i < Hand::CARDS; ++i) {
        std::string hStr;
        ss >> hStr;
        
        cards[i] = createCard(hStr);
    }
    h1 = createHand(cards);
    
    for(int i = 0; i < Hand::CARDS; ++i) {
        std::string hStr;
        ss >> hStr;
        
        cards[i] = createCard(hStr);
    }
    h2 = createHand(cards);
    
    std::cout << "End" << std::endl;
}
