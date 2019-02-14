#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, m, k, M, curMask;
vector<int> arr, p;
vector<vector<int> > dp, g;

void countDP() {
    dp.resize(M);
    for (int i = 0; i < M; i++) {
        dp[i].resize(n, 0);
    }
    for (int i = 0; i < n; i++) {
        dp[p[i]][i] = 1;
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < n; j++) {
            if ((i & p[j]) != 0) {
                for (int l = 0; l < n; l++) {
                    if ((i & p[l]) == 0 && g[j][l] >= k) {
                        dp[i + p[l]][l] += dp[i][j];
                    }
                }
            }
        }
    }
}

void found() {
    int last = -1;
    for (int i = 0; i < n && last == -1; i++) {
        if ((p[i] & curMask) != 0) {
            int newMask = curMask - p[i];
            for (int j = 0; j < n; j++) {
                if ((p[j] & newMask) != 0 && g[i][j] >= k) {
                    if (dp[newMask][j] >= m) {
                        last = j;
                        cout << arr[i] << " ";
                        curMask = newMask;
                        break;
                    } else {
                        m -= dp[newMask][j];
                    }
                }
            }
        }
    }
    if (last == -1) {
        cout << -1 << endl;
        return;
    }
    for (int len = 1; len < n; ++len) {
        int newMask = curMask - p[last];
        for (int j = 0; j < n; j++) {
            if ((p[j] & newMask) != 0 && g[last][j] >= k) {
                if (dp[newMask][j] >= m) {
                    cout << arr[last] << " ";
                    last = j;
                    curMask = newMask;
                    break;
                } else {
                    m -= dp[newMask][j];
                }
            }
        }
    }
    cout << arr[last] << endl;
}

int gcd(int a, int b) {
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

main() {
    ios_base::sync_with_stdio(false);
    freopen("perm.in", "r", stdin);
    freopen("perm.out", "w", stdout);
    cin >> n >> m >> k;
    p.resize(n);
    p[0] = 1;
    for (int i = 1; i < n; i++) {
        p[i] = p[i - 1] * 2;
    }
    M = p.back() * 2;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    if (n == 1) {
        if (m == 1) {
            cout << arr[0] << endl;
        } else {
            cout << -1 << endl;
        }
        return 0;
    }
    sort(arr.begin(), arr.end());
    g.resize(n);
    for (int i = 0; i < n; i++) {
        g[i].resize(n);
        for (int j = 0; j < n; j++) {
            g[i][j] = gcd(arr[i], arr[j]);
        }
    }
    countDP();
    curMask = M - 1;
    found();
    return 0;
}
