#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "utils.h"

using namespace std;


int LSB_extract(string path) {

    cv::Mat image = cv::imread(path);
    if(image.empty()) {
        cout << "Невозможно загрузить изображение. Проверьте путь к файлу." << endl;
        return -1;
    }
    // Получаем размеры изображения
    int rows = image.rows;
    int cols = image.cols;
    int rounds = 0;
    string extractedText = "";
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            // Получаем текущий пиксель
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

            string binaryPixel = toBinary(static_cast<int>(pixel[0]));

            char lastBit = binaryPixel[binaryPixel.length()-1];

            extractedText += lastBit;
        }
    }
    string text = convertExtractText(extractedText);

    cout << text <<endl;
    return 0;
}

int LSB_embed(string imagePath, string text, string imageName) {
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
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (rounds < binaryText.length()) {
                char bit = binaryText[rounds];
                cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

                string binaryPixel = toBinary(static_cast<int>(pixel[0]));
                binaryPixel[binaryPixel.length()-1] = bit;
                pixel[0] = binaryToDecimal(binaryPixel); 
                
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