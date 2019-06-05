#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <vector>
#include <memory>

#include "graph.hpp"
#include "djikstra.hpp"
#include "bubblesort.hpp"

TEST_CASE("bubblesort", "[sort]")
{
  std::vector<int> v{0, -4, 3, 5, -6};
  bubblesort(std::begin(v), std::end(v));
  REQUIRE(std::is_sorted(std::cbegin(v), std::cend(v)));
}

TEST_CASE("bubblesort with comparison function", "[sort]")
{
  std::vector<int> v{0, -4, 3, 5, -6};
  bubblesort(std::begin(v), std::end(v), [](int l, int r) {
    return l < r;
  });
  REQUIRE(std::is_sorted(std::cbegin(v), std::cend(v)));
}

TEST_CASE("djikstra", "[graph]")
{
  Graph graph;

  auto a = graph.add("Node A");
  auto b = graph.add("Node B");

  a->connect(b, 5);

  Djikstra djikstra{graph};
  djikstra.djikstra(a);
  auto path = djikstra.path(b);

  REQUIRE(path.size() == 2);
  REQUIRE(path.front() == a);
  REQUIRE(path.back() == b);
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
