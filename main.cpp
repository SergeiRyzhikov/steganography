#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "utils.h"
using namespace std;

vector<string> convertText(string text){
    vector<string> data;
    for (int i = 0; i < text.length(); i++) {

        if (int(text[i]) > 0 && int(text[i]) <256){
            data.push_back(addZeros(toBinary(int(text[i]))));
        }
        
    }
    return data;
}
int PM1(string path, string text){
    return 0;
}


int main() {
    // Загружаем изображение
    cv::Mat image = cv::imread("steg1.png");

    // Проверяем, удалось ли загрузить изображение
    if(image.empty()) {
        cout << "Невозможно загрузить изображение. Проверьте путь к файлу." << endl;
        return -1;
    }

    // Получаем размеры изображения
    int rows = image.rows;
    int cols = image.cols;

    // Выводим информацию о размерах изображения
    cout << "Размеры изображения: " << rows << "x" << cols << endl;

    // Проходим по всем пикселям изображения
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            // Получаем текущий пиксель
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

            // Изменяем пиксель (например, инвертируем цвета)
            pixel[0] = 255 - pixel[0]; // Синий
            pixel[1] = 255 - pixel[1]; // Зеленый
            pixel[2] = 255 - pixel[2]; // Красный

            // Сохраняем изменения в изображении
            image.at<cv::Vec3b>(y, x) = pixel;
        }
    }
    // Сохраняем измененное изображение
    cv::imwrite("new_image.png", image);

    cout << "Измененное изображение сохранено как new_image.png" << endl;

    vector<string> data = convertText("abcdef my name сергей");
    for (int i = 0; i<data.size(); i++) {
        cout << data[i] << endl;
    }
    return 0;
}
