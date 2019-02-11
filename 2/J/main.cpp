#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

unsigned int cur = 0, a, b;

unsigned int nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

unsigned int nextRand32() {
    unsigned int a = nextRand24(), b = nextRand24();
    return (a << 8) ^ b;
}

int n;
ll k, ans = 0;
vector<ll> arr, buf;

void findSegments(int l, int r) {
    if (l == r) {
        return;
    } else {
        int mid = (l + r) / 2;
        findSegments(l, mid);
        findSegments(mid + 1, r);
        for (int i = l, j = mid + 1; i <= mid && j <= r;) {
            if (arr[j] - arr[i] < k) {
                ans += mid - i + 1;
                j++;
            } else {
                i++;
            }
        }
        for (int i = l, j = mid + 1, k = 0; i <= mid || j <= r; k++) {
            if (i <= mid && j <= r) {
                if (arr[i] <= arr[j]) {
                    buf[k] = arr[i++];
                } else {
                    buf[k] = arr[j++];
                }
            } else if (i <= mid) {
                buf[k] = arr[i++];
            } else {
                buf[k] = arr[j++];
            }
        }
        for (int i = l; i <= r; i++) {
            arr[i] = buf[i - l];
        }
    }
}

int main() {
    cin >> n >> k >> a >> b;
    arr.resize(static_cast<unsigned int>(n + 1));
    buf.resize(static_cast<unsigned int>(n + 1));
    arr[0] = 0;
    for (int i = 1; i <= n; i++) {
        arr[i] = (ll) ((int) nextRand32());
        arr[i] += arr[i - 1];
    }
    findSegments(0, n);
    cout << (ll) n * ll(n + 1) / 2 - ans << endl;
    return 0;
}
