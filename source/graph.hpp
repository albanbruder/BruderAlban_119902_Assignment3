#ifndef BUW_GRAPH_HPP
#define BUW_GRAPH_HPP

#include <limits>
#include <vector>
#include <map>
#include <memory>
#include <list> 

class GraphNode;

class Graph {
private:
  /* data */
  std::vector<std::shared_ptr<GraphNode>> nodes_;
  std::vector<std::shared_ptr<GraphNode>> minPriorityQueue_;

public:
  /**
   * Add a node.
   */
  void add(std::shared_ptr<GraphNode> const& node);

  /**
   * Add a node with given label.
   */
  std::shared_ptr<GraphNode> add(std::string const& node);

  /**
   * Remove a node.
   */
  void remove(std::shared_ptr<GraphNode> const& node);

  /**
   * Sorts the min-priority Queue.
   */
  void sort();

  /**
   * Returns first element in minPriorityQueue_ or nullptr if queue is empty.
   */
  std::shared_ptr<GraphNode> front() const;

  /**
   * Removes first element in minPriorityQueue_.
   */
  void pop_front();

  /**
   * Get all nodes.
   */
  std::vector<std::shared_ptr<GraphNode>> nodes() const;

  /**
   * Resets weights, parents and minPriorityQueue_.
   */
  void reset();
};

class GraphNode {
private:
  /* data */
  std::string label_;
  std::map<std::shared_ptr<GraphNode>, unsigned int> adjacentNodes_;
  std::shared_ptr<GraphNode> parent_ = nullptr;
  unsigned int distance_ = std::numeric_limits<unsigned int>::max();

public:
  /**
   * Constructor with label
   */
  GraphNode(std::string const& label);

  /**
   * Set the label.
   */
  void label(std::string const& label);

  /**
   * Get the label.
   */
  std::string label() const;

  /**
   * Set the parent.
   */
  void parent(std::shared_ptr<GraphNode> const& parent);

  /**
   * Get the parent.
   */
  std::shared_ptr<GraphNode> parent() const;

  /**
   * Set the distance.
   */
  void distance(unsigned int distance);

  /**
   * Get the distance.
   */
  unsigned int distance() const;

  /**
   * Add a connection.
   */
  void connect(std::shared_ptr<GraphNode> const& node, int distance);

  /**
   * Remove a connection
   */
  void disconnect(std::shared_ptr<GraphNode> const& node);

  /**
   * Get all adjacent nodes.
   */
  std::map<std::shared_ptr<GraphNode>, unsigned int> adjacentNodes() const;
};

#endif