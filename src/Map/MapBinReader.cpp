//
// Created by 盧威任 on 3/30/24.
//
#include "Map/MapBinReader.hpp"
std::vector<std::vector<std::shared_ptr<TileClass>>>
MapBinReader::readBin(const std::string filepath, int width, int hieght) {

    std::vector<std::vector<std::shared_ptr<TileClass>>> fullmap;
    std::vector<std::shared_ptr<TileClass>> mapRow;
    auto file = MapBinReader::readBinFiles(filepath);

    unsigned char data;

    int i = 0;
    int k = 0;
    int imageId = 0;
    int imageIndex = 0;
    int case1hasValue = -1;
    while (file.read(reinterpret_cast<char *>(&data), 1)) {

        if ((i - 17) / 3 >= width * hieght) {
            break;
        }
        if (i >= 17) {
            // std::cout << static_cast<int>(data) << " ";
            switch (k) {
            case 0:
                imageId = static_cast<int>(data);
                break;
            case 1:
                /*
                if (!(static_cast<int>(data) == 255 ||
                      static_cast<int>(data) == 0)) {
                    imageIndex = static_cast<int>(data);
                    case1hasValue = 1;
                }
                 */
                break;
            case 2:
                if (case1hasValue != 1) {
                    imageIndex = static_cast<int>(data);
                }

                auto tileimage =
                    YAMLReader::convertYAMLTileToImagePath(imageId, imageIndex);

                auto tile =
                    YAMLReader::convertYAMLTileToTileClass(imageId, imageIndex);
                // mapRow.push_back(std::make_shared<TileClass>(*tile));
                mapRow.insert(mapRow.begin() + 0,
                              std::make_shared<TileClass>(*tile));
                imageId = 0;
                k = -1;
                imageIndex = 0;
                // std::cout << " " << i << "\n";

                if (((i - 16) / 3) % (width) == 0) {
                    // fullmap.push_back(mapRow);
                    fullmap.insert(fullmap.begin() + 0, mapRow);
                    mapRow.clear();
                }
                case1hasValue = -1;
                break;
            }
            k++;
        }

        i++;
    }

    // Close the file
    file.close();
    return fullmap;
}

std::ifstream MapBinReader::readBinFiles(const std::string filepath) {
    std::ifstream file(filepath, std::ios::binary);
    // Open the binary file
    // Check if the file is opened successfully
    if (!file.is_open()) {
        LOG_DEBUG("Error opening bin file!");
    }
    return file;
}
