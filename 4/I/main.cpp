#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = (ll) 1e9 + 7;

struct edge {
    int to;
    ll L, R;

    edge(int to, ll L, ll R) {
        this->to = to;
        this->L = L;
        this->R = R;
    }
};

int n, m;
vector<vector<edge> > g;
vector<ll> cnt, dp, last;
vector<pair<ll, ll> > arr;

void lose() {
    cout << 0 << endl;
    exit(0);
}

void dfs(int v, int p) {
    for (int i = 0; i < (int) g[v].size(); i++) {
        int to = g[v][i].to;
        ll L = g[v][i].L,
                R = g[v][i].R;
        if (to != p) {
            dfs(to, v);
            cnt[v] += cnt[to];
            ll u = 2 * cnt[to] * (ll) (n - cnt[to]) * L;
            if (u > (ll) m) {
                lose();
            } else {
                m -= (int) u;
                arr.emplace_back(2 * cnt[to] * (ll) (n - cnt[to]), R - L);
            }
        }
    }
}

ll getMod(ll a) {
    if (a < 0) {
        a += (abs(a) / MOD) * MOD;
    }
    while (a < 0) {
        a += MOD;
    }
    return a %= MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int from, to;
        ll L, R;
        cin >> from >> to >> L >> R;
        from--;
        to--;
        g[from].push_back(edge(to, L, R));
        g[to].push_back(edge(from, L, R));
    }
    cnt.resize(n, 1);
    dfs(0, -1);
    dp.resize(m + 1, 0);
    last.resize(m + 1, 0);
    last[0] = 1;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j <= m; j++) {
            dp[j] = last[j];
            if ((ll) j >= arr[i].first) {
                dp[j] = (dp[j] + dp[j - arr[i].first]) % MOD;
                if ((ll) j >= (arr[i].second + 1) * arr[i].first) {
                    dp[j] = getMod(dp[j] - last[j - (arr[i].second + 1) * arr[i].first]);
                }
            }
        }
        for (int j = 0; j <= m; j++) {
            last[j] = dp[j];
        }
    }
    cout << dp[m] << endl;
    return 0;
}
