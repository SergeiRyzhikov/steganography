#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "utils.h"

using namespace std;

/**
 * @file QIM.cpp
 * @brief Embeding and extracting using QIM method.
 * 
 */

/**
 * @brief Embeds text into an image using the Quantization Index Modulation (QIM) method.
 * 
 * This function takes an image path, text to embed, and an output image name.
 * It converts the text to binary and embeds it into the blue channel of the image pixels
 * using quantization with a specified quantization step.
 * 
 * Формула встраивания:
 * \f[
 * P_i' = q \cdot \left\lfloor \frac{P_i}{q} \right\rfloor + \frac{q}{2} \cdot m_i,
 * \f]
 * 
 * Формула извлечения:
 * \f[
 * m_i = \arg \min_{e \in \{0,1\}} \left| P_i' - P_{i,e}'' \right|,
 * \f]
 *
 * @param imagePath Path to the input image file.
 * @param text Text to embed into the image.
 * @param imageName Name of the output image file with embedded text.
 * @return int Returns 0 on success, -1 if the image cannot be loaded.
 */
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
    cout << "\nВставка текста произошла успешно. Стегоизображение: " << imageName <<endl;
    return 0;
}

/**
 * @brief Extracts embedded text from an image using the Quantization Index Modulation (QIM) method.
 * 
 * This function takes the path to an image file with embedded text. It reads the blue channel
 * of the image pixels and extracts the embedded binary data using quantization with a specified quantization step.
 * 
 * @param path Path to the image file with embedded text.
 * @return int Returns 0 on success, -1 if the image cannot be loaded.
 */
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
    cout << "Извелеченный текст: " << text <<endl;
    return 0;
}