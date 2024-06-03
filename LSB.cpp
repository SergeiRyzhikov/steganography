#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "utils.h"

using namespace std;

/**
 * @file LSB.cpp
 * @brief Embeding and extracting using LSB method.
 *
 */

/**
 * @brief Extracts embedded text from an image using the Least Significant Bit (LSB) method.
 *
 * This function takes the path to an image file with embedded text. It reads the least significant
 * bit (LSB) of the blue channel of each pixel and converts the extracted binary data back to text.
 *
 * @param path Path to the image file with embedded text.
 * @return int Returns 0 on success, -1 if the image cannot be loaded.
 */
int LSB_extract(string path)
{

    cv::Mat image = cv::imread(path);
    if (image.empty())
    {
        cout << "Невозможно загрузить изображение. Проверьте путь к файлу." << endl;
        return -1;
    }
    int rows = image.rows;
    int cols = image.cols;
    int rounds = 0;
    string extractedText = "";
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

            string binaryPixel = toBinary(static_cast<int>(pixel[0]));

            char lastBit = binaryPixel[binaryPixel.length() - 1];

            extractedText += lastBit;
        }
    }
    string text = convertExtractText(extractedText);

    cout << "Извелеченный текст: " << text << endl;
    return 0;
}

/**
 * @brief Embeds text into an image using the Least Significant Bit (LSB) method.
 *
 * This function takes an image path, text to embed, and an output image name.
 * It converts the text to binary and embeds it into the least significant bit (LSB)
 * of the blue channel of the image pixels.
 *
 * Формула встраивания:
 * \f[
 * P_i = p_7p_6p_5p_4p_3p_2p_1p_0, \quad
 * P_i' = p_7p_6p_5p_4p_3p_2p_1m_i
 * \f]
 *
 * @param imagePath Path to the input image file.
 * @param text Text to embed into the image.
 * @param imageName Name of the output image file with embedded text.
 * @return int Returns 0 on success, -1 if the image cannot be loaded.
 */
int LSB_embed(string imagePath, string text, string imageName)
{
    
    string binaryText = convertText(text);


    cv::Mat image = cv::imread(imagePath);

    if (image.empty())
    {
        cout << "Невозможно загрузить изображение. Проверьте путь к файлу." << endl;
        return -1;
    }
    int rows = image.rows;
    int cols = image.cols;
    int rounds = 0;
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            if (rounds < binaryText.length())
            {
                char bit = binaryText[rounds];
                cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

                string binaryPixel = toBinary(static_cast<int>(pixel[0]));
                binaryPixel[binaryPixel.length() - 1] = bit;
                pixel[0] = binaryToDecimal(binaryPixel);

                image.at<cv::Vec3b>(y, x) = pixel;
            }
            else
            {
                break;
            }
            rounds += 1;
        }
    }
    cv::imwrite(imageName, image);
    cout << "\nВставка текста произошла успешно. Стегоизображение: " << imageName << endl;
    return 0;
}