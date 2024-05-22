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
vector<string> convertText(string text){
    vector<string> data;
    for (int i = 0; i < text.length(); i++) {

        if (int(text[i]) > 0 && int(text[i]) <256){
            data.push_back(addZeros(toBinary(int(text[i]))));
        }
        
    }
    return data;
}