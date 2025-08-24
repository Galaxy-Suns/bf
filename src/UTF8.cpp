#include "UTF8.h"
#include <string>
#include <cstdint>

#define LEN1CODE 0x80
#define LEN2CODE 0xE0
#define LEN3CODE 0xF0
#define LEN4CODE 0xF8
#define LEN1RES  0x00
#define LEN2RES  0xC0
#define LEN3RES  0xE0
#define LEN4RES  0xF0

int utf_size(char first) {
    if ((first & LEN1CODE) == LEN1RES) return 1;
    if ((first & LEN2CODE) == LEN2RES) return 2;
    if ((first & LEN3CODE) == LEN3RES) return 3;
    if ((first & LEN4CODE) == LEN4RES) return 4;
    return 0;
}

void string_to_buffer(const std::string &utf8_s, uint8_t buffer[]) {
    if (utf8_s.size() == 0) {
        buffer[0] = 0;
        return;
    }
    int size = utf_size(utf8_s[0]);
    for (int i = 0; i < size; i++) {
        buffer[i] = utf8_s[i];
    }
}

std::string buffer_to_string(const uint8_t buffer[]) {
    std::string s;
    int size = utf_size(buffer[0]);
    for (int i = 0; i < size; i++) {
        s.push_back(buffer[i]);
    }
    return s;
}

#ifdef UTF8_TEST
#include <iostream>

int main() {
    std::string s;
    std::cout << "Input a utf-8 string" << std::endl;
    std::cin >> s;
    uint8_t buffer[100];
    string_to_buffer(s, buffer);
    std::string first = buffer_to_string(buffer);
    std::cout << "first uft-8 character is " << first << std::endl;
    return 0;
}

#endif
