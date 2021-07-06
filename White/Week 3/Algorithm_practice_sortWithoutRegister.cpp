#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
void printVector(const vector<string>& v) {
    for (const auto& e : v) cout << e << " ";
}
int main()
{
    int n;
    cin >> n;
    vector<string> arr(n);
    for (auto& s : arr) cin >> s;
    sort(begin(arr), end(arr), [](string a, string b) {
        bool result;
        for (int i = 0; i < (min(a.size(), b.size())); i++) {
            if (tolower(a[i]) == tolower(b[i])) continue;
            return tolower(a[i]) < tolower(b[i]);
        }
        return(a.size() < b.size());
        });
    printVector(arr);
}
