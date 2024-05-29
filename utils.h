#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

int randomBinary();

std::string convertText(std::string text);

std::string toBinary(int decimal);

int binaryToDecimal(const std::string &binary);

std::string convertExtractText(std::string extractedText);

std::string addZeros(std::string s);
#endif