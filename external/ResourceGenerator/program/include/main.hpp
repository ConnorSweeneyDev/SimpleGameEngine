#pragma once

#include <filesystem>
#include <string>
#include <vector>

struct Resource
{
  std::filesystem::path path = "";
  std::string name = "";
  std::string extension = "";
  std::vector<unsigned char> binary = {};
  int width = 0;
  int height = 0;
  int channels = 0;
};

struct Configuration
{
  std::vector<Resource> resources = {};
  std::filesystem::path path = {};
  std::string name = "";
  std::string extension = "";
  std::string text_postfix = "";
  std::string image_postfix = "";
};

int main(int argc, char *argv[]);
std::string unsigned_char_to_hex(unsigned char character);
