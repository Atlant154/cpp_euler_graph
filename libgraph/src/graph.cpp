#include <iostream>
#include <fstream>
#include <stack>

#include "../include/graph.h"

void graph::read_from_file(std::string const &input_file_path, std::string const &delimiter)
{
    node_counter_ = 0;
    graph_.clear();

    std::ifstream input_file;
    input_file.open(input_file_path);
    if (!input_file.is_open())
        return;

    int node_number;
    std::string buffer;
    size_t position = 0;

    while (!std::getline(input_file, buffer).eof()) {
        node_number = 1;
        add_node();
        while (std::string::npos != (position = buffer.find(delimiter))) {
            if (std::stoi(buffer.substr(0, position)))
                graph_[node_counter_].emplace(node_number);

            buffer.erase(0, position + delimiter.length());
            ++node_number;
        }
        if (std::stoi(buffer))
            graph_[node_counter_].emplace(node_number);
    }
    input_file.close();
}

void graph::read_from_console()
{
    node_counter_ = 0;
    graph_.clear();

    int size;
    std::cout << "Enter graph size: ";
    std::cin >> size;

    for(int iter = 0; iter < size; ++iter)
    {
        add_node();
        std::cout << "Node num: " << node_counter_ << "." << std::endl;
        for(int adjacent_iter = 0; adjacent_iter < size; ++adjacent_iter)
        {
            int buffer;
            std::cin >> buffer;
            if(buffer > 0)
                add_edge(node_counter_, adjacent_iter + 1);
        }
    }
}

void graph::write_matrix_to_file(std::string const &output_dir) const
{
    std::fstream output_file;
    std::string const filename = "/adjacent_matrix.txt";
    output_file.open(output_dir + filename, std::ios::out | std::ios::trunc);

    for (int node_iter = 1; node_iter <= (int)graph_.size(); ++node_iter) {
        for (int adjacement_iter = 1; adjacement_iter <= (int)graph_.size(); ++adjacement_iter) {
            if (graph_.at(node_iter).find(adjacement_iter) == graph_.at(node_iter).end())
                output_file << "0 ";
            else
                output_file << "1 ";
        }
        output_file << std::endl;
    }

    output_file.close();
}

void graph::print_to_console() const
{
    for (const auto &node : graph_) {
        std::cout << "Node: " << node.first << ". Adjacent nodes: ";
        for (const auto &adj_node : node.second) {
            std::cout << adj_node << " ";
        }
        std::cout << std::endl;
    }
}

void graph::add_node()
{
    ++node_counter_;
    graph_.try_emplace(node_counter_, std::set<int>());
}

void graph::add_edge(int departure, int destination)
{
    std::cout << "Dep: " << departure << ". Dest: " << destination << "." << std::endl;
    graph_[departure].emplace(destination);
    graph_[destination].emplace(departure);
}

void graph::remove_edge(int departure, int destination)
{
    graph_[departure].erase(destination);
    graph_[destination].erase(departure);
}

bool graph::is_edge(int departure, int destination) const
{
    return !(graph_.at(departure).find(destination) == graph_.at(departure).end());
}

void graph::deep_first_search(std::vector<bool> &visited, int current) const
{
    if(visited.at(current) == true)
        return;

    visited.at(current) = true;
    for (auto const & node : graph_) {
        if(visited.at(node.first) == false && !node.second.empty())
            deep_first_search(visited, node.first);
    }
}

bool graph::is_euler() const
{
    std::vector<bool> visited(graph_.size() + 1, false);
    size_t special_nodes_counter = 0;

    for (auto const & node : graph_)
        if(node.second.size() % 2 == 1)
            ++special_nodes_counter;
    if (special_nodes_counter > 2)
        return false;


    for (auto const & node : graph_)
        if (node.second.size() > 0) {
            deep_first_search(visited, node.first);
            break;
        }

    for (auto const & node : graph_) {
        if( node.second.size() > 0 && visited.at(node.first) == false )
            return false;
    }

    return true;
}

std::vector<int> graph::get_euler_path() const
{
    std::vector<int> result;

    if (!is_euler()) {
        std::cout << "No Euler path!" << std::endl;
        return result;
    }

    auto tested_graph = graph_;
    std::stack<int> stack;

    for (const auto &node : tested_graph) {
        if (node.second.size() % 2 == 1) {
            stack.emplace(node.first);
            break;
        }
    }

    if (stack.empty())
        stack.emplace(1);

    while (!stack.empty()) {
        auto w = stack.top();
        for (auto const & node : tested_graph) {
            if (node.second.find(w) != node.second.end()) {
                stack.push(node.first);
                tested_graph.at(node.first).erase(w);
                tested_graph.at(w).erase(node.first);
                break;
            }
        }
        if (w == stack.top())
            stack.pop();
        if (stack.size() == graph_.size() + 1)
            while (!stack.empty()) {
                result.emplace_back(stack.top());
                stack.pop();
            }
    }

    return result;
}