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
    std::string& floating,
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
    string tempFloating = floating;

    wordleHelper(in, tempFloating, dict, current, out);
    return out;
}

// Define any helper functions here

void wordleHelper(
    const std::string& in,
    std::string& floating,
    const std::set<std::string>& dict,
    std::string& current,
    std::set<std::string>& out)
{

    size_t currLength = current.length();
    size_t inLength = in.length();
    size_t floatLength = floating.length();

    if (floatLength > inLength - currLength) {
        return;
    }

    if (currLength == inLength) {
        if (floatLength != 0 || dict.find(current) == dict.end()) {
            return;
        }
        out.insert(current);
        return;
    }

    char c = in[currLength];
    if (c == '-') {
        for (int i = 0; i < 26; ++i) {
            c = 'a' + i;
            size_t index = floating.find(c);
            if (index != std::string::npos) {
                floating.erase(index, 1);
            }
            current.push_back(c);
            wordleHelper(in, floating, dict, current, out);
            current.pop_back();
            floating.push_back(c);
        }
    } else {
        current.push_back(c);
        wordleHelper(in, floating, dict, current, out);
        current.pop_back();
    } //

   
}