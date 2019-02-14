#include <bits/stdc++.h>

using namespace std;

const int INF = (int) 2e9;

int n, N;
vector<vector<pair<int, int> > > g;
vector<vector<int> > dp;

int myPow(int a) {
    int ans = 1;
    while (a--) {
        ans *= 2;
    }
    return ans;
}

int main() {
    freopen("salesman.in", "r", stdin);
    freopen("salesman.out", "w", stdout);
    int m;
    cin >> n >> m;
    N = myPow(n);
    g.resize(n);
    while (m--) {
        int from, to, dist;
        cin >> from >> to >> dist;
        from--;
        to--;
        g[from].push_back(make_pair(to, dist));
        g[to].push_back(make_pair(from, dist));
    }
    dp.resize(N);
    for (int i = 0; i < N; i++) {
        dp[i].resize(n, INF);
    }
    for (int i = 0; i < n; i++) {
        dp[myPow(i)][i] = 0;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < n; j++) {
            if (dp[i][j] == INF) {
                continue;
            }
            for (int k = 0; k < (int) g[j].size(); k++) {
                int to = g[j][k].first,
                        dist = g[j][k].second,
                        TO = myPow(to);
                if ((TO & i) == 0 && dp[TO | i][to] > dp[i][j] + dist) {
                    dp[TO | i][to] = dp[i][j] + dist;
                }
            }
        }
    }
    int ans = INF;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[N - 1][i]);
    }
    (ans == INF) ? cout << -1 << endl : cout << ans << endl;
    return 0;
}
