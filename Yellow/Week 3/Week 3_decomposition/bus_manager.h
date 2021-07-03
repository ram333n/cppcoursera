#pragma once
#include "responses.h"

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops);
    //const methods
    BusesForStopResponse GetBusesForStop(const string& stop) const;

    StopsForBusResponse GetStopsForBus(const string& bus) const;

    AllBusesResponse GetAllBuses() const;
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};
