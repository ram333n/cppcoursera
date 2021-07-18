#include <iostream>
#include <queue>
#include <map>

using namespace std;


class BookingManager {
public:
	/*
	map<string, map<uint32_t, int>> hotels_to_users_orders;
	map<string, int> hotels_to_rooms;
	*/


	void book(const int64_t& time, const string& hotel_name, const uint32_t& client_id,	const int& room_count) 	{

		Update(time);

		booking_stream.push({ client_id,time,hotel_name, room_count });
		
		hotels_to_rooms[hotel_name] += room_count;
		hotels_to_users_orders[hotel_name][client_id] += room_count;

	}

	size_t clients(const string& hotel_name) {
		size_t result = 0u;
		auto required_hotel = hotels_to_users_orders.find(hotel_name);

		if (required_hotel != hotels_to_users_orders.end()) {
			result = required_hotel->second.size();
		}

		return result;
	}

	int rooms(const string& hotel_name) {
		int result = 0;
		auto required_hotel = hotels_to_rooms.find(hotel_name);

		if (required_hotel != hotels_to_rooms.end()) {
			result = required_hotel->second;
		}

		return result;
	}
private:
	void Update(const int64_t& current_time) {
		if (!booking_stream.empty()) {

			auto predicate = [current_time](const Order& ord) {
				return !(current_time - 86400 < ord.time && current_time >= ord.time);
			};

			while (!booking_stream.empty() &&
				predicate(booking_stream.front())) {

				Order current_order = booking_stream.front();
				booking_stream.pop();
	
				hotels_to_rooms[current_order.hotel]-=current_order.count;

				auto it_to_del = hotels_to_users_orders.find(current_order.hotel);
				it_to_del->second[current_order.id] -= current_order.count;
				if (it_to_del->second[current_order.id] == 0) {
					it_to_del->second.erase(it_to_del->second.begin());
				}

			}
		}	
	}

	struct Order {
		Order(const uint32_t& i, const int64_t& t, const string& h, const int& c)
			:id(i), time(t), hotel(h), count(c) {}

		uint32_t id = 0u;
		int64_t time = 0;
		string hotel = "";
		int count = 0;
	};


	map<string, map<uint32_t, int>> hotels_to_users_orders;
	map<string, int> hotels_to_rooms;
	queue<Order> booking_stream;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	BookingManager manager;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;

		if (query_type == "BOOK") {
			int64_t time;
			string hotel_name;
			uint32_t client_id;
			int room_count;

			cin >> time >> hotel_name >> client_id >> room_count;
			manager.book(time, hotel_name, client_id, room_count);
		}
		else if (query_type == "CLIENTS") {
			string hotel_name;

			cin >> hotel_name;
			cout << manager.clients(hotel_name) << '\n';
		}
		else if (query_type == "ROOMS") {
			string hotel_name;

			cin >> hotel_name;
			cout << manager.rooms(hotel_name) << '\n';
		}
	}

	return 0;
}
