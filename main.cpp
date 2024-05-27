#include <iostream>
#include <string>
#include "LSB.h"
#include "PM1.h"
#include "QIM.h"
#include <limits>
using namespace std;

/**
 * @brief Converts a binary string representing text back to its original text form.
 * 
 */
int main() {
    string method, choice, path, name, text;
    cout << "Выберите стегонаграфический метод (PM1, QIM, LSB): " << endl;
    cin >> method;
    cout << "" << endl;

    cout << "Выберите встраивание или извлечение: " << endl;
    cin >> choice;
    cout << "" << endl;

    if (choice == "извлечение"){
        cout << "Введите путь до изображения: " << endl;
        cin >> path;
        cout << "" << endl;

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
            cout << "Метод введен неверно :(" << endl;
        }
    }

    else if (choice == "встраивание"){
        cout << "Введите путь до изображения: " << endl;
        cin  >> path;
        cout << "" << endl;

        cout << "Введите название стегоизображения: " << endl;
        cin >> name;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "" << endl;

        cout << "Введите текст: " << endl;
        getline(cin, text);
        cout << "" << endl;

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
            cout << "Метод введен неверно :(" << endl;
        }
    }

    else {
        cout << "Некорректно введенные данные :(" << endl;
    }

    return 0;
}