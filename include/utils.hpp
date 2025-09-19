#include <string>
#include <vector>
#include <fstream>
#include <sstream>

namespace aoc {

inline std::vector<std::string> read_lines(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    return lines;
}

inline std::vector<int> read_ints(const std::string& filename) {
    std::vector<int> result;
    for (auto& line : read_lines(filename)) {
        result.push_back(std::stoi(line));
    }
    return result;
}

inline std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delimiter)) tokens.push_back(item);
    return tokens;
}

inline std::string trim(const std::string& s) {
    const char* whitespace = " \t\n\r";
    size_t start = s.find_first_not_of(whitespace);
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(whitespace);
    return s.substr(start, end - start + 1);
}
} // namespace aoc
