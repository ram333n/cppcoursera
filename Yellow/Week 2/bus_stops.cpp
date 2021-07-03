#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

// ajvbko;ejlipggjl;ioea

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string command;
    is >> command;
    if (command == "NEW_BUS") {
        q.type = QueryType::NewBus;
        int stop_count;
        is >> q.bus >> stop_count;
        q.stops.resize(stop_count);
        for (string& s : q.stops) {
            is >> s;
        }
    }
    else if (command == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (command == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (command == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    vector<string> buses_for_stop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses_for_stop.empty()) {
        os << "No stop";
    }
    else {
        for (const string& b : r.buses_for_stop) {
            os << b << " ";
        }
    }
    return os;
}

struct StopsForBusResponse {
    string bus_name;
    vector<string> stops;
    map<string, vector<string>> stops_to_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops.empty()) {
        os << "No bus";
    }
    else {
        for (const string& s : r.stops) {
            os << "Stop " << s << ": ";
            if (r.stops_to_buses.at(s).size() == 1) {
                os << "no interchange";
            }
            else {
                for (const string& bus : r.stops_to_buses.at(s)) {
                    if (bus != r.bus_name) {
                        os << bus << " ";
                    }
                }
            }
            os << endl;
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses.empty()) {
        os << "No buses";
    }
    else {
        for (const auto& bus : r.buses) {
            os << "Bus " << bus.first << ": ";
            for (const string& stop : bus.second) {
                os << stop << " ";
            }
            os << endl;
        }
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (const string& stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }
    //const methods
    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse result;
        if (stops_to_buses.count(stop)) {
            result.buses_for_stop = stops_to_buses.at(stop);
        }
        return result;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse result;
        result.bus_name = bus;
        if (buses_to_stops.count(bus)) {
            result.stops = buses_to_stops.at(bus);
        }
        result.stops_to_buses = stops_to_buses;
        return result;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse result;
        result.buses = buses_to_stops;
        return result;
    }
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

/*int main() {

    int query_count;
    Query q;

    cin >> query_count;
    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}
*/