#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> p, rang, big;

int getNext(vector<int> &p, int v) {
    if (p[v] == v) {
        return v;
    } else {
        return p[v] = getNext(p, p[v]);
    }
}

void unite(int a, int b) {
    a = getNext(p, a);
    b = getNext(p, b);
    if (a == b) {
        return;
    }
    if (rang[a] < rang[b]) {
        swap(a, b);
    }
    p[b] = a;
    if (rang[a] == rang[b]) {
        rang[a]++;
    }
}

void uniteBig(int a, int b) {
    a = getNext(big, a);
    b = getNext(big, b);
    if (a == b) {
        return;
    }
    big[a] = b;
}

int main() {
    ios_base::sync_with_stdio(false);
    int q;
    cin >> n >> q;
    p.resize(n);
    big.resize(n);
    rang.resize(n, 0);
    for (int i = 0; i < n; i++) {
        p[i] = i;
        big[i] = i;
    }
    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        x--;
        y--;
        if (type == 1) {
            unite(x, y);
        } else if (type == 2) {
            x = getNext(big, x);
            for (int i = x + 1; i <= y; i++) {
                int j = i - 1;
                i = getNext(big, i);
                unite(x, i);
                uniteBig(j, i);
            }
        } else {
            x = getNext(p, x);
            y = getNext(p, y);
            (x == y) ? cout << "YES" << endl : cout << "NO" << endl;
        }
    }
    return 0;
}
