#include <iostream>
#include <algorithm>
#include <fstream>
#include <stack>

#include "../include/graph.h"

void graph::read_from_file(std::string const & input_file_path, std::string const & delimiter)
{
    node_counter_ = 0;
    graph_.clear();

    std::ifstream input_file;
    input_file.open(input_file_path);
    if ( !input_file.is_open() )
        return;

    uint32_t node_number;
    std::string buffer;
    size_t position = 0;

    while ( !std::getline(input_file, buffer).eof() )
    {
        node_number = 0;
        add_node();

        while ( std::string::npos != ( position = buffer.find( delimiter ) ) )
        {
            auto value = static_cast< uint32_t >( std::stoi( buffer.substr( 0, position ) ) );
            if ( value )
                graph_[node_counter_ - 1].emplace( vertex( node_number, value ) );

            buffer.erase( 0, position + delimiter.length() );
            ++node_number;
        }
        auto value = static_cast< uint32_t >( std::stoi( buffer ) );
        if ( value )
            graph_[node_counter_ - 1].emplace( vertex( node_number, value ) );
    }
    input_file.close();
}

void graph::read_from_console()
{
    node_counter_ = 0;
    graph_.clear();

    uint32_t size;
    std::cout << "Enter graph size: ";
    std::cin >> size;

    for( uint32_t iter = 0; iter < size; ++iter )
    {
        add_node();
        std::cout << "Node num: " << node_counter_ << "." << std::endl;

        for( uint32_t adjacent_iter = 0; adjacent_iter < size; ++adjacent_iter )
        {
            uint32_t buffer;
            std::cin >> buffer;
            if( buffer > 0 )
                add_edge(node_counter_, adjacent_iter, buffer );
        }
    }
}

void graph::write_matrix_to_file(std::string const &output_dir) const
{
    std::fstream output_file;
    std::string const filename = "/adjacent_matrix.txt";
    output_file.open(output_dir + filename, std::ios::out | std::ios::trunc);

    for ( const auto & vertex : graph_ )
    {
        for( uint32_t node_iter = 0; node_iter < graph_.size(); ++node_iter )
        {
            if( vertex.second.find( { node_iter, 1 } ) == vertex.second.end() )
                output_file << "0 ";
            else
                output_file << "1 ";
        }
        output_file << '\n';
    }
    output_file.close();
}

void graph::print_to_console() const
{
    for ( auto const & node : graph_)
    {
        std::cout << "Node: " << node.first << ". Adjacent nodes: ";
        std::cout << node.second << std::endl;
    }
}

void graph::add_node()
{
    graph_.try_emplace( node_counter_, std::set< vertex >() );
    ++node_counter_;
}

void graph::add_edge( uint32_t departure, uint32_t destination, uint32_t const distance = 1 )
{
    graph_[departure].emplace( destination, distance );
    graph_[destination].emplace( departure, distance );
}

void graph::add_direct_edge( uint32_t const departure, uint32_t const destination, uint32_t const distance = 1 )
{
    graph_[departure].emplace( destination, distance );
}

void graph::remove_edge( uint32_t departure, uint32_t destination )
{
    graph_.at( departure ).erase( { destination, 1 } );
    graph_.at( destination ).erase( { departure, 1 } );
}

bool graph::is_edge( uint32_t departure, uint32_t destination) const
{
    return !( graph_.at( departure ).find( {destination, 1} ) == graph_.at( destination ).end() );
}

void graph::deep_first_search( std::vector< bool > & visited, uint32_t current ) const
{
    visited.at( current ) = true;

    for( auto const & vertex : graph_.at( current ) )
        if( visited.at( vertex.vertex_id_ ) == false )
            deep_first_search( visited, vertex.vertex_id_ );
}

bool graph::is_euler() const
{
    std::vector<bool> visited( graph_.size(), false );
    size_t special_nodes_counter = 0;

    for ( auto const & node : graph_ )
        if( node.second.size() % 2 == 1 )
            ++special_nodes_counter;
    if ( special_nodes_counter > 2 )
        return false;


    for ( auto const & node : graph_ )
        if ( !node.second.empty() )
        {
            deep_first_search( visited, node.first );
            break;
        }

    for ( auto const & node : graph_ )
    {
        if( !node.second.empty() && visited.at( node.first ) == false )
            return false;
    }

    return true;
}

std::vector< uint32_t > graph::get_euler_path() const
{
    std::vector< uint32_t > result;

    if ( !is_euler() ) {
        std::cout << "No Euler path!" << std::endl;
        return result;
    }

    auto tested_graph = graph_;
    std::stack< uint32_t > stack;

    for (const auto &node : tested_graph) {
        if (node.second.size() % 2 == 1) {
            stack.emplace(node.first);
            break;
        }
    }

    if ( stack.empty() )
        stack.emplace(1);

    while ( stack.size() < graph_.size() && !stack.empty() )
    {
        auto w = stack.top();
        for (auto const & node : tested_graph) {
            if ( node.second.find( { w, 1} ) != node.second.end() )
            {
                stack.push(node.first);
                tested_graph.at( node.first ).erase( { w, 1} );
                tested_graph.at( w ).erase( { node.first, 1} );
                break;
            }
        }
        if (w == stack.top())
            stack.pop();
    }

    while ( !stack.empty() )
    {
        result.emplace_back(stack.top());
        stack.pop();
    }

    return result;
}