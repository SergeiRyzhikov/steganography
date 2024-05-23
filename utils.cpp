#include <string>
#include <vector>
using namespace std;

string addZeros(string s) {
    if (s.length()<8) {
        s.insert(0, 8-s.length(), '0');
    }
    return s;
}

string toBinary(int decimal) {
    string binary = ""; 

    while (decimal > 0) {
        int remainder = decimal % 2;
        binary = to_string(remainder) + binary;
        decimal /= 2;
    }
    return binary;
}

string convertText(string text){
    string data;
    for (int i = 0; i < text.length(); ++i) {

        if (int(text[i]) > 0 && int(text[i]) <256){
            string binary = addZeros(toBinary(int(text[i])));
            for (int j = 0; j < binary.length(); ++j) {
                data += binary[j];
            }
        }
    }
    return data;
}

int binaryToDecimal(const std::string& binary) {
    int decimal = 0;
    int power = 1; // Степень двойки, которая будет умножаться на каждый бит

    // Проходим по строке двоичного числа справа налево
    for (int i = binary.size() - 1; i >= 0; --i) {
        // Если текущий символ '1', то прибавляем к десятичному числу значение степени двойки
        if (binary[i] == '1') {
            decimal += power;
        }
        // Увеличиваем степень двойки
        power *= 2;
    }

    return decimal;
}

string convertExtractText(string extractedText){
    string text;
    for (int i = 0; i<extractedText.length(); i+=8){
        int code = binaryToDecimal(extractedText.substr(i, 8));

        if (code >31 && code < 127){
            text += char(code);
        }
    }
    return text;
}