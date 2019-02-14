#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> a;

bool isHeap() {
    for (int i = 0; 2 * i + 1 < n; i++) {
        if (a[i] > a[2 * i + 1]) {
            return false;
        } else if (2 * i + 2 < n && a[i] > a[2 * i + 2]) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (isHeap()) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
