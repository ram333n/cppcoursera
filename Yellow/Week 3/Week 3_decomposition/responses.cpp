#include "responses.h"

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
