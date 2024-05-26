#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "utils.h"
#include "LSB.h"
#include "PM1.h"

using namespace std;

int main() {
    string text;
    // cin >> text;
    PM1_embed("steg1.png", "hi my name is sergei");
    PM1_extract("new_image.png");

    return 0;
}


