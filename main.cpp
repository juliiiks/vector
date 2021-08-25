#include <iostream>
#include "vector.h"
#include <vector>

int main() {
    auto vec1 = Vector<int>(10);

    auto vec2 = Vector<int>({ 1, 2, 3 });

    vec1 = Vector<int>(vec2);

    vec1.shrink_to_fit();

    std::cout << "Print:\n";
    vec1.print();

    std::cout << "\nLength: " << vec1.get_length() << std::endl;

    vec1.set_elem(0, 123);
    
    std::cout << "\nFirst element: " << vec1.get_elem(0) << std::endl;

    int* new_array = vec1.to_array();

    std::cout << "\nAll elements (iterator): \n";
    for (auto& element : vec1)
        std::cout << element << std::endl;

    vec1 = vec2;

    vec1 += vec2;
    vec1 -= vec2;

    vec1 *= 2;
    vec1 /= 2;

    std::cout << "\nVector1: \n" << vec1 << std::endl;

    auto temp1 = vec1 + vec2;
    auto temp2 = vec1 - vec2;

    auto temp3 = vec1 * 2;
    auto temp4 = vec1 / 2;

    return 0;
}