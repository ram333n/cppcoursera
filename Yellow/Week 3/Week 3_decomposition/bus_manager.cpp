#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (const string& stop : stops) {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    BusesForStopResponse result;
    if (stops_to_buses.count(stop)) {
        result.buses_for_stop = stops_to_buses.at(stop);
    }
    return result;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    StopsForBusResponse result;
    result.bus_name = bus;
    if (buses_to_stops.count(bus)) {
        result.stops = buses_to_stops.at(bus);
    }
    result.stops_to_buses = stops_to_buses;
    return result;
}

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse result;
    result.buses = buses_to_stops;
    return result;
}