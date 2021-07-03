#include <iostream>
#include "query.h"

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