#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = (ll) 1e18;

int n;
vector<pair<ll, ll> > matrix;
vector<vector<ll> > dp;
vector<vector<int> > p;

void dfs(int l, int r) {
    if (l == r) {
        cout << "A";
    } else {
        cout << "(";
        dfs(l, p[l][r]);
        dfs(p[l][r] + 1, r);
        cout << ")";
    }
}

int main() {
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin >> n;
    matrix.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> matrix[i].first >> matrix[i].second;
    }
    dp.resize(n);
    p.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(n, INF);
        p[i].resize(n, -1);
        dp[i][i] = 0;
    }
    for (int j = 1; j < n; j++) {
        for (int i = 0; i + j < n; i++) {
            for (int k = i; k + 1 <= i + j; k++) {
                if (dp[i][i + j] >
                    dp[i][k] + dp[k + 1][i + j] +
                    matrix[i].first * matrix[k].second * matrix[i + j].second) {
                    dp[i][i + j] =
                            dp[i][k] + dp[k + 1][i + j] +
                            matrix[i].first * matrix[k].second * matrix[i + j].second;
                    p[i][i + j] = k;
                }
            }
        }
    }
    dfs(0, n - 1);
    cout << endl;
    return 0;
}
