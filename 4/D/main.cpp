#include <bits/stdc++.h>

using namespace std;

int n, M;
vector<int> m, c;
vector<vector<int> > dp;

int main() {
    ios_base::sync_with_stdio(false);
    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
    cin >> n >> M;
    m.resize(n + 1);
    c.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> m[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    dp.resize(n + 1);
    for (int i = 0; i <= n; i++) {
        dp[i].resize(M + 1, 0);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= M; j++) {
            dp[i][j] = dp[i - 1][j];
        }
        for (int j = 0; j + m[i] <= M; j++) {
            if (dp[i][j + m[i]] < dp[i - 1][j] + c[i]) {
                dp[i][j + m[i]] = dp[i - 1][j] + c[i];
            }
        }
    }
    vector<int> ans;
    for (int i = n, j = M; i > 0;) {
        if (dp[i][j] == dp[i - 1][j]) {
            i--;
        } else {
            ans.push_back(i);
            j -= m[i];
            i--;
        }
    }
    cout << ans.size() << endl;
    for (int num : ans) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
