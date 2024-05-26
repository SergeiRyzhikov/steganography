#ifndef QIM_H
#define QIM_H

#include <string>

int QIM_extract(std::string path);

int QIM_embed(std::string imagePath, std::string text, std::string imageName);

#endif