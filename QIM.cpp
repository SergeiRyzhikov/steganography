#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "utils.h"

using namespace std;

int QIM_embed(string imagePath, string text, string imageName) {
    string binaryText = convertText(text);
    
    cv::Mat image = cv::imread(imagePath);

    if(image.empty()) {
        cout << "Невозможно загрузить изображение. Проверьте путь к файлу." << endl;
        return -1;
    }
    // Получаем размеры изображения
    int rows = image.rows;
    int cols = image.cols;
    int rounds = 0;
    int q = 4;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (rounds < binaryText.length()) {
                int bit = binaryText[rounds] - '0';
                cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

                int blue_current_pixel = static_cast<int>(pixel[0]);

                blue_current_pixel = q*floor(blue_current_pixel/q)+(q/2)*bit;

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
    cv::imwrite(imageName, image);
    return 0;
}

int QIM_extract(string path) {
    
    cv::Mat image = cv::imread(path);

    if(image.empty()) {
        cout << "Невозможно загрузить изображение. Проверьте путь к файлу." << endl;
        return -1;
    }
    
    // Получаем размеры изображения
    int rows = image.rows;
    int cols = image.cols;
    string extractedText = "";
    int q = 4;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

            int blue_current_pixel = static_cast<int>(pixel[0]);

            int vstr1 = q*floor(blue_current_pixel/q) + q/2;

            int vstr0 = q*floor(blue_current_pixel/q);

            if (abs(blue_current_pixel -vstr1) > abs(blue_current_pixel -vstr0)){
                extractedText += '0';
            }else{
                extractedText += '1';
            }
        }
    }
    string text = convertExtractText(extractedText);
    cout << text <<endl;
    return 0;
}