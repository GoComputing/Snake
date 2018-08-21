#include <tools.hpp>
#include <cassert>
#include <fstream>

size_t fileSize(std::istream &is) {
    size_t file_size;
    is.seekg(0, std::ios_base::end);
    file_size = is.tellg();
    is.seekg(0, std::ios_base::beg);
    return file_size;
}

std::string loadBinaryFile(const std::string &path) {
    std::ifstream file = std::ifstream(path);
    size_t file_size;
    char *file_data;
    std::string res;
    if(!file.is_open())
        throw std::runtime_error ("Error openning file at " + path + "'");
    file_size = fileSize(file);
    file_data = new char[file_size];
    file.read(file_data, file_size);
    file.close();
    res = std::move(std::string(file_data, file_size));
    delete[] file_data;
    return res;
}
