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
class MapBinReader {
public:
    static std::ifstream readBinFiles(const std::string filepath);
    static std::vector<std::vector<std::shared_ptr<TileClass>>>
    readBin(const std::string filepath, int width, int hieght);
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MAPBINREADER_HPP
