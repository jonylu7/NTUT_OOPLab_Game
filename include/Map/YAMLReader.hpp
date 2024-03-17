//
// Created by 盧威任 on 3/17/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_YAMLREADER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_YAMLREADER_HPP

#include <iostream>
#include <yaml-cpp/yaml.h>
class YAMLReader {
public:
    int readYAML() {
        std::vector<std::string> allFiles;
        // Parse the YAML file
        YAML::Node config = YAML::LoadFile("../assets/map/temperat.yaml");
        if (config.IsNull()) {
            std::cerr << "Error parsing YAML file!" << std::endl;
            return 1;
        }
        for (auto i : config["Templates"]) {
            std::cout << i.second["Id"] << std::endl;
            // temperat[(std::to_string(i.first)] = i.second;
        }

        return 0;
    }
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_YAMLREADER_HPP
