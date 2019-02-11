#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> arr;

int getLeftBound(int value) {
    int l = -1,
        r = n;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (arr[mid] < value) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return r;
}

int getRightBound(int value) {
    int l = -1,
        r = n;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (arr[mid] > value) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return l;
}

int main() {
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int m;
    cin >> m;
    while (m--) {
        int value;
        cin >> value;
        int l = getLeftBound(value) + 1,
            r = getRightBound(value) + 1;
        if (l <= r) {
            cout << l << " " << r << endl;
        } else {
            cout << -1 << " " << -1 << endl;
        }
    }
    return 0;
}
