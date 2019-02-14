#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> p;

int getNext(int v) {
    if (p[v] == v) {
        return v;
    } else {
        return p[v] = getNext(p[v]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    for (int i = 0; i < n; i++) {
        int car;
        cin >> car;
        car--;
        int place = getNext(car);
        cout << place + 1 << " ";
        p[place] = p[p[(place + 1) % n]];
    }

    return 0;
}
