#include <bits/stdc++.h>

#define int long long
using namespace std;

const int INF = (int) 2e18 + 228;

int n;
vector<int> f, ans;
vector<vector<int> > dp, r;

int getValue(int l, int r) {
    return f[r] - ((l > 0) ? f[l - 1] : 0);
}

void dfs(int L, int R) {
    if (L < R) {
        int mid = r[L][R];
        ans.push_back(0);
        dfs(L, mid);
        ans.pop_back();
        ans.push_back(1);
        dfs(mid + 1, R);
        ans.pop_back();
    } else {
        for (auto i : ans) {
            cout << i;
        }
        cout << endl;
    }
}

main() {
    ios_base::sync_with_stdio(false);
    freopen("optimalcode.in", "r", stdin);
    freopen("optimalcode.out", "w", stdout);
    cin >> n;
    f.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> f[i];
        f[i] += ((i > 0) ? f[i - 1] : 0);
    }
    dp.resize(n);
    r.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(n, INF);
        r[i].resize(n, -1);
        dp[i][i] = 0;
        r[i][i] = i;
    }
    for (int d = 1; d < n; d++) {
        for (int i = 0; i + d < n; i++) {
            for (int j = r[i][i + d - 1]; j <= r[i + 1][i + d]; j++) {
                if (j + 1 < n && dp[i][i + d] >= dp[i][j] + dp[j + 1][i + d] + getValue(i, i + d)) {
                    dp[i][i + d] = dp[i][j] + dp[j + 1][i + d] + getValue(i, i + d);
                    r[i][i + d] = j;
                }
            }
        }
    }
    cout << dp[0][n - 1] << endl;
    dfs(0, n - 1);
    return 0;
}
