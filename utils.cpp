#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace std;

/**
 * @file utils.cpp
 * @brief Utils function for embeding and extracting.
 *
 */

/**
 * @brief Generates a random binary digit (0 or 1).
 *
 * @return int Random binary digit (0 or 1).
 */
int randomBinary()
{
    return rand() % 2;
}

/**
 * @brief Adds leading zeros to a string to make its length 8.
 *
 * @param s The input string.
 * @return std::string The input string with leading zeros added to make its length 8.
 */
string addZeros(string s)
{
    if (s.length() < 8)
    {
        s.insert(0, 8 - s.length(), '0');
    }
    return s;
}

/**
 * @brief Converts a decimal number to its binary representation as a string.
 *
 * @param decimal The decimal number to be converted.
 * @return std::string The binary representation of the decimal number.
 * @throw std::invalid_argument If the decimal number is negative.
 */
string toBinary(int decimal)
{
    if (decimal == 0)
        return "0";
    if (decimal < 0)
        throw invalid_argument("Negative numbers are not supported");

    string binary = "";
    while (decimal > 0)
    {
        int remainder = decimal % 2;
        binary = to_string(remainder) + binary;
        decimal /= 2;
    }

    return binary;
}

/**
 * @brief Converts a text string to its binary representation.
 *
 * @param text The text string to be converted.
 * @return std::string The binary representation of the text string.
 * @throw std::invalid_argument If the text contains unsupported characters.
 */
string convertText(string text)
{
    string data;
    for (int i = 0; i < text.length(); ++i)
    {
        if (int(text[i]) > 0 && int(text[i]) < 256)
        {
            string binary = addZeros(toBinary(int(text[i])));
            for (int j = 0; j < binary.length(); ++j)
            {
                data += binary[j];
            }
        }
        else
        {
            throw invalid_argument("Such symbols are not supported");
        }
    }
    return data;
}

/**
 * @brief Converts a binary string to its decimal representation.
 *
 * @param binary The binary string to be converted.
 * @return int The decimal representation of the binary string.
 * @throw std::invalid_argument If the binary string contains characters other than '0' or '1'.
 */
int binaryToDecimal(const std::string &binary)
{
    int decimal = 0;
    int power = 1;

    for (int i = binary.size() - 1; i >= 0; --i)
    {
        if (binary[i] == '1')
        {
            decimal += power;
        }
        if (binary[i] != '0' && binary[i] != '1')
        {
            throw invalid_argument("Binary number must have only 0 or 1 in writing");
        }
        power *= 2;
    }

    return decimal;
}

/**
 * @brief Converts a binary string representing text back to its original text form.
 *
 * @param extractedText The binary string representing the text.
 * @return std::string The original text.
 */
string convertExtractText(string extractedText)
{
    string text;
    for (int i = 0; i < extractedText.length(); i += 8)
    {
        int code = binaryToDecimal(extractedText.substr(i, 8));
        if (code > 31 && code < 127)
        {
            text += char(code);
        }
    }
    return text;
}
