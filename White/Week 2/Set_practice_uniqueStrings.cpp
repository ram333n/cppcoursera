#include <iostream>
#include <string>
#include <set>

using namespace std;

void main1()
{
    string words;
    int q;
    set<string>unique;
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> words;
        unique.insert(words);
    }
    cout << unique.size() << endl;
}

