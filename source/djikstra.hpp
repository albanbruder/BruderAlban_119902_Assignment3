#ifndef BUW_DJIKSTRA_HPP
#define BUW_DJIKSTRA_HPP

#include "graph.hpp"

class Djikstra {

public:
  /**
   * Constructor
   */
  Djikstra(Graph const& graph);

  /**
   * Returns source node or nullptr if source not set.
   */
  std::shared_ptr<GraphNode> source() const;
  
  /**
   * Runs the Djikstra algorithm on the given source.
   */
  void djikstra(std::shared_ptr<GraphNode> src);

  /**
   * Returns shortest path to a given target or a vector of length 0 if target can't be reached.
   */
  std::vector<std::shared_ptr<GraphNode>> path(std::shared_ptr<GraphNode> const& target) const;

private:
  /* data */
  Graph graph_;
  std::shared_ptr<GraphNode> source_ = nullptr;
};

#endif