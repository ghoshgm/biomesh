#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

int main() {
    try {
        // Load the YAML file
        YAML::Node config = YAML::LoadFile("/home/ghoshgm/Desktop/dev/biomesh/test/config.yaml");

        // Access values
        int steps = config["simulation"]["steps"].as<int>();
        double timestep = config["simulation"]["timestep"].as<double>();
        std::string method = config["physics"]["method"].as<std::string>();
        double temperature = config["physics"]["temperature"].as<double>();

        // Print them out
        std::cout << "Simulation steps: " << steps << "\n";
        std::cout << "Timestep: " << timestep << "\n";
        std::cout << "Physics method: " << method << "\n";
        std::cout << "Temperature: " << temperature << " K" << std::endl;
    }
    catch (const YAML::Exception& e) {
        std::cerr << "Error parsing YAML file: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
