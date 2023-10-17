#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAXN = 1005;

vector<int> adj[MAXN];
int low[MAXN], dfn[MAXN], parent[MAXN]; // low和dfn用于Tarjan算法求割边
bool visited[MAXN];
int n, m, dfs_cnt, cc_cnt;

void dfs(int u) {
    visited[u] = true;
    cc_cnt++;
    for (int v : adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            dfs(v);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                cout << u << " " << v << " is a bridge" << endl;
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void tarjan() {
    dfs_cnt = cc_cnt = 0;
    fill(visited, visited + n + 1, false);
    fill(low, low + n + 1, 0);
    fill(dfn, dfn + n + 1, 0);
    fill(parent, parent + n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
}

int bfs(int u, int removed_u, int removed_v) {
    int cnt = 0;
    fill(visited, visited + n + 1, false);
    visited[u] = true;
    for (int v : adj[u]) {
        if (v == removed_u || v == removed_v) continue;
        if (!visited[v]) {
            visited[v] = true;
            cnt++;
            queue<int> q;
            q.push(v);
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                for (int y : adj[x]) {
                    if (y == removed_u || y == removed_v) continue;
                    if (!visited[y]) {
                        visited[y] = true;
                        q.push(y);
                    }
                }
            }
        }
    }
    return cnt;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    tarjan();

    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            if (u < v) { // 避免重复枚举边
                int current_cc = bfs(u, u, v);
                if (current_cc > cc_cnt) {
                    cout << u << " " << v << " is a bridge" << endl;
                }
            }
        }
    }

    return 0;
}/*
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1005;

int parent[MAXN];
int n, m, cc_cnt;

int find(int x) {
    if (parent[x] == x) {
        return x;
    } else {
        parent[x] = find(parent[x]);
        return parent[x];
    }
}

void union_set(int x, int y) {
    parent[find(x)] = find(y);
}

void init() {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
}

int main() {
    cin >> n >> m;
    init();
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        union_set(u, v);
    }
    for (int i = 1; i <= n; i++) {
        if (parent[i] == i) {
            cc_cnt++;
        }
    }
    cout << "The number of connected components is: " << cc_cnt << endl;
    return 0;
}*/
/*
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1005;

struct Edge {
    int from, to, weight;
    Edge(int u, int v, int w) : from(u), to(v), weight(w) {}
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

vector<Edge> edges;
int parent[MAXN];
int n, m;

int find(int x) {
    if (parent[x] == x) {
        return x;
    } else {
        parent[x] = find(parent[x]);
        return parent[x];
    }
}

void union_set(int x, int y) {
    parent[find(x)] = find(y);
}

int kruskal() {
    int cnt = 0, ans = 0;
    sort(edges.begin(), edges.end());
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    for (int i = 0; i < m; i++) {
        int u = edges[i].from, v = edges[i].to, w = edges[i].weight;
        if (find(u) != find(v)) {
            union_set(u, v);
            ans += w;
            cnt++;
            if (cnt == n - 1) {
                break;
            }
        }
    }
    return ans;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }
    int ans = kruskal();
    cout << "The weight of minimum spanning tree is: " << ans << endl;
    return 0;
}*/
