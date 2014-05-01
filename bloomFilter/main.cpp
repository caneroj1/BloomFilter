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
    cout << bf.calculateFalsePositive() << endl;
    
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
            cout << "Wasn't there!" << endl;
        }
    }
    
    cout << "Creating a Bloom Filter for ints" << endl;
    //  instantiate a filter that holds ints
    BloomFilter<int> bf2(30, 10);
    
    //  add some ints to the filter
    count = -1;
    int input2[10];
    do {
        count++;
        cout << "What do you want to add? ";
        cin >> input2[count];
        cout << input2[count];
        if (cin.fail()) {
            cin.clear(100);
            cout << "Invalid!" << endl;
        }
        else {
            bf2.add(input2[count]);
            cout << "Added \"" << input2[count] << "\"" << endl;
        }
    } while (count < 10);
    
    //  these should all be Yes
    //  bloom filters do not give false negatives
    for (int i = 0; i < count; i++) {
        cout << "Checking if \"" << input2[i] << "\" is in the Bloom Filter!" << endl;
        if (bf2.check(input2[i])) {
            cout << "Yes!" << endl;
        }
        else {
            cout << "Wasn't there!" << endl;
        }
    }
    
    return 0;
}

