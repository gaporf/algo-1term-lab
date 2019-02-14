#include <bits/stdc++.h>

using namespace std;

int x, a, y, b, l;
vector<vector<int> > dp;

bool check(int w) {
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j <= y; j++) {
            dp[i][j] = -1;
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j <= y; j++) {
            if (dp[i][j] == -1) {
                continue;
            }
            for (int k = 0; i + k <= x; k++) {
                int newJ;
                if (k * a >= w) {
                    newJ = 0;
                } else {
                    newJ = (w - k * a) / b;
                    if (newJ * b + k * a < w) {
                        newJ++;
                    }
                }
                if (i + k <= x && j + newJ <= y) {
                    dp[i + k][j + newJ] = max(dp[i + k][j + newJ], dp[i][j] + 1);
                    if (dp[i + k][j + newJ] >= l) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    freopen("bridge.in", "r", stdin);
    freopen("bridge.out", "w", stdout);
    cin >> x >> a >> y >> b >> l;
    dp.resize(x + 1);
    for (int i = 0; i <= x; i++) {
        dp[i].resize(y + 1);
    }
    int minW = 1,
            maxW = (x * a + y * b) / l + 1;
    while (minW + 1 < maxW) {
        int mid = (minW + maxW) / 2;
        if (check(mid)) {
            minW = mid;
        } else {
            maxW = mid;
        }
    }
    cout << minW << endl;
    return 0;
}
