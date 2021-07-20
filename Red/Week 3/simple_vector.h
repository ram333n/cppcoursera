#pragma once

#include <cstdlib>
#include <iostream>

template <typename T>
class SimpleVector {
public:
	SimpleVector() {
		data = nullptr;
	}

	explicit SimpleVector(size_t size) {
		data = new T[size];
		size_ = size;
		capacity_ = size;
	}

	~SimpleVector() {
		delete[] data;
	}

	T& operator[](size_t index) {
		return data[index];
	}

	T* begin() { 
		return data;
	}

	T* end() {
		return data + Size();
	}

	size_t Size() const {
		return size_;
	}

	size_t Capacity() const {
		return capacity_;
	}

	void PushBack(const T& value) {
		if (!data) {
			data = new T[1];
			capacity_ = 1;
		}
		else {
			if (size_ == capacity_) {
				T* tmp = data;
				T* new_data = new T[2 * capacity_];

				std::copy(begin(), end(), new_data);
				data = new_data;
				capacity_ *= 2;
				delete[] tmp;
			}
		}

		data[size_] = value;
		++size_;
	}

private:
	T* data;
	size_t size_ = 0;
	size_t capacity_ = 0;
};