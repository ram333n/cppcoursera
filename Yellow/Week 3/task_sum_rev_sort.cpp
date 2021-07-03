#include <algorithm>
#include <iostream>
#include "sum_reverse_sort.h"

int Sum(int x, int y) {
    return x + y;
}

string Reverse(string s) {
    reverse(begin(s), end(s));
    return s;
}

void Sort(vector<int>& nums) {
    sort(begin(nums), end(nums));
}
/*int main()
{}
    */