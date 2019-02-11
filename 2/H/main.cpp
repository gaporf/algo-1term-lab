#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef long long ll;

ll ans = 0;
int n;
uint cur = 0, m, a, b;
vector<uint> arr, buf;

uint nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

void getInversion(int l, int r) {
    if (l == r) {
        return;
    } else {
        int mid = (l + r) / 2;
        getInversion(l, mid);
        getInversion(mid + 1, r);
        for (int i = l, j = mid + 1, k = 0; i <= mid || j <= r;) {
            if (i <= mid && j <= r) {
                if (arr[i] <= arr[j]) {
                    buf[k++] = arr[i++];
                } else {
                    buf[k++] = arr[j++];
                    ans += mid - i + 1;
                }
            } else if (i <= mid) {
                buf[k++] = arr[i++];
            } else {
                buf[k++] = arr[j++];
            }
        }
        for (int i = l; i <= r; i++) {
            arr[i] = buf[i - l];
        }
    }
}

int main() {
    cin >> n >> m;
    cin >> a >> b;
    arr.resize(n);
    buf.resize(n);
    for (int i = 0; i < n; i++) {
        arr[i] = nextRand24() % m;
    }
    getInversion(0, n - 1);
    cout << ans << endl;
    return 0;
}
