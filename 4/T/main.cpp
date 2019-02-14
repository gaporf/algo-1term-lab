#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
vector<vector<pair<int, int> > > g;
vector<ll> mySize, len, ans;

void dfs(int v, int p) {
    mySize[v] = 1;
    len[v] = 0;
    for (int i = 0; i < (int) g[v].size(); i++) {
        int to = g[v][i].first;
        if (to != p) {
            dfs(to, v);
            mySize[v] += mySize[to];
            len[v] += len[to] + mySize[to];
        }
    }
}

void dfs(int v, int p, ll pLen, ll pSize, int num) {
    pLen += pSize;
    for (int i = 0; i < (int) g[v].size(); i++) {
        int to = g[v][i].first,
                num = g[v][i].second;
        if (to != p) {
            dfs(to, v, pLen + len[v] - len[to] - mySize[to], pSize + mySize[v] - mySize[to], num);
        }
    }
    if (num != -1) {
        ans[num] = len[v] * pSize + pLen * mySize[v];
    }
}

int main() {
    freopen("treedp.in", "r", stdin);
    freopen("treedp.out", "w", stdout);
    cin >> n;
    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int from, to;
        cin >> from >> to;
        from--;
        to--;
        g[from].push_back(make_pair(to, i));
        g[to].push_back(make_pair(from, i));
    }
    mySize.resize(n);
    len.resize(n);
    ans.resize(n - 1);
    dfs(0, -1);
    dfs(0, -1, 0, 0, -1);
    for (int i = 0; i < n - 1; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
