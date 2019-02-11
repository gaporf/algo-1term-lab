#include <bits/stdc++.h>

using namespace std;

int n;
double A;
vector<double> arr;

bool check() {
    for (int i = 2; i < n; i++) {
        arr[i] = 2 * (arr[i - 1] + 1) - arr[i - 2];
        if (arr[i] <= 0) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> n >> A;
    arr.resize(n);
    arr[0] = A;
    double r = A,
            l = 0;
    for (int i = 0; i < 10000; i++) {
        double mid = (l + r) / 2;
        arr[1] = mid;
        if (check()) {
            r = mid;
        } else {
            l = mid;
        }
    }
    setprecision(2);
    cout << fixed << setprecision(2) << arr.back();
    return 0;
}
