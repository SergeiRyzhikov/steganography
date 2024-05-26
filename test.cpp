#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "utils.h"
#include "LSB.h"
#include "PM1.h"
#include "QIM.h"
#include <string>

using namespace std;


TEST_CASE("testing randomBinary positive") {
    int result = randomBinary();
    REQUIRE((result == 0 || result == 1));
}

TEST_CASE("testing randomBinary negative") {
    int result = randomBinary();
    REQUIRE_FALSE((result == 10));
}

TEST_CASE("testing addZeros positive") {
    REQUIRE(addZeros("10101") == "00010101");
    REQUIRE(addZeros("10110101") == "10110101");
    REQUIRE(addZeros("") == "00000000");

}

TEST_CASE("testing addZeros negative") {
    REQUIRE(addZeros("negative_value") == "negative_value");
    REQUIRE(addZeros("000000000") == "000000000");
    REQUIRE_FALSE(addZeros("0") == "0");
    REQUIRE_FALSE(addZeros("101") == "1");
}

TEST_CASE("testing toBinary positive") {
    REQUIRE(toBinary(1) == "1");
    REQUIRE(toBinary(2) == "10");
    REQUIRE(toBinary(3) == "11");
    REQUIRE(toBinary(4) == "100");
    REQUIRE(toBinary(10) == "1010");
    REQUIRE(toBinary(255) == "11111111");
    REQUIRE(toBinary(0) == "0");
}

TEST_CASE("testing the toBinary negative") {
    CHECK_THROWS_AS(toBinary(-1), invalid_argument);
    CHECK_THROWS_AS(toBinary(-2), invalid_argument);
    CHECK_THROWS_AS(toBinary(-10), invalid_argument);
}

TEST_CASE("testing convertText positive") {
    REQUIRE(convertText("A") == "01000001"); 
    REQUIRE(convertText(" ") == "00100000"); 
    REQUIRE(convertText("AB") == "0100000101000010"); 
    REQUIRE(convertText("Hello") == "0100100001100101011011000110110001101111"); 
    REQUIRE(convertText("\x7F") == "01111111"); 
    REQUIRE(convertText("") == "");
}

TEST_CASE("testing convertText negative") {

    CHECK_THROWS_AS(convertText("русский текст"), invalid_argument);
    CHECK_THROWS_AS(convertText("english and русский"), invalid_argument);
    CHECK_THROWS_AS(convertText("😂"), invalid_argument);
    CHECK_THROWS_AS(convertText("💕"), invalid_argument);
    CHECK_THROWS_AS(convertText("🫠"), invalid_argument);
}

TEST_CASE("testing binaryToDecimal positive") {
    REQUIRE(binaryToDecimal("11111111") == 255); 
    REQUIRE(binaryToDecimal("1010") == 10); 
    REQUIRE(binaryToDecimal("100") == 4); 
    REQUIRE(binaryToDecimal("11") == 3); 
    REQUIRE(binaryToDecimal("10") == 2); 
    REQUIRE(binaryToDecimal("1") == 1); 
    REQUIRE(binaryToDecimal("0") == 0); 
}

TEST_CASE("testing binaryToDecimal negative") {
    CHECK_THROWS_AS(binaryToDecimal("A"), invalid_argument);
    CHECK_THROWS_AS(binaryToDecimal("текст"), invalid_argument);
    CHECK_THROWS_AS(binaryToDecimal("text"), invalid_argument);
    CHECK_THROWS_AS(binaryToDecimal("10101A"), invalid_argument);
    CHECK_THROWS_AS(binaryToDecimal("42"), invalid_argument);
}
TEST_CASE("testing convertExtractText positive") {
    REQUIRE(convertExtractText("01000001") == "A"); 
    REQUIRE(convertExtractText("00100000") == " ");
    REQUIRE(convertExtractText("0100000101000010") == "AB"); 
    REQUIRE(convertExtractText("0100100001100101011011000110110001101111") == "Hello"); 
    REQUIRE(convertExtractText("") == "");
}
TEST_CASE("testing convertExtractText negative") {
    REQUIRE_FALSE(convertExtractText("00000001") == "B"); 
    REQUIRE_FALSE(convertExtractText("00001111") == "AB"); 
    REQUIRE_FALSE(convertExtractText("0000111100001111") == "YY"); 
    CHECK_THROWS_AS(convertExtractText("wehbfeub"), invalid_argument); 
    CHECK_THROWS_AS(convertExtractText("230202"), invalid_argument); 
    CHECK_THROWS_AS(convertExtractText("a1a1a1"), invalid_argument); 
}

TEST_CASE("testing PM1 positive") {
    // корректные входные данные
    REQUIRE(PM1_embed("steg1.png", "A", "test_output.png") == 0);
    REQUIRE(PM1_extract("test_output.png") == 0);

    // Проверка, что файл test_output.png был создан
    ifstream f("test_output.png");
    CHECK(f.good());
    f.close();
    
    remove("test_output.png");
}

TEST_CASE("testing LSB positive") {
    // корректные входные данные
    REQUIRE(LSB_embed("steg1.png", "A", "test_output.png") == 0);
    REQUIRE(LSB_extract("test_output.png") == 0);

    // Проверка, что файл test_output.png был создан
    ifstream f("test_output.png");
    CHECK(f.good());
    f.close();
    remove("test_output.png");
}

TEST_CASE("testing QIM positive") {
    // корректные входные данные
    REQUIRE(QIM_embed("steg1.png", "A", "test_output.png") == 0);
    REQUIRE(QIM_extract("test_output.png") == 0);
    
    // Проверка, что файл test_output.png был создан
    ifstream f("test_output.png");
    CHECK(f.good());
    f.close();
    remove("test_output.png");
}

TEST_CASE("testing PM1 negative") {
    REQUIRE(PM1_embed("pathDoesntExists", "text", "name")==-1); 
    REQUIRE(PM1_extract("pathDoesntExists")==-1); 
}

TEST_CASE("testing LSB negative") {
    REQUIRE(LSB_embed("pathDoesntExists", "text", "name")==-1);
    REQUIRE(LSB_extract("pathDoesntExists")==-1);  
}
TEST_CASE("testing QIM negative") {
    REQUIRE(QIM_embed("pathDoesntExists", "text", "name")==-1); 
    REQUIRE(QIM_extract("pathDoesntExists")==-1); 
}

