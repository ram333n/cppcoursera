#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct BusesForStopResponse {
    vector<string> buses_for_stop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
    string bus_name;
    vector<string> stops;
    map<string, vector<string>> stops_to_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
    map<string, vector<string>> buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);
