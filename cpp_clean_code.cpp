#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <memory>
#include <numeric>
#include <ctime>

constexpr double kPi = 3.1415926535;
constexpr int kMax = 1000;

struct User {
    std::string name;
    int age;
    std::string city;
};

// Базовий клас із віртуальним деструктором
class Base {
public:
    virtual void run() { std::cout << "base\n"; }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void run() override { std::cout << "derived\n"; }
    ~Derived() override = default;
};

// Функція створення об'єкту
std::unique_ptr<Base> makeRandomBase() {
    if (rand() % 2) {
        return std::make_unique<Base>();
    } else {
        return std::make_unique<Derived>();
    }
}

// Підрахунок суми вектора
int sumVector(const std::vector<int>& v) {
    return std::accumulate(v.begin(), v.end(), 0);
}

// Проста функція для парсингу конфігу
void parseConfig(const std::string& path, std::map<std::string, std::string>& out) {
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line, ',')) {
        auto eq_pos = line.find('=');
        if (eq_pos != std::string::npos) {
            std::string key = line.substr(0, eq_pos);
            std::string value = line.substr(eq_pos + 1);
            out[key] = value;
        }
    }
}

// Форматування інформації користувача
std::string formatUser(const User& u) {
    return u.name + " - age:" + std::to_string(u.age) + " - city:" + u.city;
}

int main(int argc, char** argv) {
    srand(static_cast<unsigned>(time(nullptr)));
    std::cout << "start\n";

    std::vector<int> a{1,2,3,4,5,6,7,8,9,10};
    std::vector<int> b{1,2,3,4,5,6,7,8,9,10};

    int totalA = sumVector(a);
    int totalB = sumVector(b);

    std::map<std::string, std::string> config;
    parseConfig("data.txt", config);

    std::string mode = (argc > 1) ? argv[1] : (config.count("mode") ? config["mode"] : "x");

    if (mode == "x" || mode == "y" || mode == "z") {
        std::cout << "MODE:" << mode << " TOTAL_A=" << totalA << " TOTAL_B=" << totalB << " pi=" << kPi << "\n";
    } else {
        std::cout << "UNKNOWN MODE\n";
    }

    // Використання класів
    auto obj = makeRandomBase();
    obj->run();

    std::cout << "done\n";
    return 0;
}