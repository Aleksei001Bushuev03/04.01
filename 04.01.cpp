#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

class Address {
private:
    std::string city;
    std::string street;
    int house_number;
    int apartment_number;

public:
    Address(const std::string& city, const std::string& street, int house_number, int apartment_number)
        : city(city), street(street), house_number(house_number), apartment_number(apartment_number) {}

    std::string get_output_address() const {
        return city + ", " + street + ", " + std::to_string(house_number) + ", " + std::to_string(apartment_number);
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::ifstream input_file("in.txt");
    std::ofstream output_file("out.txt");

    if (!input_file.is_open() || !output_file.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    int address_count;
    input_file >> address_count;
    input_file.ignore(); 

    Address** addresses = new Address * [address_count];

    for (int i = 0; i < address_count; ++i) {
        std::string city, street;
        int house_number, apartment_number;

        std::getline(input_file, city);
        std::getline(input_file, street);
        input_file >> house_number >> apartment_number;
        input_file.ignore(); 

        addresses[i] = new Address(city, street, house_number, apartment_number);
    }

    output_file << address_count << std::endl;

    for (int i = address_count - 1; i >= 0; --i) {
        output_file << addresses[i]->get_output_address() << std::endl;
        delete addresses[i]; 
    }

    delete[] addresses;

    input_file.close();
    output_file.close();

    std::cout << "Адреса успешно записаны в файл out.txt в обратном порядке." << std::endl;

    return 0;
}
