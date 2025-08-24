#pragma once
#include <string>
#include <cstdint>

void string_to_buffer(const std::string &uft8_s, uint8_t buffer[]); 
std::string buffer_to_string(const uint8_t buffer[]); 
