#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

std::string generate_password() {
    time_t now = time(nullptr);
    tm* local_time = localtime(&now);
    int seed = local_time->tm_hour;
    srand(seed);
    std::string password;
    for (int i = 0; i < 8; ++i) {
        password += 'A' + (rand() % 26);
    }
    return password;
}


int main() {
    std::string pass = generate_password();
    std::cout << pass << std::endl;

}