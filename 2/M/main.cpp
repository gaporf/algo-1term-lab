#include <bits/stdc++.h>

using namespace std;

int n;
vector<pair<int, int> > arr;
vector<int> a, b;

void compare(int A, int B) {
    if (A > B) {
        swap(A, B);
    }
    if (b[A] > b[B]) {
        swap(b[A], b[B]);
    }
}

void check() {
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
    }
    for (int i = 0; i < (int) arr.size(); i++) {
        compare(arr[i].first, arr[i].second);
    }
    for (int i = 0; i + 1 < n; i++) {
        if (b[i] > b[i + 1]) {
            cout << "No" << endl;
            exit(0);
        }
    }
}

void gen(int num) {
    if (num == n) {
        check();
    } else {
        a[num] = 0;
        gen(num + 1);
        a[num] = 1;
        gen(num + 1);
    }
}

int main() {
    int m, k;
    cin >> n >> m >> k;
    while (k--) {
        int r;
        cin >> r;
        while (r--) {
            int a, b;
            cin >> a >> b;
            arr.emplace_back(--a, --b);
        }
    }
    a.resize(n);
    b.resize(n);
    gen(0);
    cout << "Yes" << endl;

    return 0;
}
