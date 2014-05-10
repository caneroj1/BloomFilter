//
//  BloomFilter.h
//  bloomFilter
//
//  Created by Joseph Canero on 5/1/14.
//  Copyright (c) 2014 Bloomin' Bloomers. All rights reserved.
//

#ifndef __bloomFilter__BloomFilter__
#define __bloomFilter__BloomFilter__

#include <functional>
#include <cmath>
#include <cstdlib>
#include <sstream>

template <class T>
class BloomFilter {

public:
    //  constructor for BloomFilter, accepts item and and bit count
    BloomFilter(int bitCount, int itemCount) {
        m = bitCount;
        n = itemCount;
        k = calculateHashNumbers();
        bitv = new bool[m];
    }
    
    //  other constructor, accepts number of items and desired (approximate) false positive rate
    BloomFilter(int itemCount, double fpRate) {
        n = itemCount;
        m = calculateBitCount(fpRate);
        k = calculateHashNumbers();
        bitv = new bool[m];
    }
    
    //  destructor
    ~BloomFilter() {
        delete [] bitv;
    }
    
    //  toString, descriptive string formatted appropriately that will output the bitset as well as number of items inserted
    std::string toString() {
        //  string to display number of items
        std::ostringstream items;
        items << "Items Inserted: " << itemsInserted << "\n";
        
        //  string to display false positive rate
        std::ostringstream fp;
        fp << "False Positive Rate: " << calculateFalsePositive() << "\n";
        
        //  string to display number of hash functions being used
        std::ostringstream hf;
        hf << "Hash functions: " << k << "\n";
        
        //  string to display number of bits used
        std::ostringstream bu;
        bu << "Bits used: " << m << "\n";
        
        //  string to display the bit vector
        std::ostringstream bits;
        bits << "Bit Vector";
        for (int i = 0; i < m; i++) {
            if (i % 10 == 0) bits << "\n";
            if (bitv[i]) bits << "1 ";
            else bits << "0 ";
        }
        
        //  convert the string streams to strings
        std::string istr = items.str();
        std::string mstr = bu.str();
        std::string rstr = fp.str();
        std::string hstr = hf.str();
        std::string bstr = bits.str();
        
        //  concatenate and return
        return istr + mstr + rstr + hstr + bstr;
    }
    
    //  calculate probability of false positives
    double calculateFalsePositive() {
        return pow((1 - pow(e, ((float)(-k*n)/m))), k);
    }
    
    //  calculate the number of bits that will be needed
    int calculateBitCount(double fpRate) {

        return (int)round(-2 * n * log(fpRate));
    }
    
    //  add an item of type T to the filter
    void add(T item) {
        //  get the array of values based off of initial hash
        size_t *ind = new size_t[k];
        calculateHash(item, ind);
        
        //  iterate through array, mod size of bit vector, mark positions as true
        for (int i = 0; i < k; i++) {
            bitv[ind[i]%m] = 1;
        }
        
        //  increment the insertion count
        itemsInserted++;
        
        //  deallocate our dynamic memory
        delete [] ind;
    }
    
    bool check(T item) {
        //  get the array of values based off of initial hash
        size_t *ind = new size_t[k];
        calculateHash(item, ind);
        
        //  boolean value to use for the result
        bool result = true;
        
        //  iterate through array, check if the bits at the positions indicated are set
        //  form the boolean return value
        for (int i = 0; i < k; i++) {
            if (bitv[ind[i]%m] == 1) {
                result &= true;
            }
            else result &= false;
        }
        
        //  return the results of the check
        return result;
    }
    
private:
    int m;                                      //  size of bit vector
    int n;                                      //  estimate of elements to be added
    int k;                                      //  number of hash functions
    int itemsInserted;                          //  number of items inserted
    
    bool *bitv;                                 //  bit vector
    const double e = 2.71828;
    
    //  calculate the number of hash functions to use
    int calculateHashNumbers() {
        int k = (int)round(0.7 * (m/n));
        if (k == 0) k = 1;
        return k;
    }
    
    //  calculate the hash values of the item
    void  calculateHash(T item, size_t hash_array[]) {
        //  generate the first hash
        std::hash<T> h;
        size_t val = h(item);

        //  seed RNG with hash value, put first hash in array
        srand(val);
        hash_array[0] = val;
        
        //  create k-1 random values based off of the hash
        for (int i = 1; i < k; i++) {
            hash_array[i] = rand();
        }
    }
};
#endif /* defined(__bloomFilter__BloomFilter__) */
