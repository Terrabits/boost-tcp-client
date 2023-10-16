/**
 * \file helpers.hpp
 * \brief rohdeschwarz helper function definition
 */


#ifndef ROHDESCHWARZ_HELPERS_HPP
#define ROHDESCHWARZ_HELPERS_HPP


// std lib
#include <string>
#include <vector>


namespace rohdeschwarz
{


// trim whitespace

/**
 * \brief Trims whitespace from left (beginning) of string
 */
std::string leftTrim(std::string text);


/**
 * \brief Trims whitespace from right (end) of string
 */
std::string rightTrim(std::string text);


/**
 * \brief Trims whitespace beginning and end of string
 */
std::string trim(const std::string& text);


// quotes

/**
 * \brief Checks for a quote at the beginning of the string
 *
 * Quotes can be single or double.
 *
 * \param[in] text C style string
 */
bool isLeftQuote(const char* text);


/**
 * \brief Checks for a quote at the beginning of the string
 *
 * Quotes can be single or double.
 *
 * \param[in] text C++ style string
 */
bool isLeftQuote(const std::string& text);


/**
 * \brief Checks for a quote at the end of the string
 *
 * Quotes can be single or double.
 *
 * \param[in] text C style string
 */
bool isRightQuote(const char* text);


/**
 * \brief Checks for a quote at the end of the string
 *
 * Quotes can be single or double.
 *
 * \param[in] text C++ style string
 */
bool isRightQuote(const std::string& text);


/**
 * \brief Checks for quotes at the beginning and end of the string
 *
 * Quotes can be single or double.
 *
 * \param[in] text C style string
 */
bool isQuoted(const char* text);


/**
 * \brief Checks for quotes at the beginning and end of the string
 *
 * Quotes can be single or double.
 *
 * \param[in] text C++ style string
 */
bool isQuoted(const std::string& text);


/**
 * \brief Surrounds string in quotes
 *
 * \param[in] text C style string to quote
 * \param[in] quote_character Quote to use; defaults to single quote
 */
std::string quote(const char* text, char quote_character = '\'');


/**
 * \brief Surrounds string in quotes
 *
 * \param[in] text C++ style string to quote
 * \param[in] quote_character Quote to use; defaults to single quote
 */
std::string quote(const std::string& text, char quote_character = '\'');


/**
 * \brief Removes quotes from beginning and end of string
 *
 * \param[in] text C style string to unquote
 */
std::string unquote(const char* text);


/**
 * \brief Removes quotes from beginning and end of string
 *
 * \param[in] text C++ style string to unquote
 */
std::string unquote(const std::string& text);


// split

/**
 * \brief Splits string on separator
 *
 * \param[in] csvList C style string to split
 * \param[in] separator Character to separate on; defaults to comma `,`
 */
std::vector<std::string> split(const char* csvList, const char separator = ',');


/**
 * \brief Splits string on separator
 *
 * \param[in] csvList C++ style string to split
 * \param[in] separator Character to separate on; defaults to comma `,`
 */
std::vector<std::string> split(const std::string& csvList, const char separator = ',');


}      // rohdeschwarz
#endif // ROHDESCHWARZ_HELPERS_HPP
