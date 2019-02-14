#include <bits/stdc++.h>

using namespace std;

string a, b;
int n, m;
vector<vector<char> > dp;

int main() {
    ios_base::sync_with_stdio(false);
    getline(cin, a);
    n = (int) a.length();
    getline(cin, b);
    m = (int) b.length();
    dp.resize(n + 1);
    for (int i = 0; i <= n; i++) {
        dp[i].resize(m + 1, false);
    }
    dp[0][0] = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (a[i - 1] == '*') {
                if (j == 0) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = (dp[i][j - 1] | dp[i - 1][j - 1] | dp[i - 1][j]);
                }
            } else if (a[i - 1] == '?') {
                if (j > 0) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            } else if (j > 0 && a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }
    cout << ((dp[n][m]) ? "YES" : "NO");
    cout << endl;
    return 0;
}
