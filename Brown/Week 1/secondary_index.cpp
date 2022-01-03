#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};


struct RecordHasher {
    size_t operator()(const Record& record) const {
        int x = 2749;
        return string_hasher(record.id)    * x * x * x * x
            + string_hasher(record.title)  * x * x * x
            + string_hasher(record.user)   * x * x
            + int_hasher(record.timestamp) * x
            + int_hasher(record.karma);
    }

    hash<string> string_hasher;
    hash<int> int_hasher;
};

class Database {
public:
    bool Put(const Record& record) {
        auto it = record_storage.find(record.id);
        if (it != record_storage.end()) {
            return false;
        }

        Positions pos;

        record_storage[record.id] = { record,{} };
        Record* record_ptr = &record_storage[record.id].first;

        pos.user_to_record_position = user_to_record.insert(pair<string, Record*>(record.user, record_ptr));
        pos.timestamp_to_record_position = timestamp_to_record.insert(pair<int, Record*>(record.timestamp, record_ptr));
        pos.karma_to_record_position = karma_to_record.insert(pair<int, Record*>(record.karma, record_ptr));

        record_storage[record.id].second = pos;

        return true;
    }

    const Record* GetById(const string& id) const {
        auto it = record_storage.find(id);
        return it != record_storage.end() ? &it->second.first : nullptr;
    }

    bool Erase(const string& id) {
        auto it = record_storage.find(id);
        if (it == record_storage.end()) {
            return false;
        }

        RemoveByPositions(it->second.second);
        record_storage.erase(it);
        return true;
    }

    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const {
        RangeBy(timestamp_to_record, low, high, callback);
    }

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const {
        RangeBy(karma_to_record, low, high, callback);
    }

    template <typename Callback>
    void AllByUser(const string& user, Callback callback) const {
        auto range = user_to_record.equal_range(user);
        while (range.first != range.second && callback(*range.first->second)) {
            range.first++;
        }
    }
private:
    struct Positions {
        multimap<string, Record*>::iterator user_to_record_position;
        multimap<int, Record*>::iterator timestamp_to_record_position;
        multimap<int, Record*>::iterator karma_to_record_position;
    };

    unordered_map<string, pair<Record, Positions>> record_storage;
    multimap<string, Record*> user_to_record;
    multimap<int, Record*> timestamp_to_record, karma_to_record;

    template <typename Callback>
    void RangeBy(const multimap<int, Record*>& source, int low, int high, Callback callback) const {
        auto lower_border = source.lower_bound(low);
        auto upper_border = source.upper_bound(high);

        while (lower_border != upper_border && callback(*lower_border->second)) {
            lower_border++;
        }
    }

    void RemoveByPositions(const Positions& pos) {
        if (pos.user_to_record_position != user_to_record.end()) {
            user_to_record.erase(pos.user_to_record_position);
        }

        if (pos.timestamp_to_record_position != timestamp_to_record.end()) {
            timestamp_to_record.erase(pos.timestamp_to_record_position);
        }

        if (pos.karma_to_record_position != karma_to_record.end()) {
            karma_to_record.erase(pos.karma_to_record_position);
        }
    }
};

void TestRangeBoundaries() {
    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({ "id1", "Hello there", "master", 1536107260, good_karma });
    db.Put({ "id2", "O>>-<", "general2", 1536107260, bad_karma });

    int count = 0;
    db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
        ++count;
        return true;
        });

    ASSERT_EQUAL(2, count);
}

void TestSameUser() {
    Database db;
    db.Put({ "id1", "Don't sell", "master", 1536107260, 1000 });
    db.Put({ "id2", "Rethink life", "master", 1536107260, 2000 });

    int count = 0;
    db.AllByUser("master", [&count](const Record&) {
        ++count;
        return true;
        });

    ASSERT_EQUAL(2, count);
}

void TestReplacement() {
    const string final_body = "Feeling sad";

    Database db;
    db.Put({ "id", "Have a hand", "not-master", 1536107260, 10 });
    db.Erase("id");
    db.Put({ "id", final_body, "not-master", 1536107260, -10 });

    auto record = db.GetById("id");
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

//int main() {
//    TestRunner tr;
//    RUN_TEST(tr, TestRangeBoundaries);
//    RUN_TEST(tr, TestSameUser);
//    RUN_TEST(tr, TestReplacement);
//    return 0;
//}
