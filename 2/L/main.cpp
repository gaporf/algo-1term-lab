#include <bits/stdc++.h>

using namespace std;

struct precious {
    double u, w;
    int num;
};

int n, k;
vector<precious> arr, buf;

void sort(int l, int r, double q) {
    if (l == r) {
        return;
    } else {
        int mid = (l + r) / 2;
        sort(l, mid, q);
        sort(mid + 1, r, q);
        for (int i = l, j = mid + 1, k = 0; i <= mid || j <= r; k++) {
            if (i <= mid && j <= r) {
                if (arr[i].u - q * arr[i].w <= arr[j].u - q * arr[j].w) {
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

bool check(double mid) {
    sort(0, n - 1, mid);
    double ans = 0;
    for (int i = n - 1; i >= n - k; i--) {
        ans += arr[i].u - mid * arr[i].w;
    }
    return ans >= 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> k;
    buf.resize(n);
    arr.resize(static_cast<unsigned long>(n));
    for (int i = 0; i < n; i++) {
        cin >> arr[i].u >> arr[i].w;
        arr[i].num = i;
    }
    double l = 0,
            r = 1e7;
    while (r - l > 1e-7) {
        double mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    for (int i = n - 1; i >= n - k; i--) {
        cout << arr[i].num + 1 << " ";
    }

    return 0;
}
