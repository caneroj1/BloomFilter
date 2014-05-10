//
//  main.cpp
//  bloomFilter
//
//  Created by Joseph Canero on 5/1/14.
//  Copyright (c) 2014 Bloomin' Bloomers. All rights reserved.
//

#include <iostream>
#include <string>
#include "BloomFilter.h"

using namespace std;

int main(int argc, const char * argv[])
{
    //  instantiate our filter
    //  this filter holds strings
    BloomFilter<string> bf(100, 30);
    cout << "False positive: " << bf.calculateFalsePositive() << endl;
    
    //  add some items to the filter
    string input[10];
    int count = -1;
    do {
        count++;
        cout << "What do you want to add? ";
        getline(cin, input[count]);
        if (cin.fail()) {
            cin.clear(100);
            cout << "Invalid!" << endl;
        }
        else if (input[count] != "n" && input[count] != "N") {
            bf.add(input[count]);
            cout << "Added \"" << input[count] << "\"" << endl;
        }
    } while (input[count] != "n" && input[count] != "N" && count < 10);
    
    //  these should all be Yes
    //  bloom filters do not give false negatives
    for (int i = 0; i < count; i++) {
        cout << "Checking if \"" << input[i] << "\" is in the Bloom Filter!" << endl;
        if (bf.check(input[i])) {
            cout << "Yes!" << endl;
        }
        else {
            cout << "Isn't there!" << endl;
        }
    }
    
    //  toString function
    cout << bf.toString() << endl;
    
    //  allow user to enter words to be checked against the first bloom filter
    string inp;
    do {
        cout << "What string do you want to check? ";
        getline(cin, inp);
        if (cin.fail()) {
            cin.clear(100);
            cout << "Invalid!" << endl;
        }
        else if (inp != "n" && inp != "N") {
            if (bf.check(inp)) {
                cout << "Yes!" << endl;
            }
            else {
                cout << "Isn't there!" << endl;
            }
        }
    } while (inp != "n" && inp != "N");

    //  use the other constructor
    BloomFilter<int> otherFilter(20, 0.15);
    
    //  toString, once again
    cout << otherFilter.toString() << endl;
    
    return 0;
}

