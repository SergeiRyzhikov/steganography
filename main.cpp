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
                int bit = binaryText[rounds]- '0';
                cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

                int blue_current_pixel = static_cast<int>(pixel[0]);

                if (blue_current_pixel%2 != bit ){
                    int r = randomBinary();
                    cout << blue_current_pixel << " " << bit << endl;
                    if (r==1){
                        blue_current_pixel -=1;
                    }
                    else{
                        blue_current_pixel +=1;
                    }
                }
                pixel[0] = blue_current_pixel;
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

int PM1_extract(string path) {
    
    cv::Mat image = cv::imread(path);

    if(image.empty()) {
        cout << "Невозможно загрузить изображение. Проверьте путь к файлу." << endl;
        return -1;
    }
    
    // Получаем размеры изображения
    int rows = image.rows;
    int cols = image.cols;
    string extractedText = "";
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

            if (pixel[0]%2 == 0){
                extractedText +="0";
            }
            else{
                extractedText +="1";
            }
        }
    }
    string text = convertExtractText(extractedText);
    cout << text <<endl;
    return 0;
}


int main() {

    PM1_embed("steg1.png", "my text");
    PM1_extract("new_image.png");

    return 0;
}


