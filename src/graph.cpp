#include "graph.h"
#include <iostream>

void graph::add_node() {
    _nodes[node_counter];
    ++node_counter;
}

void graph::add_edge(int departure, int destination) {
    _nodes[departure].emplace(vertex(destination));
    _nodes[destination].emplace(vertex(departure));
}

void graph::add_edge(int departure, int destination, int distance) {
    _nodes[departure].emplace(vertex(destination, distance));
    _nodes[destination].emplace(vertex(departure, distance));
}

void graph::write_to_console() {
    for (const auto &node : _nodes) {
        std::cout << "Departure: " << node.first << ". Destination: ";
        for (const auto &item : node.second) {
            std::cout << item._id << " ";
        }
        std::cout << std::endl;
    }
}