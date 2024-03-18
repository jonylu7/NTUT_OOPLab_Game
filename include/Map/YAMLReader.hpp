//
// Created by 盧威任 on 3/17/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_YAMLREADER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_YAMLREADER_HPP

#include "Util/Image.hpp"
#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>
class YAMLReader {
public:
    static std::shared_ptr<Util::Image> convertYAMLTileToImage(int id,
                                                               int index);

private:
    static std::shared_ptr<YAML::Node> m_mapTile;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_YAMLREADER_HPP
