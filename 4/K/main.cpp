#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = (ll) 1e9;

int n;
vector<int> a;
vector<vector<ll> > dp;

ll getMod(ll a) {
    if (a < 0) {
        a += (abs(a) / MOD) * MOD;
    }
    while (a < 0) {
        a += MOD;
    }
    return a % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(n, 0);
        dp[i][i] = 1;
    }
    for (int len = 1; len < n; ++len) {
        for (int i = 0; i + len < n; i++) {
            dp[i][i + len] = getMod(dp[i + 1][i + len] +
                                    dp[i][i + len - 1] - dp[i + 1][i + len - 1]);
            if (a[i] == a[i + len]) {
                dp[i][i + len] = getMod(dp[i][i + len] + dp[i + 1][i + len - 1] + 1);
            }
        }
    }
    cout << dp[0][n - 1] << endl;
    return 0;
}
