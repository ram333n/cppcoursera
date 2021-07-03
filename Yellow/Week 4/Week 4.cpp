#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
/*vector<string> SplitIntoWords(const string& str) {
  // ������� ������, � ������� ����� ��������� �����
  vector<string> result;

  // ��� ��� ��������� ����� ������������ ������� �� �������� ����� ������
  // str_begin ����� ��������� ������
  auto str_begin = begin(str);
  // str_end ������ ����� ��������� �� ����� ������ (������� �� �����������)
  const auto str_end = end(str);

  // � ����� ��� ������� ����������, ��� ��� ������������ ������ ��������� ��� �
  // ������� break
  while (true) {
    
    // ������� ������ ������ � ������� ������� ������
    auto it = find(str_begin, str_end, ' ');
    
    // ������������ [str_begin, it) � ��������� �����
    result.push_back(string(str_begin, it));
    
    if (it == str_end) {
      // ���� �������� ������ ���, ���� ���� ���������.
      // ��������� ����� ��� ���������
      break;
    } else {
      // ����� ������ ������ ����� ������� � ������ ���������� �����.
      // ���� � �������� str_begin
      str_begin = it + 1;
    }
    
  }

  return result;
}*/

vector<string> SplitIntoWords(const string& s) {
    vector<string> result;
    for (auto first_it = begin(s); first_it < end(s);) {
        auto second_it = find(first_it+1, end(s), ' ');
        result.push_back(string(first_it, second_it));
        first_it = second_it;
        if (first_it != end(s)) first_it++;
    }
    return result;
}

/*int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}*/


