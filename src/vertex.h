#pragma once

struct vertex {

    explicit vertex(int id): _id(id) {};
    explicit vertex(int id, int distance): _id(id), _distance(distance) {};

    int _id;
    int _distance = 1;

    friend bool operator<(const vertex& lhs, const vertex& rhs){
        return lhs._id < rhs._id;
    }

};