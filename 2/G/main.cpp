#include <bits/stdc++.h>

using namespace std;

unsigned int a, b, cur = 0;

const int K = 2048;

unsigned int nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

unsigned int nextRand32() {
    unsigned int a = nextRand24(), b = nextRand24();
    return (a << 8) ^ b;
}

int n;
vector<unsigned int> arr, newArr;
vector<int> nums[K];

void solve() {
    for (int i = 0; i < n; i++) {
        arr[i] = nextRand32();
        nums[arr[i] & 2047].push_back(i);
    }
    for (int i = 0, cur = 0; i < K; i++) {
        for (int j : nums[i]) {
            newArr[cur++] = arr[j];
        }
        if (!nums[i].empty()) {
            nums[i].clear();
        }
    }
    for (int i = 0; i < n; i++) {
        arr[i] = newArr[i];
    }
    for (int i = 0; i < n; i++) {
        nums[(arr[i] >> 11) & 2047].push_back(i);
    }
    for (int i = 0, cur = 0; i < K; i++) {
        for (int j : nums[i]) {
            newArr[cur++] = arr[j];
        }
        if (!nums[i].empty()) {
            nums[i].clear();
        }
    }
    for (int i = 0; i < n; i++) {
        arr[i] = newArr[i];
    }
    for (int i = 0; i < n; i++) {
        nums[arr[i] >> 22].push_back(i);
    }
    unsigned long long ans = 0;
    for (int i = 0, cur = 1; i < K; i++) {
        for (int j : nums[i]) {
            ans += (unsigned long long) (cur) * (unsigned long long) arr[j];
            cur++;
        }
        if (!nums[i].empty()) {
            nums[i].clear();
        }
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t >> n;
    cin >> a >> b;
    arr.resize(n);
    newArr.resize(n);
    while (t--) {
        solve();
    }
    return 0;
}
