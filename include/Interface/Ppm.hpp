/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Ppm class declaration
*/
/**
 * @file Ppm.hpp
 * @brief The Ppm class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef PPM_HPP_
    #define PPM_HPP_

    #include "AInterface.hpp"

namespace Raytracer {
    /**
     * @class Ppm
     * @brief Class for rendering RtwImages in PPM format
     */
    class Ppm final : public AInterface {
        public:
            /* Constructor and Destructor */

            /**
             * @brief Constructor for Ppm class
             */
            Ppm(void);

            /**
             * @brief Destructor for Ppm class
             */
            ~Ppm();
            
            /**
             * @brief Resize the resolution of the output image
             */
            void resize() override;

            /**
             * @brief Setup the output file
             * @param filename The name of the output file
             */
            void setupOutputFile(const std::string &filename) override;

            /**
             * @brief Render the image in PPM format
             */
            void render() override;



        private:
            std::string _filename; ///< Name of the output file
            std::ofstream _file; ///< Output file stream for the PPM file
    };



    /**
     * @brief Create a Ppm interface
     * @return <b>std::unique_ptr<IInterface></b> A unique pointer to the Ppm interface
     */
    extern "C" std::unique_ptr<IInterface> createInterface(void);
}

#endif /* PPM_HPP_ */