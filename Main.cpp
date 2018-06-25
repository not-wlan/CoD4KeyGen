#include <string>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>

template<class OutIt>
void random_chars(OutIt begin, OutIt end) {
    const auto randchar = []() -> char
    {
        constexpr const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        return charset[rand() % (std::size(charset)-1)];
    };

    while (begin != end) {
        *begin = randchar();
        ++begin;
    }
}

unsigned int get_checksum(const std::string& key) {
    // We need 16 (Random) Characters for this to work
    assert(key.length() == 16);

    // Variables for the Loop
    unsigned int v2 = 0;
    auto v3 = 0;

    do
    {
        // Binary XOR
        v2 ^= *(std::uint8_t*)(v3 + key.c_str());
        auto v4 = 8;
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
    return v2;
}

int main(const int argc, char * argv[]) {
    std::printf("Open Source Keygen for CoD4 | http://github.com/not-wlan\n");
    std::printf("For EDUCATIONAL Purposes only!\n\n");

    std::string base(16, ' ');

    if (argc == 2) {
        std::string option = argv[1];

        // User set a base
        if (option.length() == 16) {
            std::transform(option.begin(), option.end(), option.begin(), toupper);

            if (!std::all_of(option.begin(), option.end(), isalnum)) {
                std::printf("Please make sure the entered base is all uppercase and alphanumeric!\n");
                return EXIT_FAILURE;
            }
            base = option;
        }
        else {
            printf("Usage: CoD4KeyGen.exe [optional 16 Char key base here]\n");
            return EXIT_SUCCESS;
        }
    }
    else {
        // Seed the PRNG
        srand(static_cast<unsigned>(time(nullptr)));
        random_chars(base.begin(), base.end()); 
    }

    const auto checksum = get_checksum(base);

    for(auto i = 0u; i < base.length(); i += 4) {
        printf("%s ", base.substr(i, 4).c_str());
    }

    std::printf("%04X\n", checksum);
}
