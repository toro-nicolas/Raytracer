/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Sfml class declaration
*/
/**
 * @file Sfml.hpp
 * @brief The Sfml class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

 #ifndef SFML_HPP_
 #define SFML_HPP_

 #include "AInterface.hpp"
 #include <fstream>

 #include <SFML/Graphics.hpp>

namespace Raytracer {
 /**
  * @class Sfml
  * @brief Class for rendering images in Graphics Library (SFML) format
  */
 class Sfml final : public AInterface {
     public:
         /* Constructor and Destructor */

         /**
          * @brief Constructor for Sfml class
          */
         Sfml(void);

         /**
          * @brief Destructor for Sfml class
          */
         ~Sfml();

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
          * @brief Render the image in SFML format
          */
         void render() override;

     private:
        std::string _filename; ///< Name of the output file
        sf::Image _image; ///< SFML image for pixel manipulation
        sf::Texture _texture; ///< SFML texture for displaying the image
        sf::Sprite _sprite; ///< SFML sprite for rendering the image
        sf::RenderWindow _window; ///< SFML window for rendering
 };

 /**
  * @brief Create a Sfml interface
  * @return <b>std::unique_ptr<IInterface></b> A unique pointer to the Sfml interface
  */
 extern "C" std::unique_ptr<IInterface> createInterface(void);
}

#endif /* SFML_HPP_ */