#include "src/cm_graph.h"

#include <iostream>

int main() {
    cm_graph testy;

    for(auto iter = 0; iter < 5; ++iter)
        testy.add_node();

    testy.add_edge(1, 2);
    testy.add_edge(1, 3);
    testy.add_edge(4, 1);
    testy.add_edge(2, 3, 15);

    testy.write_to_console();

    std::cout << testy.is_euler() << std::endl;
    return 0;
}