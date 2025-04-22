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
    // cout << current << endl;
    if (in.length() - current.length() < floating.length()) {
        return;
    }
    if (current.length() == in.length()) {
        if (dict.find(current) == dict.end()) {
            return;
        }
        // we will never make a choice that does not match the in string, so don't need to check
        out.insert(current);
        return;
    }

    size_t endIndex = current.length();
    if (in[current.length()] == '-') {
        for (int i = 0; i < floating.length(); ++i) { // try floating letters first
            char c = floating.back();
            string newFloating = floating;
            newFloating.pop_back();
            wordleHelper(in, newFloating, dict, current + c, out);
        }
        for (int i = 0; i < 26; ++i) {
            char c = 'a' + i;
            size_t index = floating.find(c);
            if (index != std::string::npos) {
                string newFloating = floating;
                newFloating.erase(index, 1);
                wordleHelper(in, newFloating, dict, current + c, out);
            }
            else {
                wordleHelper(in, floating, dict, current + c, out);
            }
        }
    } else {
        wordleHelper(in, floating, dict, current + in[current.length()], out);
    } //

   
}