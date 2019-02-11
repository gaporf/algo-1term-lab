#include <bits/stdc++.h>

using namespace std;

const int INF = int(2e9);

int n;
vector<int> arr;

void pushUp(int num) {
    if (num != 0 && arr[(num - 1) / 2] > arr[num]) {
        swap(arr[(num - 1) / 2], arr[num]);
        pushUp((num - 1) / 2);
    }
}

void pushDown(int num) {
    if (2 * num + 1 < n) {
        int a = arr[2 * num + 1],
                b = INF;
        if (2 * num + 2 < n) {
            b = arr[2 * num + 2];
        }
        if (a < b) {
            if (arr[num] > arr[2 * num + 1]) {
                swap(arr[num], arr[2 * num + 1]);
                pushDown(2 * num + 1);
            }
        } else {
            if (arr[num] > arr[2 * num + 2]) {
                swap(arr[num], arr[2 * num + 2]);
                pushDown(2 * num + 2);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    arr.resize(static_cast<unsigned long>(n));
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        pushUp(i);
    }
    while (n > 0) {
        cout << arr[0] << " ";
        arr[0] = arr[n - 1];
        n--;
        pushDown(0);
    }

    return 0;
}
