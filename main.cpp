#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Загружаем изображение
    cv::Mat image = cv::imread("steg1.png");

    // Проверяем, удалось ли загрузить изображение
    if(image.empty()) {
        std::cout << "Невозможно загрузить изображение. Проверьте путь к файлу." << std::endl;
        return -1;
    }

    // Получаем размеры изображения
    int rows = image.rows;
    int cols = image.cols;

    // Выводим информацию о размерах изображения
    std::cout << "Размеры изображения: " << rows << "x" << cols << std::endl;

    // Получаем первый пиксель изображения
    cv::Vec3b pixel = image.at<cv::Vec3b>(0, 0);

    // Выводим значения цвета первого пикселя
    std::cout << "Значения цвета первого пикселя (BGR): ";
    std::cout << static_cast<int>(pixel[0]) << " ";
    std::cout << static_cast<int>(pixel[1]) << " ";
    std::cout << static_cast<int>(pixel[2]) << std::endl;

    return 0;
}