#include <bits/stdc++.h>

using namespace std;

const int INF = (int) 2e9;

int n;
vector<int> arr, dp, maxValue;

int find(int value) {
    int l = -1,
            r = n + 1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (dp[mid] < value) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    freopen("lis.in", "r", stdin);
    freopen("lis.out", "w", stdout);
    cin >> n;
    arr.resize(n);
    maxValue.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    dp.resize(n + 1, INF);
    dp[0] = -INF;
    int ans = 0,
        pos = 0;
    for (int i = 0; i < n; i++) {
        int index = find(arr[i]);
        if (dp[index + 1] > arr[i]) {
            dp[index + 1] = arr[i];
        }
        maxValue[i] = index + 1;
        if (index + 1 > ans) {
            ans = index + 1;
            pos = i;
        }
    }
    cout << ans << endl;
    vector<int> ansArr;
    int value = arr[pos];
    ansArr.push_back(value);
    ans--;
    for (int i = pos - 1; i >= 0; i--) {
        if (maxValue[i] == ans && arr[i] < value) {
            ansArr.push_back(arr[i]);
            value = arr[i];
            ans--;
        }
    }
    reverse(ansArr.begin(), ansArr.end());
    for (int i : ansArr) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
