#include <iostream>
#include <string>
#include "LSB.h"
#include "PM1.h"
#include "QIM.h"
#include <limits>
using namespace std;

/**
 * @file main.cpp
 * @brief Main entry point for the steganography program.
 *
 * This file contains the main function which allows the user to choose between different
 * steganography methods (PM1, QIM, LSB) and perform embedding or extraction of text in/from images.
 */

/**
 * @brief Main function to drive the steganography program.
 *
 * This function allows the user to select a steganography method and either embed text into
 * an image or extract text from an image using the chosen method.
 *
 * The following methods are supported:
 * - **LSB (Least Significant Bit)**:
 *   \f[
 *   P_i = p_7p_6p_5p_4p_3p_2p_1p_0, \quad
 *   P_i' = p_7p_6p_5p_4p_3p_2p_1m_i
 *   \f]
 * - **PM1 (Plus-Minus One)**:
 *   \f[
 *   P_i' =
 *   \begin{cases}
 *   P_i \pm 1 \cdot r, & \text{if } P_i \mod 2 \neq m_i; \\
 *   P_i, & \text{otherwise},
 *   \end{cases}
 *   \f]
 * - **QIM (Quantization Index Modulation)**:
 *   \f[
 *   P_i' = q \cdot \left\lfloor \frac{P_i}{q} \right\rfloor + \frac{q}{2} \cdot m_i
 *   \f]
 *
 * @return int Returns 0 on successful execution.
 */
int main()
{
    string method, choice, path, name, text;
    cout << "Выберите стегонаграфический метод (PM1, QIM, LSB): " << endl;
    cin >> method;
    cout << "" << endl;
    cout << "Выберите встраивание или извлечение: " << endl;
    cin >> choice;
    cout << "" << endl;

    if (choice == "извлечение")
    {
        cout << "Введите путь до изображения: " << endl;
        cin >> path;
        cout << "" << endl;

        if (method == "QIM")
        {
            QIM_extract(path);
        }
        else if (method == "LSB")
        {
            LSB_extract(path);
        }
        else if (method == "PM1")
        {
            PM1_extract(path);
        }
        else
        {
            cout << "Метод введен неверно :(" << endl;
        }
    }

    else if (choice == "встраивание")
    {
        cout << "Введите путь до изображения: " << endl;
        cin >> path;
        cout << "" << endl;

        cout << "Введите название стегоизображения: " << endl;
        cin >> name;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "" << endl;

        cout << "Введите текст: " << endl;
        getline(cin, text);
        cout << "" << endl;

        if (method == "QIM")
        {
            QIM_embed(path, text, name);
        }
        else if (method == "LSB")
        {
            LSB_embed(path, text, name);
        }
        else if (method == "PM1")
        {
            PM1_embed(path, text, name);
        }
        else
        {
            cout << "Метод введен неверно :(" << endl;
        }
    }

    else
    {
        cout << "Некорректно введенные данные :(" << endl;
    }

    return 0;
}