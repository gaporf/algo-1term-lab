#include <bits/stdc++.h>

using namespace std;

int n, m;

void check() {
    m--;
    if (m == 0) {
        exit(0);
    }
}

void myCout(int a, int b, int c) {
    cout << a << " " << b << " " << c << endl;
    check();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    myCout(1, 1, 2);
    if (m == 1) {
        myCout(0, 1, 2);
    }
    myCout(1, 1, 3);
    myCout(0, 2, 3);
    myCout(1, 1, 4);
    myCout(1, 1, 5);
    myCout(0, 4, 5);
    myCout(1, 1, 6);
    myCout(1, 1, 7);
    myCout(0, 6, 7);
    int cur = 8,
        last = 1;
    while (true) {
        myCout(1, cur, last);
        myCout(0, 2, 3);
        myCout(0, 4, 5);
        myCout(0, 6, 7);
        last = cur;
        cur++;
    }
    return 0;
}
