#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;


int PM1(string path, string text){
    return 0;
}


int main() {
    // Загружаем изображение
    cv::Mat image = cv::imread("steg1.png");

    // Проверяем, удалось ли загрузить изображение
    if(image.empty()) {
        cout << "Невозможно загрузить изображение. Проверьте путь к файлу." << std::endl;
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
    
    return 0;
}
