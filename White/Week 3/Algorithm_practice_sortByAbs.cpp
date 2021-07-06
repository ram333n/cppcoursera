#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
void printVector(const vector<int>& v) {
    for (const auto& e : v) cout << e << " ";
}
void pp_main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (auto& n : arr) cin >> n;
    sort(begin(arr), end(arr), [](int a, int b) {return (abs(a) < abs(b)); });
    printVector(arr);
}
