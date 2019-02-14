#include <bits/stdc++.h>

using namespace std;

const int INF = 58829464;

int n, P;
int bestAns = INF, bestV;
vector<vector<pair<int, int> > > g;
vector<vector<vector<int> > > dp;
vector<vector<vector<pair<int, int> > > > r;
vector<int> cnt, par, nums;
vector<char> del;

void dfs(int v, int p) {
    par[v] = p;
    int children = 0;
    for (int i = 0; i < (int) g[v].size(); i++) {
        int to = g[v][i].first,
                num = g[v][i].second;
        if (to != p) {
            nums[to] = num;
            dfs(to, v);
            cnt[v] += cnt[to];
            children++;
        }
    }
    int m = cnt[v];
    dp[v].resize(m + 1);
    r[v].resize(m + 1);
    for (int i = 1; i <= m; i++) {
        dp[v][i].resize(children + 1, INF);
        r[v][i].resize(children + 1);
    }
    dp[v][1][0] = 0;
    int last = 0;
    int M = 1;
    for (int i = 0; i < (int) g[v].size(); i++) {
        int to = g[v][i].first;
        if (to != p) {
            M += cnt[to];
            for (int j = 1; j <= M; j++) {
                dp[v][j][last + 1] = dp[v][j][last] + 1;
                r[v][j][last + 1] = make_pair(-1, j);
                for (int k = 1; k <= cnt[to] && j > k; k++) {
                    if (dp[to][k].back() + dp[v][j - k][last] < dp[v][j][last + 1]) {
                        dp[v][j][last + 1] = dp[to][k].back() + dp[v][j - k][last];
                        r[v][j][last + 1] = make_pair(to, k);
                    }
                }
            }
            last++;
        }
    }
    if (v == 0) {
        if (bestAns > dp[v][P].back()) {
            bestAns = dp[v][P].back();
            bestV = v;
        }
    } else if (P <= m) {
        if (bestAns > dp[v][P].back() + 1) {
            bestAns = dp[v][P].back() + 1;
            bestV = v;
        }
    }
}

void recover(int v, int P) {
    if (P < cnt[v]) {
        int t = (int) (dp[v][P].size() - 1);
        while (P > 1) {
            pair<int, int> R = r[v][P][t];
            if (R.first != -1) {
                del[R.first] = true;
                recover(R.first, R.second);
                P -= R.second;
            }
            t--;
        }
        for (int i = 0; i < (int) g[v].size(); i++) {
            int to = g[v][i].first,
                    num = g[v][i].second;
            if (to != par[v]) {
                if (!del[to]) {
                    cout << num << " ";
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> P;
    dp.resize(n);
    r.resize(n);
    g.resize(n);
    cnt.resize(n, 1);
    nums.resize(n);
    del.resize(n, false);
    for (int i = 1; i < n; i++) {
        int from, to;
        cin >> from >> to;
        --from;
        --to;
        g[from].push_back(make_pair(to, i));
        g[to].push_back(make_pair(from, i));
    }
    par.resize(n);
    dfs(0, -1);
    cout << bestAns << endl;
    recover(bestV, P);
    if (par[bestV] != -1) {
        cout << nums[bestV];
    }
    cout << endl;
    return 0;
}

