#ifndef CPP_EULER_GRAPH_CM_GRAPH_H
#define CPP_EULER_GRAPH_CM_GRAPH_H

#include "graph.h"

class cm_graph : public graph {
public:
    bool is_euler() const;
};


#endif
