#include <iostream>
#include <string>

int main() {
    std::string x;
    bool state = false;
    while (std::cin >> x) {
        if (x == "QUIT") {
            break;    
        } else if (x == "STATUS") {
            if (state) {
                std::cout << "ON\n";
            } else {
                std::cout << "OFF\n";   
            }
        } else if (x == "ON") {
            if (state) {
                std::cout << "already on\n";
            } else {
                std::cout << "turned on\n";
            }
            state = true;
            continue;
        } else if (x == "OFF") {
            if (!state) {
                std::cout << "already off\n";    
            } else {
                std::cout << "turned off\n";    
            }
            state = false;
            continue;
        }
    }
    return 0;
}