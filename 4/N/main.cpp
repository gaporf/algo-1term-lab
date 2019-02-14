#include <bits/stdc++.h>

using namespace std;

const int MOD = (int) 1e9 + 7;

int n;
vector<vector<char> > used;
vector<vector<int> > dp;

int getMod(int a) {
    while (a < 0) {
        a += MOD;
    }
    return a % MOD;
}

int main() {
    freopen("operators.in", "r", stdin);
    freopen("operators.out", "w", stdout);
    int m;
    cin >> n >> m;
    n *= 2;
    dp.resize(n);
    used.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(n, 0);
        used[i].resize(n, true);
    }
    while (m--) {
        int r, p;
        cin >> r >> p;
        used[p][2 * (r - 1) + p] = false;
    }
    for (int j = 0; j < n; j++) {
        dp[0][j] = 1;
    }
    for (int i = 1; i < n; i++) {
        dp[i][i] = dp[i - 1][i];
        if (used[i][i]) {
            dp[i][i] = (dp[i][i] + dp[i - 1][i - 1]) % MOD;
        }
        for (int j = i + 1; j < n; j++) {
            dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
            dp[i][j] = getMod(dp[i][j] - dp[i - 1][j - 1]);
            if (i % 2 == j % 2 && used[i][j]) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD;
            }
        }
    }
    cout << dp.back().back() << endl;
    return 0;
}
