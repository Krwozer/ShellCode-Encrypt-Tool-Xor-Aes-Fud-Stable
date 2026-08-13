#include <iostream>
#include <fstream>

void encrypt(unsigned char* data, size_t size, unsigned char* key, size_t key_size) {
    size_t key_index = 0;
    for (size_t i = 0; i < size; ++i) {
        data[i] = (data[i] + key[key_index]) % 256;
        key_index = (key_index + 1) % key_size;
    }
}

unsigned char mass[8] = { 0x3C , 0x18, 0x70, 0x18, 0x1C, 0x20, 0x24, 0x88 };

int main() {
    // Путь к файлу для чтения
    std::string input_filename = ".xxx";

    // Путь к файлу для записи
    std::string output_filename = "output.bin";

    // Открываем файл для чтения в бинарном режиме
    std::ifstream input_file(input_filename, std::ios::binary | std::ios::ate);
    if (!input_file) {
        std::cerr << "Cannot open the file for reading: " << input_filename << std::endl;
        return 1;
    }

    // Определяем размер файла
    std::streamsize size = input_file.tellg();
    input_file.seekg(0, std::ios::beg);

    // Выделяем память для массива
    unsigned char* buffer = new unsigned char[size];

    // Читаем данные из файла
    if (!input_file.read(reinterpret_cast<char*>(buffer), size)) {
        std::cerr << "Error reading the file." << std::endl;
        delete[] buffer;
        input_file.close();
        return 1;
    }

    // Закрываем файл после чтения
    input_file.close();

    // Открываем файл для записи в бинарном режиме
    std::ofstream output_file(output_filename, std::ios::binary);
    if (!output_file) {
        std::cerr << "Cannot open the file for writing: " << output_filename << std::endl;
        delete[] buffer;
        return 1;
    }
    encrypt(buffer, size, mass, 8);
    // Пишем данные в файл
    output_file.write(reinterpret_cast<char*>(buffer), size);
    if (!output_file.good()) {
        std::cerr << "Error writing to the file." << std::endl;
    }
    else {
        std::cout << "Data has been successfully written to the file." << std::endl;
    }

    // Освобождаем память и закрываем файлы
    delete[] buffer;
    output_file.close();

    return 0;
}