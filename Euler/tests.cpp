//
//  tests.cpp
//  Euler
//
//  Created by Artur Mazurek on 05/08/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "tests.h"

#include <iostream>
#include <string>

#include "BigNumber.h"

using namespace std;

#define CHECK_TRUE(x) _check((x), #x)
#define CHECK_FALSE(x) _check(!(x), #x)

static void testBigNumber();
static void testBigNumberAdd();
static void checkBigNumberComparison();
static bool _check(bool, const string&);

void runTests() {
    testBigNumber();
    cout << "Tests finished" << endl;
}

static bool _check(bool result, const string& text) {
    if(!result) {
        cout << "FAILED: " << text << endl;
    }
    
    return result;
}

static void testBigNumber() {
    testBigNumberAdd();
    checkBigNumberComparison();
}

static void testBigNumberAdd() {
    CHECK_TRUE(BigNumber{1} + BigNumber{1} == BigNumber{2});
    CHECK_TRUE(BigNumber{2} + BigNumber{2} == BigNumber{4});
    CHECK_TRUE(BigNumber{9} + BigNumber{9} == BigNumber{18});
    CHECK_TRUE(BigNumber{181} + BigNumber{256} == BigNumber{437});
    
    CHECK_TRUE(BigNumber{1} + BigNumber{1} != BigNumber{3});
    CHECK_TRUE(BigNumber{2} + BigNumber{2} != BigNumber{5});
    CHECK_TRUE(BigNumber{9} + BigNumber{9} != BigNumber{19});
    CHECK_TRUE(BigNumber{181} + BigNumber{256} != BigNumber{438});
    
    CHECK_TRUE(BigNumber{1} + BigNumber{2} == BigNumber{2} + BigNumber{1});
    CHECK_TRUE(BigNumber{2} + BigNumber{0} == BigNumber{0} + BigNumber{2});
    CHECK_TRUE(BigNumber{9} + BigNumber{9} == BigNumber{10} + BigNumber{8});
    CHECK_TRUE(BigNumber{181} + BigNumber{256} == BigNumber{100} + BigNumber{337});
}

static void checkBigNumberComparison() {
    CHECK_TRUE(BigNumber{0} < BigNumber{2});
    CHECK_TRUE(BigNumber{123} < BigNumber{432});
    CHECK_TRUE(BigNumber{123} < BigNumber{124});
    
    CHECK_TRUE(BigNumber{0} <= BigNumber{0});
    CHECK_TRUE(BigNumber{987978} <= BigNumber{412321312});
    CHECK_TRUE(BigNumber{321} <= BigNumber{321});
    
    CHECK_TRUE(BigNumber{3} > BigNumber{2});
    CHECK_TRUE(BigNumber{3212} > BigNumber{444});
    CHECK_TRUE(BigNumber{1} > BigNumber{0});
    
    CHECK_TRUE(BigNumber{123} >= BigNumber{123});
    CHECK_TRUE(BigNumber{0} >= BigNumber{0});
    CHECK_TRUE(BigNumber{4214} >= BigNumber{2});
}