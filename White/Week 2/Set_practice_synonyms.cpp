#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;
int main() {
	int q;
	map<string,set<string>> vocabulary;
	cin >> q;
	for (int t = 0; t < q; t++) {
		string command;
		cin >> command;
		if (command == "ADD") {
			string word1, word2;
			cin >> word1 >> word2;
			(vocabulary[word1]).insert(word2);
			(vocabulary[word2]).insert(word1);
		}
		if (command == "COUNT") {
			string word;
			cin >> word;
			cout << vocabulary[word].size() << endl;
		}
		if (command == "CHECK") {
			string word1, word2;
			cin >> word1 >> word2;
			if (vocabulary[word1].count(word2) != 0 || vocabulary[word2].count(word1) != 0) cout << "YES" << endl;
			else cout << "NO" << endl;
		}
	}
}