#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct cash {
    ll a, b, t;
};

ll n, p, t;
int m;
vector<cash> arr, buf;

void sort(int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    sort(l, mid);
    sort(mid + 1, r);
    for (int i = l, j = mid + 1, k = 0; i <= mid || j <= r;) {
        if (i <= mid && j <= r) {
            ll a, b;
            if (arr[i].a != 0) {
                a = max(0ll, (t - arr[i].t - arr[i].b) / arr[i].a);
            } else {
                if (t - arr[i].t - arr[i].b >= 0) {
                    a = p + 1;
                } else {
                    a = 0;
                }
            }
            if (arr[j].a != 0) {
                b = max(0ll, (t - arr[j].t - arr[j].b) / arr[j].a);
            } else {
                if (t - arr[i].t - arr[i].b >= 0) {
                    b = p + 1;
                } else {
                    b = 0;
                }
            }
            if (a <= b) {
                buf[k++] = arr[j++];
            } else {
                buf[k++] = arr[i++];
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

bool check() {
    sort(0, m - 1);
    ll curP = 0;
    for (int i = 0; i < min(n, (ll) m); i++) {
        if (arr[i].a != 0) {
            curP += max((ll) 0, (t - arr[i].t - arr[i].b) / arr[i].a);
        } else if (t - arr[i].t - arr[i].b >= 0) {
            curP += p + 1;
        }
    }
    return curP >= p;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> m;
    arr.resize(m);
    buf.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> arr[i].a >> arr[i].b >> arr[i].t;
    }
    cin >> n >> p;
    ll l = -1,
            r = (ll) 2e10 + 1;
    while (l + 1 < r) {
        ll mid = (l + r) / 2;
        t = mid;
        if (check()) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << endl;
    return 0;
}
