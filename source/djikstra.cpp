#include "djikstra.hpp"

#include <algorithm>

/**
 * Implementation of Djikstra
 */

Djikstra::Djikstra(Graph const& graph)
{
  graph_ = graph;
}

std::shared_ptr<GraphNode> Djikstra::source() const {
  return source_;
}

void Djikstra::djikstra(std::shared_ptr<GraphNode> source)
{
  source_ = source;

  graph_.reset();
  source->distance(0);

  while(graph_.front() != nullptr) {
    graph_.sort();
    auto parent = graph_.front();

    if(parent->distance() < std::numeric_limits<unsigned int>::max()) {
      for(auto p : parent->adjacentNodes()) {
        unsigned int distance = parent->distance() + p.second;
        if(p.first->parent() == nullptr || distance < p.first->distance()) {
          p.first->parent(parent);
          p.first->distance(distance);
        }
      }
    }

    graph_.pop_front();
  }
}

std::vector<std::shared_ptr<GraphNode>> Djikstra::path(std::shared_ptr<GraphNode> const& target) const
{
  std::vector<std::shared_ptr<GraphNode>> shortestPath;
  if(target->distance() == std::numeric_limits<unsigned int>::max()) {
    return shortestPath;
  }

  std::shared_ptr<GraphNode> curr = target;
  do {
    shortestPath.insert(std::begin(shortestPath), curr);
    curr = curr->parent();
  } while(curr != source_);
  shortestPath.insert(std::begin(shortestPath), source_);
  return shortestPath;
}