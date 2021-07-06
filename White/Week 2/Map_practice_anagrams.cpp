#include <iostream>
#include <map>
#include <string>

using namespace std;

map<char, int> BuildCharCounters(const string& s) {
    map<char, int> result;
    for (const auto& c : s) {
        result[c]++;
    }
    return result;
}

void psevdo_main()
{
    int n;
    cin >> n;
    string s1, s2;
    for (int i = 0; i < n; i++) {
        cin >> s1 >> s2;
        if (BuildCharCounters(s1) == BuildCharCounters(s2)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}

