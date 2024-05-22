#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "utils.h"
using namespace std;

int PM1(string path, string text) {
    vector<char> binaryText = convertText(text);
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
            char bit = binaryText[rounds];
            // Получаем текущий пиксель
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
            // cout << << endl;
            // Изменяем пиксель (например, инвертируем цвета)
            // binaryToDecimal

            string binaryPixel = toBinary(static_cast<int>(pixel[0]));
            binaryPixel[-1] = bit;
            pixel[0] = binaryToDecimal(binaryPixel); // Синий

            // Сохраняем изменения в изображении
            image.at<cv::Vec3b>(y, x) = pixel;
            rounds +=1;
        }
    }
    // Сохраняем измененное изображение
    cv::imwrite("new_image.png", image);
    return 0;
}


int main() {
    PM1("steg1.png", "my text");
    // vector<string> data = convertText("abcdef my name сергей");
    // for (int i = 0; i<data.size(); i++) {
    //     cout << data[i] << endl;
    // }
    return 0;
}
