#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include<array>
using namespace std;

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ptrace.h>
#include <unistd.h>
#endif

static constexpr array<uint8_t, 9> ENC = { 0x13, 0x81, 0x18, 0x20, 0x81, 0x3B, 0x42, 0x51, 0x7D };
static constexpr uint8_t XOR_KEY = 0x5A;
static constexpr uint8_t ADD = 0x13;
string recover_secret() {
    string out;
    out.reserve(ENC.size());
    for (size_t i = 0; i < ENC.size(); ++i) {
        uint8_t e = ENC[i];
        uint8_t tmp = static_cast<uint8_t>((e - ADD) & 0xFF);
        uint8_t orig = static_cast<uint8_t>(tmp ^ XOR_KEY);
        out.push_back(static_cast<char>(orig));
    }
    return out;
}


bool is_debugger_present() {
#ifdef _WIN32
    return IsDebuggerPresent();
#else
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) {
        return true;
    }
    return false;
#endif
}

string generate_password() {
    time_t now = time(nullptr);
    tm* local_time = localtime(&now);
    int seed = local_time->tm_hour;

    srand(seed);

    string password;
    for (int i = 0; i < 8; ++i) {
        password += 'A' + (rand() % 26);
    }

    return password;
}



bool check_code_integrity() {

    volatile auto func_ptr = &generate_password;
    volatile unsigned char* code_ptr = reinterpret_cast<unsigned char*>(func_ptr);

    unsigned char simple_hash = 0;
    for (int i = 0; i < 32; ++i) { 
        simple_hash ^= code_ptr[i];
    }
    return simple_hash != 0; 
}

int main() {

    if (is_debugger_present()) {
        cout << "Debugger detected! Exiting..." << endl;
        return -1;
    }

    if (!check_code_integrity()) {
        cout << "Code integrity check failed!" << endl;
        return -1;
    }

    cout << "Enter password: ";

    string input;
    cin >> input;

    string correct_password = generate_password();

    if (input == correct_password) {
        string flag = recover_secret();
        cout << "Congratulations! FECTF{" << flag<<"}" << endl;
    }
    else {
        cout << "Wrong password! Try again." << endl;
    }
    system("pause");
    return 0;
}