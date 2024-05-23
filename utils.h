#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

std::string convertText(std::string text);

std::string toBinary(int decimal);

int binaryToDecimal(const std::string& binary);

std::string convertExtractText(std::string extractedText);
#endif