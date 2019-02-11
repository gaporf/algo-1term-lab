#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> arr;
int n, k;
ll L, R;

void fill() {
    int A, B, C, a1, a2;
    cin >> A >> B >> C >> a1 >> a2;
    arr[0] = a1;
    arr[1] = a2;
    for (int i = 2; i < n; i++) {
        arr[i] = A * arr[i - 2] + B * arr[i - 1] + C;
    }
    L = R = arr[0];
    for (int i = 0; i < n; i++) {
        L = min(L, (ll) arr[i]);
        R = max(R, (ll) arr[i]);
    }
}

ll orderStatistics() {
    L--;
    R++;
    while (L + 1 < R) {
        ll mid = (L + R) / 2;
        int newK = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] < mid) {
                newK++;
            }
        }
        if (newK > k) {
            R = mid;
        } else {
            L = mid;
        }
    }
    return L;
}

int main() {
    cin >> n >> k;
    k--;
    arr.resize((unsigned long) max(2, n));
    fill();
    cout << orderStatistics();
    return 0;
}
