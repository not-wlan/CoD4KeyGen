#include "Windows.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Macro to ensure valid user input
static inline bool is_invalid_keychar(char c)
{
	return !(isalnum(c) && islower(c));
}

// Taken from https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
std::string random_string(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

string GetChecksum(string key) {
	// We need 16 (Random) Characters for this to work
	if (key.length() != 16) {
		return "";
	}

	// Convert the string to a C String for some bitshifting
	const char * cdkey_arr = key.c_str();
	char checksum[5];

	// Variables for the Loop
	unsigned int v2 = 0; 
	signed int v3 = 0;
	signed int v4;

	do
	{
		// Binary XOR
		v2 ^= *(BYTE *)(v3 + cdkey_arr);
		v4 = 8;
		do
		{
			// Binary AND
			if (v2 & 1)
				// Binary XOR
				v2 ^= 0x14002u;
			// Binary Right Shift
			v2 >>= 1;
			--v4;
		} while (v4);
		++v3;
	} while (v3 < 16);

	// Format the checksum
	sprintf_s(&checksum[0], sizeof(checksum), "%04x", v2);
	return string(checksum);
}

int main(int argc, char * argv[]) {
	printf("Open Source Keygen for CoD4 | http://github.com/jafrewa\n");
	printf("For EDUCATIONAL Purposes only!\n\n");

	string base(16, ' ');
	string checksum;
	string cdkey;

	if (argc == 2) {
		
		string option = argv[1];

		// User set a base
		if (option.length() == 16) {
			if (find_if(option.begin(), option.end(), is_invalid_keychar) == option.end()) {
				printf("Please make sure the entered base is all uppercase and alphanumeric!\n");
				return 0;
			}
			base = option;
		}
		else {
			printf("Usage: CoD4KeyGen.exe [optional 16 Char key base here]\n");
			return 0;
		}
	} else {
		// Seed the PRNG
		srand(static_cast<unsigned int>(time(NULL)) * GetCurrentProcessId());
		base = random_string(16);
	}

	// For a prettier output make the checksum all uppercase
	checksum = GetChecksum(base);
	for (auto & c : checksum) c = toupper(c);

	// Merge base and Checksum
	cdkey = base + checksum;

	cout << cdkey.substr(0, 4) << " " << cdkey.substr(4, 4) << " " << cdkey.substr(8, 4) << " " << cdkey.substr(12, 4) << " " << cdkey.substr(16, 4) << endl;
}