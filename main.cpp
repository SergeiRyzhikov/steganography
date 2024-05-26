#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "utils.h"
#include "PM1.h"
using namespace std;


int main() {

    PM1_embed("steg1.png", "my text");
    PM1_extract("new_image.png");

    return 0;
}


