#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<int> > yes;
vector<vector<pair<int, int> > > p;

void recover(int x, int y) {
    if (x != 0 || y != 0) {
        int X = p[x][y].first,
            Y = p[x][y].second;
        recover(X, Y);
        cout << y - Y;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    cin >> n;
    if (n < 10) {
        cout << n << endl;
        return 0;
    }
    yes.resize(n);
    p.resize(n);
    for (int i = 0; i < n; i++) {
        yes[i].resize(n + 1, 0);
        p[i].resize(n + 1);
    }
    queue<pair<int, int> > q;
    for (int i = 1; i <= 9; i++) {
        yes[i][i] = 1;
        p[i][i] = make_pair(0, 0);
        q.push(make_pair(i, i));
    }
    while (!q.empty()) {
        int x = q.front().first,
            y = q.front().second;
        q.pop();
        for (int u = 0; u <= 9; u++) {
            int X = (x * 10 + u) % n,
                Y = y + u;
            if (Y <= n && yes[X][Y] == 0) {
                yes[X][Y] = yes[x][y] + 1;
                q.push(make_pair(X, Y));
                p[X][Y] = make_pair(x, y);
            }
        }
    }
    recover(0, n);
    cout << endl;
    return 0;
}
