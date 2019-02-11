#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int> > ans[16];

int n, m = 0, R = 0;

int getNextPow(int a) {
    int curAns = 1;
    while (curAns < a) {
        curAns *= 2;
    }
    return curAns;
}

int buildSortingNetwork(int l, int r) {
    int deep = 0;
    if (l == r) {
        return deep;
    }
    if (l + 1 == r) {
        if (r + 1 <= n) {
            ans[deep].emplace_back(l + 1, r + 1);
            R = max(R, 1);
            m++;
        }
        return deep;
    }
    int mid = (l + r) / 2;
    deep = max(deep, buildSortingNetwork(l, mid) + 1);
    deep = max(deep, buildSortingNetwork(mid + 1, r) + 1);
    for (int i = l, j = r; i < j; i++, j--) {
        if (j + 1 <= n) {
            ans[deep].emplace_back(i + 1, j + 1);
            m++;
        }
    }
    for (int s = getNextPow(r - l + 1) / 4; s > 0; s /= 2) {
        deep++;
        vector<char> used(n, false);
        for (int i = l; i <= r; i++) {
            if (!used[i]) {
                if (i + s + 1 <= n) {
                    ans[deep].emplace_back(i + 1, i + s + 1);
                    m++;
                    used[i] = used[i + s] = true;
                }
            }
        }
    }
    R = max(R, deep + 1);
    return deep;
}

int main() {
    cin >> n;
    buildSortingNetwork(0, getNextPow(n) - 1);
    cout << n << " " << m << " " << R << endl;
    if (R > 12) {
        cout << "Проиграли";
    }
    for (int i = 0; i < R; i++) {
        cout << ans[i].size() << " ";
        for (auto j : ans[i]) {
            cout << j.first << " " << j.second << " ";
        }
        cout << endl;
    }
    return 0;
}
