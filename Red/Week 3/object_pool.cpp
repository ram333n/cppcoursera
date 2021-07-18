#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
	T* Allocate() {
		T* result;

		if (!free_objects.empty()) {
			result = free_objects.front();
			free_objects.pop();
		}
		else {
			result = new T;
		}

		selected_objects.insert(result);
		return result;

	}

	T* TryAllocate() {
		T* result = nullptr;

		if (!free_objects.empty()) {
			result = free_objects.front();
			free_objects.pop();
			selected_objects.insert(result);
		}

		return result;
	}

	void Deallocate(T* object) {
		auto result_it = selected_objects.find(object);

		if (result_it == selected_objects.end()) {
			throw invalid_argument("This object doesn't exist");
		}
		
		free_objects.push(*result_it);
		selected_objects.erase(result_it);
	}

	~ObjectPool() {
		while (!free_objects.empty()) {
			delete free_objects.front();
			free_objects.pop();
		}

		for (auto& obj : selected_objects) {
			delete obj;
		}
	}

private:
	queue<T*> free_objects;
	set<T*> selected_objects;
};

void TestObjectPool() {
	ObjectPool<string> pool;

	auto p1 = pool.Allocate();
	auto p2 = pool.Allocate();
	auto p3 = pool.Allocate();

	*p1 = "first";
	*p2 = "second";
	*p3 = "third";

	pool.Deallocate(p2);
	ASSERT_EQUAL(*pool.Allocate(), "second");

	pool.Deallocate(p3);
	pool.Deallocate(p1);
	ASSERT_EQUAL(*pool.Allocate(), "third");
	ASSERT_EQUAL(*pool.Allocate(), "first");

	pool.Deallocate(p1);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestObjectPool);
	return 0;
}
