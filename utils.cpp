#include <string>
using namespace std;

string toBinary(int decimal) {
    string binary = ""; 

    while (decimal > 0) {
        int remainder = decimal % 2;
        binary = to_string(remainder) + binary;
        decimal /= 2;
    }
    return binary;
}