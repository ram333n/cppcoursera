#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template<typename T>
class Deque {
public:
	Deque() = default;

	bool Empty() const {
		return front_part.empty() && back_part.empty();
	}

	size_t Size() const {
		return front_part.size() + back_part.size();
	}

	T& operator[](size_t index) {
		if (index < front_part.size()) {
			return front_part[front_part.size() - index - 1];
		}
		else {
			return back_part[index - front_part.size()];
		}
	}
	
	const T& operator[](size_t index) const {
		if (index < front_part.size()) {
			return front_part[front_part.size() - index - 1];
		}
		else {
			return back_part[index - front_part.size()];
		}
	}

	T& At(size_t index) {
		if (index >= Size()) {
			throw out_of_range("Out of range");
		}

		return this->operator[](index);
	}

	const T& At(size_t index) const {
		if (index >= Size()) {
			throw out_of_range("Out of range");
		}

		return this->operator[](index);
	}

	T& Front() {
		return this->operator[](0);
	}

	const T& Front() const  {
		return this->operator[](0);
	}

	T& Back() {
		return this->operator[](Size() - 1);
	}

	const T& Back() const {
		return this->operator[](Size() - 1);
	}

	void PushFront(const T& to_push) {
		front_part.push_back(to_push);
	}

	void PushBack(const T& to_push) {
		back_part.push_back(to_push);
	}

private:
	vector<T> front_part, back_part;
};

//int main() {
//	Deque<int> d;
//
//	for (int i = 0; i < 10; ++i) {
//		d.PushFront(i);
//		cout << "Deque : ";
//		for (size_t j = 0; j < d.Size(); ++j) {
//			cout << d[j] << " ";
//		}
//		cout << endl;
//	}
//
//	cout << "Front : " << d.Front() << ", Back : " << d.Back() << endl;
//
//}

