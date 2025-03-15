#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(DijkstrasTest, SmallGraph) {
  Graph graph;
  vector<int> previous;
  file_to_graph("src/small.txt", graph);
  vector<int> distances = dijkstra_shortest_path(graph, 0, previous);

  int dest = 2;
  int distance = distances[dest];
  vector<int> path = extract_shortest_path(distances, previous, dest);
  vector<int> expected = {0, 3, 1, 2};
  EXPECT_EQ(path, expected) << "Error: path from vertex 0 to vertex 2 is incorrect";
}
