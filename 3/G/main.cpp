#include <bits/stdc++.h>

using namespace std;

const int MIN_VALUE = -2147483648;

int n, N = 0;
vector<vector<pair<int, int> > > arr;
vector<int> heap, numOfOperation, numOfNumber;

void pushUp(int num) {
    if (num != 0) {
        int up = (num - 1) / 2;
        if (heap[up] < heap[num]) {
            swap(heap[up], heap[num]);
            int A = numOfOperation[up],
                    B = numOfOperation[num];
            swap(numOfOperation[up], numOfOperation[num]);
            swap(numOfNumber[A], numOfNumber[B]);
            pushUp(up);
        }
    }
}

void pushDown(int num) {
    if (2 * num + 1 < N) {
        int a = heap[2 * num + 1],
                b = MIN_VALUE;
        if (2 * num + 2 < N) {
            b = heap[2 * num + 2];
        }
        if (a > b) {
            if (heap[num] < a) {
                swap(heap[num], heap[2 * num + 1]);
                int A = numOfOperation[num],
                        B = numOfOperation[2 * num + 1];
                swap(numOfOperation[num], numOfOperation[2 * num + 1]);
                swap(numOfNumber[A], numOfNumber[B]);
                pushDown(2 * num + 1);
            }
        } else {
            if (heap[num] < b) {
                swap(heap[num], heap[2 * num + 2]);
                int A = numOfOperation[num],
                        B = numOfOperation[2 * num + 2];
                swap(numOfOperation[num], numOfOperation[2 * num + 2]);
                swap(numOfNumber[A], numOfNumber[B]);
                pushDown(2 * num + 2);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int m;
    cin >> n >> m;
    arr.resize(n + 1);
    while (m--) {
        int l, r, v;
        cin >> l >> r >> v;
        l--;
        r--;
        arr[l].push_back(make_pair(r + 1, v));
    }
    arr[0].push_back(make_pair(n, MIN_VALUE));
    for (int i = 0, cur = 0; i < n; i++) {
        for (int j = 0; j < (int) arr[i].size(); j++) {
            if (arr[i][j].first > 0) {
                heap.push_back(arr[i][j].second);
                numOfOperation.push_back(cur);
                numOfNumber.push_back(N);
                N++;
                pushUp(N - 1);
                int r = arr[i][j].first;
                arr[r].push_back(make_pair(-cur, arr[i][j].second));
                cur++;
            } else {
                int num = -arr[i][j].first;
                int u = numOfNumber[num];
                swap(heap[u], heap[N - 1]);
                int A = numOfOperation[u],
                        B = numOfOperation[N - 1];
                swap(numOfOperation[u], numOfOperation[N - 1]);
                swap(numOfNumber[A], numOfNumber[B]);
                heap.pop_back();
                numOfOperation.pop_back();
                numOfNumber[A] = -1;
                N--;
                pushDown(u);
                pushUp(u);
            }
        }
        cout << heap[0] << " ";
    }
    cout << endl;
    return 0;
}
