#include<iostream>
#include<cstdlib>
#include<string>
#include<array>
using namespace std;
static constexpr array<uint8_t, 25> ENC = { 0x2F, 0x32, 0x2C, 0x21, 0x2F, 
											0x34, 0x3B, 0x52, 0x4E, 0x51, 
											0x36, 0x18, 0x4F, 0x48, 0x3B, 
											0x18, 0x4E, 0x47, 0x36, 0x41, 
											0x45, 0x46, 0x47, 0x50, 0x3A};
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

int main() {
	string flag = recover_secret();
	int pwd = 0;
	cout << "Password: ";
	cin >> pwd;
	if (pwd == 0x400) cout << "\n" << flag << endl;
	else cout << "Wrong, think again\n";
	system("pause");
	return 0;
}