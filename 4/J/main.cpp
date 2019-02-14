#include <bits/stdc++.h>

using namespace std;

string a, b;
int n, m, ans;
vector<vector<int> > dp;

void dfs(int ll, int lr, int rl, int rr, int ans) {
    if (ans == 0) {
        return;
    }
    if (ans == 1) {
        for (int i = ll; i <= lr; i++) {
            for (int j = rl; j <= rr; j++) {
                if (a[i - 1] == b[j - 1]) {
                    cout << a[i - 1];
                    return;
                }
            }
        }
    }
    int mid = (ll + lr) / 2;
    dp.resize(n + 1);
    dp[ll - 1].resize(m + 1, 0);
    for (int i = ll; i <= mid; i++) {
        dp[i].resize(m + 1, 0);
        for (int j = rl; j <= rr; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = max(max(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1] + 1);
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        vector<int>().swap(dp[i - 1]);
    }
    vector<int> bestl(m + 1),
            bestr(m + 1);
    for (int i = rl; i <= rr; i++) {
        bestl[i] = dp[mid][i];
    }
    vector<vector<int> >().swap(dp);
    dp.resize(n + 2);
    dp[lr + 1].resize(m + 2, 0);
    for (int i = lr; i > mid; i--) {
        dp[i].resize(m + 2, 0);
        for (int j = rr; j >= rl; j--) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = max(max(dp[i + 1][j], dp[i][j + 1]), dp[i + 1][j + 1] + 1);
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
            }
        }
        vector<int>().swap(dp[i + 1]);
    }
    for (int i = rl; i <= rr; i++) {
        bestr[i] = dp[mid + 1][i];
    }
    vector<vector<int> >().swap(dp);
    for (int i = rl; i < rr; i++) {
        if (bestl[i] + bestr[i + 1] == ans) {
            int a = bestl[i];
            vector<int>().swap(bestl);
            vector<int>().swap(bestr);
            dfs(ll, mid, rl, i, a);
            dfs(mid + 1, lr, i + 1, rr, ans - a);
            return;
        }
    }
    if (bestl[rr] == ans) {
        vector<int>().swap(bestl);
        vector<int>().swap(bestr);
        dfs(ll, mid, rl, rr, ans);
        return;
    }
    if (bestr[rl] == ans) {
        vector<int>().swap(bestl);
        vector<int>().swap(bestr);
        dfs(mid + 1, lr, rl, rr, ans);
        return;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> a >> b;
    n = (int) a.length();
    m = (int) b.length();
    dp.resize(n + 1);
    dp[0].resize(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        dp[i].resize(m + 1, 0);
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = max(max(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1] + 1);
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        vector<int>().swap(dp[i - 1]);
    }
    ans = dp[n][m];
    if (ans == 0) {
        return 0;
    }
    vector<vector<int> >().swap(dp);
    dfs(1, n, 1, m, ans);
    cout << endl;
    return 0;
}
