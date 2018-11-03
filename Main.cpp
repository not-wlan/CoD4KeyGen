#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <array>

constexpr unsigned int calculate_checksum(char(&key)[16]) {
	// straight outta IDA B)
	auto v2 = 0u;
	auto v3 = 0;
	do
	{
		v2 ^= key[v3];
		auto v4 = 8;
		do
		{
			// is odd
			if (v2 & 1)
				v2 ^= 0x14002u;
			v2 >>= 1;
			--v4;
		} while (v4);
		++v3;
	} while (v3 < 16);
	return v2;
}

int main(const int, char**) {
	std::printf("open source keygen for CoD4 | http://github.com/not-wlan\n");
	std::printf("for *EDUCATIONAL* purposes only!\n\n");

	char base[16] = {};

	srand(static_cast<unsigned>(time(nullptr)));
	
	const auto random_char = []() -> char{
		constexpr const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		return charset[rand() % (std::size(charset) - 1)];
	};

	std::generate(std::begin(base), std::end(base), random_char);

	const auto checksum = calculate_checksum(base);

	for (auto i = 0u; i < std::size(base); i += 4) {
		std::printf("%.*s-", 4, &base[i]);
	}
	
	std::printf("%04X\n", checksum);
}
