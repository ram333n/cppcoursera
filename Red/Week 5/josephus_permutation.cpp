#include "test_runner.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <iostream>
#include <list>

using namespace std;

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
    list<typename RandomIt::value_type> pool;

    for (size_t i = 0; i < distance(first, last); ++i) {
        pool.push_back(move(*(first + i)));
    }

    size_t cur_pos = 0;
    auto it = pool.begin();
    auto next_elem = it;
    bool is_first_taken = true;

    *(first++) = move(*it);
    pool.erase(it);
    it = pool.begin();

    while (!pool.empty()) {
       // size_t dist = pool.size() - cur_pos;

        for (size_t i = 0; i < step_size - 1; ++i) {
            if (next(it) != pool.end()) {
                it++;
            }
            else {
                it = pool.begin();
            }
        }

        is_first_taken = false;

        next_elem = next(it) != pool.end() ? next(it) : pool.begin();

        *(first++) = move(*it);
        pool.erase(it);
        if (pool.empty()) {
            break;
        }
        it = next_elem;
        //cur_pos = (cur_pos + step_size - 1) % pool.size();
    }
}

template <typename RandomIt>
void MakeJosephusPermutationSuka(RandomIt first, RandomIt last, uint32_t step_size) {
    vector<typename RandomIt::value_type> pool(first, last);
    size_t cur_pos = 0;
    while (!pool.empty()) {
        *(first++) = pool[cur_pos];
        pool.erase(pool.begin() + cur_pos);
        if (pool.empty()) {
            break;
        }
        cur_pos = (cur_pos + step_size - 1) % pool.size();
    }
}

vector<int> MakeTestVector() {
    vector<int> numbers(10);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

void TestIntVector() {
    const vector<int> numbers = MakeTestVector();
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        ASSERT_EQUAL(numbers_copy, numbers);
    }
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
        ASSERT_EQUAL(numbers_copy, vector<int>({ 0, 3, 6, 9, 4, 8, 5, 2, 7, 1 }));
    }
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»

struct NoncopyableInt {
    int value;

    NoncopyableInt(int value) : value(value) {}

    NoncopyableInt(const NoncopyableInt&) = delete;
    NoncopyableInt& operator=(const NoncopyableInt&) = delete;

    NoncopyableInt(NoncopyableInt&&) = default;
    NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
    return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
    return os << v.value;
}

void TestAvoidsCopying() {
    vector<NoncopyableInt> numbers;
    numbers.push_back({ 1 });
    numbers.push_back({ 2 });
    numbers.push_back({ 3 });
    numbers.push_back({ 4 });
    numbers.push_back({ 5 });

    MakeJosephusPermutation(begin(numbers), end(numbers), 2);

    vector<NoncopyableInt> expected;
    expected.push_back({ 1 });
    expected.push_back({ 3 });
    expected.push_back({ 5 });
    expected.push_back({ 4 });
    expected.push_back({ 2 });

    ASSERT_EQUAL(numbers, expected);
}

void Pizdetc() {
    vector<int>a(100000), b(100000);
    iota(begin(a), end(a), 0);
    iota(begin(b), end(b), 0);
    MakeJosephusPermutation(begin(a), end(a), 100);
    MakeJosephusPermutationSuka(begin(b), end(b), 100);

    ASSERT_EQUAL(a, b);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    RUN_TEST(tr, Pizdetc);
    return 0;
}
