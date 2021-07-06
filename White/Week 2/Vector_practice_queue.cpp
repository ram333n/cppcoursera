#include <iostream>
#include <vector>
#include <string>
using namespace std;

void queue(){ 
	int q;
	string command;
	vector<bool>queue(false);
	cin >> q;
	for (int t = 0; t < q; t++) {
		cin >> command;
		if (command == "WORRY_COUNT") {
			int quantityOfWorry(0);
			for (const bool& m : queue) if (m) quantityOfWorry++;
			cout << quantityOfWorry;
		}
		if (command == "WORRY") {
			int idxOfWorry;
			cin >> idxOfWorry;
			queue[idxOfWorry] = true;
		}
		if (command == "QUIET") {
			int idxOfQuiet;
			cin >> idxOfQuiet;
			queue[idxOfQuiet] = false;
		}
		if (command == "COME") {
			int quantity;
			cin >> quantity;
			if (quantity > 0) queue.resize(queue.size() + quantity, 0);
			else queue.resize(queue.size() + quantity);
		}
	}	
}