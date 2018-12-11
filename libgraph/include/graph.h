#pragma once

#include <vector>
#include <set>
#include <map>

class graph
{
public:
    void read_from_file(std::string const &input_file_path, std::string const &delimiter = " ");
    void read_from_console();

    void add_node();
    void add_edge(int departure, int destination);

    void remove_edge(int departure, int destination);

    bool is_edge(int departure, int destination) const;

    void print_to_console() const;
    void write_matrix_to_file(std::string const &output_dir = ".") const;

    std::vector<int> get_euler_path() const;

public:
    explicit graph() = default;
    ~graph() = default;

private:
    void deep_first_search(std::vector<bool> &visited, int current) const;
    bool is_euler() const;

private:
    int node_counter_ = 0;
    std::map<int, std::set<int>> graph_;
};
