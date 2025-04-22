#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    std::string& current,
    const int maxLength,
    std::set<std::string>& out);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<std::string> out;
    string current = "";

    wordleHelper(in, floating, dict, current, in.length(), out);
    return out;
}

// Define any helper functions here

void wordleHelper(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    std::string& current,
    const int maxLength,
    std::set<std::string>& out)
{
    if (current.length() == maxLength) {
        int wordsFound = 0;
        for (int i = 0; i < floating.length(); ++i) {
            if (current.find(i) == std::string::npos) {
                return;
            } else {
                ++wordsFound;
            }
        }
        if (wordsFound < floating.length() || dict.find(current) == dict.end()) {
            return;
        }
        
        // we will never make a choice that does not match the in string, so don't need to check
        out.insert(current);
    }

    current += '-';
    for (int i = 0; i < 26; ++i) {
        char c = 'a' + i;
        int lastIndex = current.length() - 1;
        if (in[current.length()] == '-' || in[current.length()] == c) { // only make valid choices, but ignores the floating chars
            current[lastIndex] = c;
            wordleHelper(in, floating, dict, current, maxLength, out);
        }
    }
}