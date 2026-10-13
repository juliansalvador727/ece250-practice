#include <iostream>
#include <string>

int main() {
    std::string line = "";
    std::string echo = "ECHO";
    std::string sum = "SUM";
    std::string repeat = "REPEAT";
    std::string alias = "ALIAS";
    std::string stop = "STOP";

    std::string alias_names[8];
    std::string alias_targets[8];
    int alias_count = 0;

    while (std::getline(std::cin, line)) {
        int current_command = 0;
        std::string command = "";
        bool first_word = true;
        bool second_word = false;
        bool third_word = false;

        long long summation = 0;

        long long repeat_times = 0;
        std::string repeat_word = "";

        std::string alias_new = "";
        std::string alias_old = "";

        if (line.empty() || line[0] == '#') {
            continue;
        }
        if (line == stop) {
            break;
        }

        std::string::size_type start = 0;

        while (start < line.size()) {
            auto end = line.find(' ', start);

            if (end == std::string::npos) {
                end = line.size();
            }

            if (end > start) {
                std::string word = line.substr(start, end - start);

                if (first_word) {
                    first_word = false;
                    second_word = true;
                    command = word;

                    for (int i = alias_count - 1; i >= 0; --i) {
                        if (command == alias_names[i]) {
                            command = alias_targets[i];
                            break;
                        }
                    }

                    if (command == stop) {
                        return 0;
                    }

                    if (command == echo) {
                        current_command = 1;
                    } else if (command == sum) {
                        current_command = 2;
                    } else if (command == repeat) {
                        current_command = 3;
                    } else if (command == alias) {
                        current_command = 4;
                    } else {
                        std::cout << "unknown " << command << "\n";
                    }
                } else if (current_command == 1) {
                    std::cout << line.substr(start) << "\n";
                    break;
                } else if (current_command == 2) {
                    summation += std::stoll(word);
                } else if (current_command == 3 && second_word && !third_word) {
                    third_word = true;
                    repeat_times = std::stoll(word);
                } else if (current_command == 3 && second_word && third_word) {
                    repeat_word = word;
                } else if (current_command == 4 && second_word && !third_word) {
                    third_word = true;
                    alias_new = word;
                } else if (current_command == 4 && second_word && third_word) {
                    alias_old = word;
                }
            }

            start = end + 1;
        }

        if (current_command == 2) {
            std::cout << summation << "\n";
        } else if (current_command == 3) {
            for (int i = 0; i < repeat_times; ++i) {
                if (i > 0) {
                    std::cout << " ";
                }
                std::cout << repeat_word;
            }
            std::cout << "\n";
        } else if (current_command == 4) {
            alias_names[alias_count] = alias_new;
            alias_targets[alias_count] = alias_old;
            ++alias_count;
        }
    }

    return 0;
}