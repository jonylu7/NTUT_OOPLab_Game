//
// Created by 盧威任 on 3/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MAPBINREADER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MAPBINREADER_HPP
#include "Tile.hpp"
#include "YAMLReader.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

//../assets/map/CIFSTE/map.bin
//"../assets/map/ore/map.bin"
class MapbinReader {
public:
    MapbinReader() {}
    ~MapbinReader() {}

    static std::ifstream readBinFiles(const std::string filepath) {
        std::ifstream file(filepath, std::ios::binary);
        // Open the binary file
        // Check if the file is opened successfully
        if (!file.is_open()) {
            LOG_DEBUG("Error opening bin file!");
        }
        return file;
    }
    std::vector<std::vector<std::shared_ptr<TileClass>>>
    readBin(const std::string filepath, int width, int hieght) {

        std::vector<std::vector<std::shared_ptr<TileClass>>> fullmap;
        std::vector<std::shared_ptr<TileClass>> mapRow;
        auto file = readBinFiles(filepath);

        unsigned char data;

        int i = 0;
        int k = 0;
        int imageId = 0;
        int imageIndex = 0;
        while (file.read(reinterpret_cast<char *>(&data), 1)) {
            if (i > width * hieght) {
                break;
            }
            if (i >= 17) {
                // std::cout << static_cast<int>(data) << " ";
                switch (k) {
                case 0:
                    imageId = static_cast<int>(data);
                    break;
                case 1:
                    break;
                case 2:
                    imageIndex = static_cast<int>(data);
                    auto tileimage =
                        YAMLReader::convertYAMLTileToImage(imageId, imageIndex);

                    auto tile = YAMLReader::convertYAMLTileToTileClass(
                        imageId, imageIndex);
                    mapRow.push_back(tile);
                    imageId = 0;
                    k = -1;
                    imageIndex = 0;
                    // std::cout << "\n";
                    break;
                }
                k++;
            }

            i++;
            if (i % width == 0) {
                fullmap.push_back(mapRow);
                mapRow.clear();
            }
        }

        // Close the file
        file.close();

        return fullmap;
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MAPBINREADER_HPP
