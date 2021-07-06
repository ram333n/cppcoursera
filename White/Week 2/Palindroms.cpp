#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool IsPalindrom(string s) {
    for (int i = 0; i < (s.length()/2); i++) {
        if (s[i] != s[s.length() - i - 1]) return false;
    }
    return true;
}

vector<string> PalindromFilter(vector<string>words, int minLength) {
    vector<string>result;
    for (auto s : words) if (IsPalindrom(s) && s.size() >= minLength) result.push_back(s);
    return result;
}

int main()
{
    
}
