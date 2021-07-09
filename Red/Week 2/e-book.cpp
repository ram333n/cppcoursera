#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>


using namespace std;

class ReadingManager {
public:
    ReadingManager()
        :page_to_number_of_users(MAX_PAGE_COUNT + 1, 0),
        users_page_storage (MAX_USER_COUNT + 1, 0) {}

    //vector<int> page_to_number_of_users;

    void Read(const int& user_id, const int& page_count) {
        if (users_page_storage[user_id]) {
            page_to_number_of_users[users_page_storage[user_id]]--;
        }
        else {
            users_id_number++;
        }

        users_page_storage[user_id] = page_count;
        page_to_number_of_users[users_page_storage[user_id]]++;
    }

    double Cheer(const int& user_id) const {
        if (users_page_storage[user_id] == 0) {
            return 0;
        }
        const int user_count = GetUserCount();
        if (user_count == 1) {
            return 1;
        }

        int people_with_less_number_of_pages = 0;
        for (int current_page = 0; current_page < users_page_storage[user_id]; ++current_page) {
            people_with_less_number_of_pages += page_to_number_of_users[current_page];
        }

        return (people_with_less_number_of_pages * 1.0) / (user_count - 1);
    }

private:
    static const int MAX_USER_COUNT = 100'000;
    static const int MAX_PAGE_COUNT = 1000;

    vector<int> page_to_number_of_users;
    vector<int> users_page_storage;

    size_t users_id_number = 0;

    int GetUserCount() const {
        return users_id_number;
    }

    void UpdateRating() {
       
    }
   
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}