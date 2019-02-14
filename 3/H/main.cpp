#include <bits/stdc++.h>

using namespace std;

int n, shift = 0;
vector<int> color, rang;
vector<pair<int, int> > p;

int getNext(int v) {
    if (p[v].first == v) {
        return v;
    } else {
        int y = getNext(p[v].first);
        int last = p[v].first;
        p[v].first = y;
        p[v].second ^= p[last].second;
        if (p[v].second == 0) {
            color[v] = color[y];
        } else {
            color[v] = (color[y] ^ 1);
        }
        return y;
    }
}

void unite(int a, int b) {
    int A = getNext(a),
            B = getNext(b);
    if (rang[A] < rang[B]) {
        swap(A, B);
        swap(a, b);
    }
    if (rang[A] == rang[B]) {
        rang[A]++;
    }
    p[B].first = A;
    if (color[a] == color[b]) {
        color[B] ^= 1;
    }
    if (color[B] == color[A]) {
        p[B].second = 0;
    } else {
        p[B].second = 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int m;
    cin >> n >> m;
    color.resize(n, 0);
    p.resize(n);
    rang.resize(n, 0);
    for (int i = 0; i < n; i++) {
        p[i] = make_pair(i, 0);
    }
    while (m--) {
        int type, a, b;
        cin >> type >> a >> b;
        int x = (a + shift) % n,
                y = (b + shift) % n;
        if (x == 0) {
            x += n;
        }
        if (y == 0) {
            y += n;
        }
        x--;
        y--;
        if (type == 0) {
            unite(x, y);
        } else {
            getNext(x);
            getNext(y);
            if (color[x] != color[y]) {
                cout << "NO" << endl;
            } else {
                cout << "YES" << endl;
                shift = (shift + 1) % n;
            }
        }
    }
    return 0;
}
