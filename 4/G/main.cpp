#include <bits/stdc++.h>

using namespace std;

int n, m, bestAns = 0, bestM = 0;
vector<int> dp, sum, p;
vector<pair<int, int> > arr;

void recover(int M) {
    if (dp[M] != 0) {
        for (int i = 0; i < n; i++) {
            if ((M & p[i]) != 0) {
                int prevM = (M ^ p[i]);
                if (dp[prevM] + 1 == dp[M] &&
                    sum[prevM] >= arr[i].first && sum[prevM] <= arr[i].second) {
                    recover(prevM);
                    cout << i + 1 << " ";
                    return;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    freopen("meetings.in", "r", stdin);
    freopen("meetings.out", "w", stdout);
    int k;
    cin >> n >> k;
    p.resize(n);
    p[0] = 1;
    for (int i = 1; i < n; i++) {
        p[i] = p[i - 1] * 2;
    }
    m = p.back() * 2;
    dp.resize(m, -1);
    dp[0] = 0;
    sum.resize(m, k);
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second >> k;
        for (int j = 0; j < m; j++) {
            if ((j & p[i]) != 0) {
                sum[j] += k;
            }
        }
    }
    for (int j = 1; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if ((j & p[i]) != 0) {
                int J = (j ^ p[i]);
                if (dp[J] != -1 && sum[J] >= arr[i].first
                    && sum[J] <= arr[i].second && dp[j] < dp[J] + 1) {
                    dp[j] = dp[J] + 1;
                    if (dp[j] > bestAns) {
                        bestAns = dp[j];
                        bestM = j;
                    }
                }
            }
        }
    }
    cout << dp[bestM] << endl;
    recover(bestM);
    cout << endl;
    return 0;
}
