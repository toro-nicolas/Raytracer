/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Exceptions class declaration
*/
/**
 * @file Exceptions.hpp
 * @brief The Exceptions class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef EXCEPTIONS_HPP_
    #define EXCEPTIONS_HPP_

    #include <exception>
    #include <string>

namespace Lib {
    /**
     * @class Exceptions
     * @brief Class for all exceptions
     */
    class Exceptions
    {
        public:
            /**
             * @class Critical
             * @brief Class for all critical exceptions
             */
            class Critical : public std::exception
            {
                public:
                    /**
                     * @brief Constructor of the Critical
                     * @param message The message of the Critical
                     */
                    Critical(const std::string &message) : _message(message) { }

                    /**
                     * @brief Destructor of the Critical
                     */
                    ~Critical() override = default;

                    /**
                     * @brief Get the message of the exception
                     * @return <b>const char *</b> The message of the exception
                     */
                    const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }

                private:
                    std::string _message; /* The message of the exception */
            };



            /**
             * @class Warning
             * @brief Class for all warning exceptions
             */
            class Warning : public std::exception
            {
                public:
                    /**
                     * @brief Constructor of the Warning
                     * @param message The message of the Warning
                     */
                    Warning(const std::string &message) : _message(message) { }

                    /**
                     * @brief Destructor of the Warning
                     */
                    ~Warning() override = default;

                    /**
                     * @brief Get the message of the exception
                     * @return <b>const char *</b> The message of the exception
                     */
                    const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }

                private:
                    std::string _message; /* The message of the exception */
            };



            /**
             * @class Help
             * @brief Class for all help exceptions
             */
            class Help : public std::exception
            {
                public:
                    /**
                     * @brief Constructor of the Help
                     * @param message The message of the Help
                     */
                    Help(const std::string &message) : _message(message) { }

                    /**
                     * @brief Destructor of the Help
                     */
                    ~Help() override = default;

                    /**
                     * @brief Get the message of the exception
                     * @return <b>const char *</b> The message of the exception
                     */
                    const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }

                private:
                    std::string _message; /* The message of the exception */
            };
    };
}

#endif /* EXCEPTIONS_HPP_ */
