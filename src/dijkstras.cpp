#include <dijkstras.h>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous[source] = UNDEFINED;
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

// vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination);

int extractVertexWithMinWeight(priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>& minHeap) {
    int vertex = minHeap.top().second;
    minHeap.pop();
    return vertex;
}

void print_path(const vector<int>& v, int total) {
    for (int vertex : v)
        cout << vertex << " ";
    cout << endl;
    cout << "Total cost is " << total << endl;
}