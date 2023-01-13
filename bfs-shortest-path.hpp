#include <vector>
#include <queue>
#include <algorithm>

const int INF = 2e9;

void bfs(std::vector<int> adj[],
         int start,
         int dist[])
{
    /*
    assumed: dist[i] = INFINITY for all i
    assumed: vis[i] = false for all i
    */
    std::queue<int> q;
    q.emplace(start);
    dist[start] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
        {
            if (dist[v] == INF)
            {
                // unexplored
                dist[v] = dist[u] + 1;
                q.emplace(v);
            }
        }
    }
}