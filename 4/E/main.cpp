#include <bits/stdc++.h>

using namespace std;

const int INF = (int) 2e9;

string a, b;
int n, m;
vector<vector<int> > dp;

int main() {
    freopen("levenshtein.in", "r", stdin);
    freopen("levenshtein.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin >> a >> b;
    n = (int) a.length();
    m = (int) b.length();
    dp.resize(static_cast<unsigned int>(n + 1));
    for (int i = 0; i <= n; i++) {
        dp[i].resize(static_cast<unsigned int>(m + 1), INF);
    }
    for (int i = 0; i <= m; i++) {
        dp[0][i] = i;
    }
    for (int i = 1; i <= n; i++) {
        dp[i][0] = i;
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
            }
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
            dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
        }
    }
    cout << dp[n][m];
    return 0;
}
