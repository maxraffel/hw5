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
    const std::string floating,
    const std::set<std::string>& dict,
    std::string current,
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

    wordleHelper(in, floating, dict, current, out);
    return out;
}

// Define any helper functions here

void wordleHelper(
    const std::string& in,
    const std::string floating,
    const std::set<std::string>& dict,
    std::string current,
    std::set<std::string>& out)
{
    if (in.length() - current.length() < floating.length()) {
        return;
    }
    if (current.length() == in.length()) {
        if ( floating.length() != 0 || dict.find(current) == dict.end()) {
            return;
        }
        // we will never make a choice that does not match the in string, so don't need to check
        out.insert(current);
        return;
    }

    current.push_back(in[current.length()]);
    if (in[current.length()] == '-') {
        for (int i = 0; i < 26; ++i) {
            char c = 'a' + i;
            current[current.length() - 1] = c;
            int index = floating.find(c);
            if (index != std::string::npos) {
                string newFloating = floating;
                newFloating.erase(index, 1);
                wordleHelper(in, newFloating, dict, current, out);
            }
            else {
                wordleHelper(in, floating, dict, current, out);
            }
        }
    } else {
        wordleHelper(in, floating, dict, current, out);
    }

   
}