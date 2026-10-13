#include <iostream>

void resize(int*& arr, int oldCap, int newCap) {
    int* jar{ new int[newCap]{} };
    if (oldCap < newCap) {
        std::cout << "Jar full! Growing from " << oldCap << " to " << newCap << ".\n";
    } else {
        std::cout << "Shrinking jar from " << oldCap << " to " << newCap << ".\n";
    }
    for (int i = 0; i < oldCap && i < newCap; ++i) {
        jar[i] = arr[i];
    }
    delete[] arr;
    arr = jar;
}
int main() {
    int capacity = 2;
    int size{};
    int resizes{};
    int* jar = new int[capacity];

    int x{};
    while (1) {
        std::cout << "Drop a number in the jar (-1 to stop): ";
        std::cin >> x;
        if (x == -1) {
            std::cout << "\n";
            break;
        }
        if (size == capacity) {
            resize(jar, capacity, capacity * 2);
            capacity *= 2;
            resizes++;
        }
        jar[size] = x;
        ++size;
    }

    // When input ends, shrink the jar to fit so its capacity equals the number of stored integers.
    resize(jar, capacity, size);
    resizes++;
    capacity = size;

    int newSize = 0;

    for (int i = 0; i < size; ++i) {
        bool duplicate = false;
        for (int j = 0; j < newSize; ++j) {
            if (jar[i] == jar[j]) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {
            jar[newSize] = jar[i];
            newSize++;
        }
    }
    std::cout << "Removing duplicates...\n";

    size = newSize;
    resize(jar, capacity, size);
    resizes++;
    capacity = size;


    std::cout << "\nFinal jar: ";
    for (int i = 0; i < newSize; ++i) {
        std::cout << jar[i] << " ";
    }
    std::cout << "\n";
    std::cout << "Size: " << size << "\n";
    std::cout << "Capacity: " << capacity << "\n";
    std::cout << "Times resized: " << resizes;

    delete[] jar;
    jar = nullptr;

    return 0;
}
