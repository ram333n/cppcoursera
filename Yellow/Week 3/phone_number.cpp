#include "phone_number.h"
#include <sstream>
#include <iostream>
/* Принимает строку в формате +XXX-YYY-ZZZZZZ
    Часть от '+' до первого '-' - это код страны.
    Часть между первым и вторым символами '-' - код города
    Всё, что идёт после второго символа '-' - местный номер.
    Код страны, код города и местный номер не должны быть пустыми.
    Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.

    Примеры:
    * +7-495-111-22-33 *
    * +7-495-1112233 *
    * +323-22-460002 *
    * +1-2-coursera-cpp *
    * 1-2-333 - некорректный номер - не начинается на '+' *
    * +7-1233 - некорректный номер - есть только код страны и города *
 */

PhoneNumber::PhoneNumber(const string& international_number) {
    istringstream is(international_number);

    char sign = is.get();
    getline(is, country_code_, '-');
    getline(is, city_code_, '-');
    getline(is, local_number_);

    if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
        throw invalid_argument("Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: " + international_number);
    }
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return ("+" + country_code_ + "-" + city_code_ + "-" + local_number_);
}
int main() {
    try {
        PhoneNumber n("+7-1233");
        cout << "County code : " << n.GetCountryCode() << endl;
        cout << "City code : " << n.GetCityCode() << endl;
        cout << "Local code : " << n.GetLocalNumber() << endl;
        cout << "Phone number : " << n.GetInternationalNumber() << endl;
    }
    catch (invalid_argument& ex) {
        cout << ex.what() << endl;
    }
}