#include <dijkstras.h>

int main() {
    Graph graph;
    vector<int> previous;
    file_to_graph("src/small.txt", graph);
    vector<int> distances = dijkstra_shortest_path(graph, 0, previous);

    int dest = 2;
    int distance = distances[dest];
    vector<int> path = extract_shortest_path(previous, dest);
    print_path(path, distance);  // 0 3 1 2
}