#include "libgraph/include/graph.h"

#include <iostream>

int main() {

    std::string const simple_path = "../sample/simple_test.txt";
    std::string const euler_path = "../sample/euler_path_test.txt";
    std::string const euler_cycle = "../sample/euler_cycle_test.txt";
    std::string const non_euler = "../sample/non_euler_test.txt";

    graph graphy;

    //graphy.read_from_console();
    graphy.read_from_file(euler_cycle);

    graphy.print_to_console();

    auto result = graphy.get_euler_path();

    std::cout << "Euler path: ";
    for (auto const & node : result) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    return 0;
}