#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll x, m;

void ask(ll a) {
    cout << "? " << a << endl;
    fflush(stdout);
}

void answer(ll a) {
    cout << "! " << a << endl;
    fflush(stdout);
    exit(0);
}

int main() {
    cin >> x >> m;
    x--;
    ask(1);
    ll b, beg;
    cin >> beg;
    beg--;
    if (beg == x) {
        answer(1);
    }
    x -= beg;
    if (x < 0) {
        x += (ll) 1e18;
    }
    ll l = 0,
            r = min(m, x - 1);
    while (x - l + 1 > (ll) 1e18 - m) {
        l++;
    }
    while (l < r) {
        ll mid = (l + r) / 2;
        ask(x - mid + 1);
        cin >> b;
        b--;
        b -= beg;
        if (b < 0) {
            b += (ll) 1e18;
        }
        if (b == x) {
            answer(x - mid + 1);
        } else if (b > x) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    if (l == r) {
        ask(x - l + 1);
        cin >> b;
        b--;
        b -= beg;
        if (b < 0) {
            b += (ll) 1e18;
        }
        if (b == x) {
            answer(x - l + 1);
        } else {
            answer(-1);
        }
    } else {
        answer(-1);
    }

    return 0;
}
