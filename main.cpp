// #include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
// #include <vector>
// #include <cmath>
// #include "utils.h"
#include "LSB.h"
#include "PM1.h"
#include "QIM.h"

using namespace std;


int main() {
    string text;
    // cin >> text;
    QIM_embed("steg1.png", "hi stegongrap", "new_image.png");
    QIM_extract("new_image.png");

    return 0;
}


