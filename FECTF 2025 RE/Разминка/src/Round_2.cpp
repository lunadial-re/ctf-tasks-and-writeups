#include<iostream>
#include<cstdlib>
#include<string>
#include<array>
using namespace std;
static constexpr array<uint8_t,22> ENC = { 0x2F, 0x32, 0x2C, 0x21, 0x2F,
							0x34, 0x47, 0x52, 0x35, 0x41, 
							0x18, 0x49, 0x52, 0x3F, 0x52, 
							0x49, 0x18, 0x3D, 0x49, 0x4E, 
							0x36, 0x3A };
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
	string password = "youshallnotpass";
	string usr_pwd = "";
	cout << "Password:\t";
	cin >> usr_pwd;
	string flag = recover_secret();
	if (usr_pwd == password) cout << flag;
	else cout << "Wrong, think again\n";
	system("pause");
	return 0;
}