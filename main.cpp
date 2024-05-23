#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "utils.h"
using namespace std;



int PM1_extract(string path) {
    string text;
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
            // cout<< lastBit <<endl;
            extractedText += lastBit;
        }
    }
    for (int i = 0; i<extractedText.length(); i+=8){
        string p = extractedText.substr(i, 8);
        int code = binaryToDecimal(p);
        if (code >31 && code < 127){
            text += char(code);
        }
    }
    cout << text <<endl;
    return 0;
}

int PM1_embed(string path, string text) {
    vector<char> binaryText = convertText(text);
    // for (int i = 0; i < binaryText.size(); ++i){
    //     cout << binaryText[i] <<endl;
    // }
    
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
            if (rounds < binaryText.size()) {
                char bit = binaryText[rounds];
                // Получаем текущий пиксель
                cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
                // cout << << endl;
                // Изменяем пиксель (например, инвертируем цвета)
                // binaryToDecimal

                string binaryPixel = toBinary(static_cast<int>(pixel[0]));
                cout << binaryPixel<< endl;
                cout << bit << endl;
                binaryPixel[binaryPixel.length()-1] = bit;
                cout << binaryPixel<< endl;
                cout << " "<<endl;
                pixel[0] = binaryToDecimal(binaryPixel); // Синий
                
                // Сохраняем изменения в изображении
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
    string p = "abcedfgh";
    cout << p[p.length()-1] <<endl;
    // PM1_embed("steg1.png", "my text");
    PM1_extract("new_image.png");
    return 0;
}
