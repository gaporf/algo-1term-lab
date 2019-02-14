#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
vector<vector<pair<int, ll> > > g;
vector<vector<ll> > dp;

void dfs(int v, int p) {
    ll sum = 0;
    for (int i = 0; i < (int) g[v].size(); i++) {
        int to = g[v][i].first;
        if (to != p) {
            dfs(to, v);
            dp[v][0] += max(dp[to][0], dp[to][1]);
            sum += max(dp[to][0], dp[to][1]);
        }
    }
    for (int i = 0; i < (int) g[v].size(); i++) {
        int to = g[v][i].first;
        ll dist = g[v][i].second;
        if (to != p) {
            dp[v][1] = max(dp[v][1], sum - max(dp[to][0], dp[to][1]) + dp[to][0] + dist);
        }
    }
}

int main() {
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin >> n;
    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int from, to;
        ll dist;
        cin >> from >> to >> dist;
        from--;
        to--;
        g[from].push_back(make_pair(to, dist));
        g[to].push_back(make_pair(from, dist));
    }
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(2, 0);
    }
    dfs(0, -1);
    cout << max(dp[0][0], dp[0][1]) << endl;
    return 0;
}
