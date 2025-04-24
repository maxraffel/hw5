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
    // // cout << current << endl;
    // if (in.length() - current.length() <= floating.length()) {
    //     if (in.length() - current.length() < floating.length()) return;
    //     if (floating.length() != 0) {
    //         for (int i = 0; i < floating.length(); ++i) { // rest must be from floating
    //             char c = floating[i];
    //             string newFloating = floating;
    //             newFloating.erase(i, 1);
    //             wordleHelper(in, newFloating, dict, current + c, out);
    //         }
    //         return;
    //     }
        
    // }
    size_t currLength = current.length();
    size_t inLength = in.length();
    if (currLength == inLength) {
        if (dict.find(current) == dict.end()) {
            return;
        }
        out.insert(current);
        return;
    }

    char c = in[currLength];
    current.push_back(c);
    if (c == '-') {
        c = 'a';
        for (int i = 0; i < 26; ++i) {
            current[currLength] = c;
            wordleHelper(in, floating, dict, current, out);
            c++;
        }
    } else {
        wordleHelper(in, floating, dict, current, out);
    } //

   
}