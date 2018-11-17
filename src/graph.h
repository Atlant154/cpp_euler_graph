#pragma once

#include "vertex.h"
#include <string>
#include <set>
#include <map>

class graph {
public:

    graph() = default;

    void add_node();

    void add_edge(int departure, int destination);
    void add_edge(int departure, int destination, int distance);

    void write_to_console();

private:
    std::map<int, std::set<vertex>> _nodes;
    int node_counter = 1;
};