/////////////////////////////////////////////////////////////////////////////
//
//  lychrel.cpp
//  (Seth Nuzum's version)
//
//  A program that searches for the largest (in terms of number of
//    iterations without exceeding a specified maximum) palindrome value.
//
//  The program reports a list of numbers that share the maximum number of
//    iterations, along with the size and final palindrome number
//
//  Best running time was 1m8.267s using the final set
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "LychrelData.h"

struct Record {
    Number n;
    Number palindrome;
};
using Records = std::vector<Record>;

const size_t MaxIterations = 7500;
const size_t MaxThreads = 10;

std::mutex dataMutex; 
std::mutex recordsMutex;
std::condition_variable condVar;
size_t current_index = 0;

// This is a worker function that will be executed by each thread
void worker(LychrelData& data, size_t& maxIter, Records& records) {
    while (true) {
        dataMutex.lock();
        if (current_index >= data.size()) {
            dataMutex.unlock();
            return;
        }
        Number number = data[current_index++];
        dataMutex.unlock();

        size_t iter = 0;
        Number n = number;
        
        //While loop for palindrome verification:
        while (!n.is_palindrome() && ++iter < MaxIterations) {
            Number sum(n.size());
            Number r = n.reverse();
            auto rd = n.begin();
            
            bool carry = false;
            std::transform(n.rbegin(), n.rend(), sum.rbegin(),
                [&](auto d) {
                    auto v = d + *rd++ + carry;
    
                    carry = v > 9;
                    if (carry) { v -= 10; }
    
                    return v;
                }
            );
            if (carry) { sum.push_front(1); }
            n = sum;
        }

        recordsMutex.lock();
        if (iter < maxIter || iter == MaxIterations) {
            recordsMutex.unlock();
            continue;
        }

        Record record{number, n};
        if (iter > maxIter) {
            records.clear();
            maxIter = iter;
        }
        records.push_back(record);
        // Unlocking dataMutex after accessing the shared data here: 
        recordsMutex.unlock();
    }
}

int main() {
    LychrelData data;
    std::cerr << "Processing " << data.size() << " values ...\n";

    size_t maxIter = 0;
    Records records;

    std::vector<std::thread> threads;
    for (size_t i = 0; i < MaxThreads; ++i) {
        threads.push_back(std::thread(worker, std::ref(data), std::ref(maxIter), std::ref(records)));
    }
    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "\nmax num of iterations = " << maxIter << "\n";
    for (auto& [number, palindrome] : records) {
        std::cout << "\t" << number << " : [" << palindrome.size() << "] " << palindrome << "\n";
    }
}

