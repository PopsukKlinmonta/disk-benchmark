#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <cstring>

// Adjust the buffer size and the total write size as per your requirement
const std::size_t BUFFER_SIZE = 1024 * 1024; // 1 MB
const std::size_t TOTAL_WRITE_SIZE = 1024 * 1024 * 100; // 100 MB

std::vector<char> generateRandomData(std::size_t size) {
    std::vector<char> data(size);
    for (std::size_t i = 0; i < size; ++i) {
        data[i] = std::rand() % 256;
    }
    return data;
}

void writeBenchmark(const std::string &filename, const std::vector<char> &data) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 0; i < TOTAL_WRITE_SIZE; i += BUFFER_SIZE) {
        ofs.write(data.data(), data.size());
    }
    ofs.close();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Write Speed: " << (TOTAL_WRITE_SIZE / (1024.0 * 1024.0)) / (duration.count() / 1000.0) << " MB/s" << std::endl;
}

void readBenchmark(const std::string &filename) {
    std::vector<char> buffer(BUFFER_SIZE);
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();
    while (ifs.read(buffer.data(), buffer.size())) {
        // just reading, do nothing
    }
    ifs.close();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Read Speed: " << (TOTAL_WRITE_SIZE / (1024.0 * 1024.0)) / (duration.count() / 1000.0) << " MB/s" << std::endl;
}

int main() {
    std::string filename = "benchmark_test.bin";
    auto data = generateRandomData(BUFFER_SIZE);
    writeBenchmark(filename, data);
    readBenchmark(filename);
    std::remove(filename.c_str());
    return 0;
}
