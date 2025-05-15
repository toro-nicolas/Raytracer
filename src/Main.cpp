/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The main function of the program
*/
/**
 * @file main.cpp
 * @brief The main function of the program
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Core/Core.hpp"

int main(int ac, char **av)
{
    try {
        Raytracer::Core core(ac, av);
        core.run();
    } catch (const Lib::Exceptions::Help &e) {
        if (!std::string(e.what()).empty())
            ERROR << "ERROR: " << e.what();
        std::cerr << "USAGE:" << std::endl;
        std::cerr << "\t./raytracer <scene_file> [options]" << std::endl;
        std::cerr << "DESCRIPTION:" << std::endl;
        std::cerr << "\tThe raytracer generates a 3D scene based on the provided scene file." << std::endl;
        std::cerr << "\t<scene_file>\t\tThe scene file to load" << std::endl;
        std::cerr << "OPTIONS:" << std::endl;
        std::cerr << "\t-h, --help\t\tDisplay this help message" << std::endl;
        std::cerr << "\t-v, --version\t\tDisplay the version of the program" << std::endl;
        std::cerr << "\t-o, --output <file>\tSpecify the output file path" << std::endl;
        std::cerr << "\t-c, --config <file>\tSpecify the configuration file path" << std::endl;
        return 84;
    } catch (const Lib::Exceptions::Critical &e) {
        ERROR << "CRITICAL ERROR: " << e.what();
        return 84;
    } catch (const std::exception &e) {
        ERROR << "EXCEPTION: " << e.what();
        return 84;
    }
    return 0;
}
