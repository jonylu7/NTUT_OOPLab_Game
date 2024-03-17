//
// Created by 盧威任 on 3/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MAPBINREADER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MAPBINREADER_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

//../assets/map/CIFSTE/map.bin
class MapbinReader {
private:
public:
    MapbinReader() {}
    ~MapbinReader() {}
    int readBin() {

        // Open the binary file
        // std::ifstream file("../assets/map/d09.jun", std::ios::binary);
        std::ifstream file("../assets/map/test/map.bin", std::ios::binary);

        // Check if the file is opened successfully
        if (!file.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return 1;
        }

        // Read the file byte by byte
        unsigned char byte;
        // Example byte with 8 bits
        unsigned char eightBits; // Example byte: 10101010

        // Truncate the two least significant bits to get 6 bits

        // Process the byte (you need to know the file structure)
        // For example, you might print each byte to the console
        // read hex
        int i = 0;
        std::string wordList =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        int k = 0;
        while (file.read(reinterpret_cast<char *>(&eightBits), 1)) {
            unsigned char sixBits =
                eightBits >> 2; // Right shift to drop 2 leastsignificant bits
            // std::cout << std::bitset<6>(eightBits) << " ";
            if (i >= 17) {
                std::cout << static_cast<int>(eightBits) << " ";

                switch (k) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    k = 0;
                    break;
                }
            }

            i++;
        }

        // 12+12*8=108
        /*
        unsigned char byte;
        int max = 16;
        unsigned int i = 0;
        while (file.read(reinterpret_cast<char *>(&byte), sizeof(byte))) {

            std::cout << std::hex << std::setw(2) << std::setfill('0')
                      << static_cast<int>(byte) << " ";
            if ((i - 17) % 5 == 0) {
                std::cout << "\n";
            }

            i++;
        }


        std::cout << "\n" << std::to_string(i) << std::endl;
        */
        // Close the file
        file.close();

        return 0;
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MAPBINREADER_HPP
