#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous.assign(numVertices, UNDEFINED);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;    // pair<weight,vertex>
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        int u = extractVertexWithMinWeight(minHeap);
        if (visited[u]) continue;
        visited[u] = true;
        for (Edge edge : G[u]) {
            int v = edge.dst;
            int newDistance = distances[u] + edge.weight;
            if (!visited[v] && newDistance < distances[v]) {
                distances[v] = newDistance;
                previous[v] = u;
                minHeap.push({newDistance, v});
            }
        }
    }

    return distances;
}

int extractVertexWithMinWeight(priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>& minHeap) {
    int vertex = minHeap.top().second;
    minHeap.pop();
    return vertex;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    int numVertices = previous.size();
    vector<int> path(numVertices, UNDEFINED);
    int vertex = destination;
    while (int i=numVertices-1; previous[vertex] != UNDEFINED && i>=0; --i) {
        path[i] = vertex;
        vertex = previous[vertex];
    }
    return path;
}

void print_path(const vector<int>& v, int total) {
    for (int vertex : v)
        cout << vertex << " ";
    cout << endl;
    cout << "Total cost is " << total << endl;
}