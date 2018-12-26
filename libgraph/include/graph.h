#pragma once

#include <vector>
#include <set>
#include <map>

class vertex
{
public:
    vertex( uint32_t vertex_count, uint32_t distance ) : vertex_id_( vertex_count ), distance_( distance ) {}

    bool operator<( const vertex & right ) const { return vertex_id_ < right.vertex_id_; }
    bool operator>( const vertex & right ) const { return vertex_id_ > right.vertex_id_; }
    bool operator==( const vertex & right ) const { return vertex_id_ == right.vertex_id_; }

public:
    vertex() = delete;
    ~vertex() = default;

public:
    uint32_t const vertex_id_;
    uint32_t const distance_;
};

std::ostream & operator<<( std::ostream & os, const std::set< vertex > & adj_vertices )
{
    for ( auto const & some_vertex : adj_vertices )
        os << "[V_NAME: " << some_vertex.vertex_id_ << ", DISTANCE: " << some_vertex.distance_ << "] ";

    return os;
}

class graph
{
public:
    void read_from_file(std::string const & input_file_path, std::string const & delimiter = " ");
    void read_from_console();

    void add_node();
    void add_edge( uint32_t departure, uint32_t destination, uint32_t distance );
    void add_direct_edge( uint32_t departure, uint32_t destination, uint32_t distance );

    void remove_edge(uint32_t departure, uint32_t destination);

    bool is_edge( uint32_t departure, uint32_t destination ) const;

    void print_to_console() const;
    void write_matrix_to_file(std::string const &output_dir = ".") const;

    std::vector< uint32_t > get_euler_path() const;

public:
    explicit graph() = default;
    ~graph() = default;

private:
    void deep_first_search( std::vector< bool > & visited, uint32_t current ) const;
    bool is_euler() const;

private:
    uint32_t node_counter_ = 0;
    std::map< uint32_t, std::set< vertex > > graph_;
};
