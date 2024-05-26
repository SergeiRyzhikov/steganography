// #include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
// #include <vector>
// #include <cmath>
// #include "utils.h"
#include "LSB.h"
#include "PM1.h"
#include "QIM.h"

using namespace std;


int main() {
    string method, choice, path, name, text;
    cout << "Выберите стегонаграфический метод (PM1, QIM, LSB): " << endl;
    cin >> method;
    cout << "Выберите встраивание или извлечение: " << endl;
    cin >> choice;
    if (choice == "извлечение"){
        cout << "Введите путь до изображения: " << endl;
        cin >> path;
        if (method == "QIM"){
            QIM_extract(path);
        }
        else if (method == "LSB"){
            LSB_extract(path);
        }
        else if (method == "PM1"){
            PM1_extract(path);
        }
        else {
            cout << "Метод введен неверно :(";
        }
    }
    else if (choice == "встраивание"){
        cout << "Введите путь до изображения: " << endl;
        cin >> path;
        cout << "Введите название стегоизображения: " << endl;
        cin >> name;
        cout << "Введите текст: " << endl;
        cin >> text;
        if (method == "QIM"){
            QIM_embed(path, text, name);
        }
        else if (method == "LSB"){
            LSB_embed(path, text, name);
        }
        else if (method == "PM1"){
            PM1_embed(path, text, name);
        }
        else {
            cout << "Метод введен неверно :(";
        }
    }
    else {
        cout << "Некорректно введенные данные :(";
    }

    // QIM_embed("steg1.png", "hi stegongrap", "new_image.png");
    // QIM_extract("new_image.png");

    return 0;
}


