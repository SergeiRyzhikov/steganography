#ifndef LSB_H
#define LSB_H

#include <string>

int LSB_extract(std::string path);

int LSB_embed(std::string imagePath, std::string text, std::string imageName);

#endif