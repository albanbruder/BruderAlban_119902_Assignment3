#include "graph.hpp"
#include "bubblesort.hpp"
#include <algorithm>

/**
 * Implementation of Graph
 */

void Graph::add(std::shared_ptr<GraphNode> const& node)
{
  nodes_.push_back(node);
}

std::shared_ptr<GraphNode> Graph::add(std::string const& label)
{
  auto ptr = std::make_shared<GraphNode>(GraphNode{ label });
  add(ptr);
  return ptr;
}

void Graph::remove(std::shared_ptr<GraphNode> const& node)
{
  nodes_.erase(
    std::remove_if(std::begin(nodes_), std::end(nodes_), [&node](std::shared_ptr<GraphNode> const& x) {
      return node->label() == x->label();
    }),
    std::end(nodes_)
  );
}

void Graph::sort()
{
  bubblesort(
    std::begin(minPriorityQueue_), 
    std::end(minPriorityQueue_), 
    [](std::shared_ptr<GraphNode> const& lhs, std::shared_ptr<GraphNode> const& rhs) { 
      return lhs->distance() < rhs->distance(); 
    }
  );
}

std::shared_ptr<GraphNode> Graph::front() const
{
  if(minPriorityQueue_.size() > 0) {
    return minPriorityQueue_.front();
  } else {
    return nullptr;
  }
}

void Graph::pop_front()
{
  minPriorityQueue_.erase(std::begin(minPriorityQueue_));
}

void Graph::reset()
{
  minPriorityQueue_.clear();

  for(auto node : nodes_) {
    node->distance(std::numeric_limits<unsigned int>::max());
    node->parent(nullptr);
    minPriorityQueue_.push_back(node);
  }
}

std::vector<std::shared_ptr<GraphNode>> Graph::nodes() const
{
  return nodes_;
}

/**
 * Implementation of GraphNode
 */

GraphNode::GraphNode(std::string const& label)
{
  label_ = label;
}

void GraphNode::label(std::string const& label)
{
  label_ = label;
}

std::string GraphNode::label() const
{
  return label_;
}

void GraphNode::parent(std::shared_ptr<GraphNode> const& parent)
{
  parent_ = parent;
}

std::shared_ptr<GraphNode> GraphNode::parent() const
{
  return parent_;
}

void GraphNode::distance(unsigned int distance)
{
  distance_ = distance;
}

unsigned int GraphNode::distance() const
{
  return distance_;
}

void GraphNode::connect(std::shared_ptr<GraphNode> const& node, int distance)
{
  adjacentNodes_.try_emplace(node, distance);
}

void GraphNode::disconnect(std::shared_ptr<GraphNode> const& node)
{
  adjacentNodes_.erase(node);
}

std::map<std::shared_ptr<GraphNode>, unsigned int> GraphNode::adjacentNodes() const
{
  return adjacentNodes_;
}