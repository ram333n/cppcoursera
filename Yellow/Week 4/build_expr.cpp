#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <deque>

using namespace std;

struct Operation {
	char oper = '0';
	int number = 0;
};

int GetOperationPriority(const char& c) {
	switch (c) {
		case '*':
		case '/':
			return 2;
		case '+':
		case '-':
			return 1;

	}
	return 0;
}
//а нафіг тут std::stack?

string GetExpression(const vector<Operation>& v,const int& first_number) {
	string result = to_string(first_number);
	deque<char> current_expression(begin(result), end(result));
	char prev_operation = v[0].oper;
	for (const Operation& op : v) {
		if (GetOperationPriority(prev_operation) < GetOperationPriority(op.oper)) {
			current_expression.push_back(')');
			current_expression.push_front('(');
		}
		string number_str = to_string(op.number);
		deque<char> temp(begin(number_str),end(number_str));
		temp.push_front(' ');
		temp.push_front(op.oper);
		temp.push_front(' ');
		copy(begin(temp), end(temp), back_inserter(current_expression));
		prev_operation = op.oper;
	}
	return string(begin(current_expression), end(current_expression));
}



int main(){
	int first_number(0),n;
	cin >> first_number >> n;
	vector<Operation> operations(n);
	for (Operation& o : operations) {
		cin >> o.oper >> o.number;
	}
	cout << GetExpression(operations, first_number) << endl;
}