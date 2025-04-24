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
    const std::string& floating,
    const std::set<std::string>& dict,
    std::string& current,
    std::set<std::string>& out)
{

    size_t currLength = current.length();
    size_t inLength = in.length();
    if (currLength == inLength) {
        string tempFloating = floating;
        for (int i = 0; i < current.length(); ++i) {
            size_t index = floating.find(current[i]);
            if (index != string::npos) {
                tempFloating.erase(index, 1);
            }
        }
        if (tempFloating.length() != 0 || dict.find(current) == dict.end()) {
            return;
        }
        out.insert(current);
        return;
    }

    char c = in[currLength];
    if (c == '-') {
        c = 'a';
        for (int i = 0; i < 26; ++i) {
            current.push_back(c);
            wordleHelper(in, floating, dict, current, out);
            current.pop_back();
        }
    } else {
        current.push_back(c);
        wordleHelper(in, floating, dict, current, out);
        current.pop_back();
    } //

   
}