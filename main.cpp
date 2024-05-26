#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "utils.h"
#include "LSB.h"

using namespace std;

int PM1_embed(string path, string text) {
    string binaryText = convertText(text);
    
    cv::Mat image = cv::imread(path);

    if(image.empty()) {
        cout << "Невозможно загрузить изображение. Проверьте путь к файлу." << endl;
        return -1;
    }
    // Получаем размеры изображения
    int rows = image.rows;
    int cols = image.cols;
    int rounds = 0;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (rounds < binaryText.length()) {
                char bit = binaryText[rounds];
                cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

                if (pixel[0]%2 != static_cast<int>(bit) ){
                    int r = randomBinary();
                    if (r==1){
                        pixel[0] -=1;
                    }
                    else{
                        pixel[0] +=1;
                    }
                    
                }
                image.at<cv::Vec3b>(y, x) = pixel;
            }
            else{
                break;
            }
            rounds +=1;
        }
    }
    // Сохраняем измененное изображение
    cv::imwrite("new_image.png", image);
    return 0;
}



int main() {

    LSB_embed("steg1.png", "my text");
    LSB_extract("new_image.png");

    return 0;
}


