#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>

using namespace std;

void p1_main() {
    int q;
    cin >> q;

    map<set<string>, int> buses;

    for (int i = 0; i < q; ++i) {
        int n;
        cin >> n;
        set<string> stops;
        for (int j = 0; j < n;j++) {
            string temp;
            cin >> temp;
            stops.insert(temp);
        }

        // проверяем, не существует ли уже маршрут с таким набором остановок
        if (buses.count(stops) == 0) {

            // если не существует, нужно сохранить новый маршрут;
            // его номер на единицу больше текущего количества маршрутов
            const int new_number = buses.size() + 1;
            buses[stops] = new_number;
            cout << "New bus " << new_number << endl;

        }
        else {
            cout << "Already exists for " << buses[stops] << endl;
        }
    }
}
