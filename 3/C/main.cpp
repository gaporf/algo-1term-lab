#include <bits/stdc++.h>

using namespace std;

const int INF = int(2e9);

vector<int> heap, numOfOperation, numOfNumber;
int n = 0;

void pushUp(int num) {
    if (num != 0) {
        int down = (num - 1) / 2;
        if (heap[down] > heap[num]) {
            swap(heap[down], heap[num]);
            int A = numOfOperation[down],
                    B = numOfOperation[num];
            swap(numOfOperation[down], numOfOperation[num]);
            swap(numOfNumber[A], numOfNumber[B]);
            pushUp(down);
        }
    }
}

void pushDown(int num) {
    if (2 * num + 1 < n) {
        int a = heap[2 * num + 1],
                b = INF;
        if (2 * num + 2 < n) {
            b = heap[2 * num + 2];
        }
        if (a < b) {
            if (heap[num] > a) {
                swap(heap[num], heap[2 * num + 1]);
                int A = numOfOperation[num],
                        B = numOfOperation[2 * num + 1];
                swap(numOfOperation[num], numOfOperation[2 * num + 1]);
                swap(numOfNumber[A], numOfNumber[B]);
                pushDown(2 * num + 1);
            }
        } else {
            if (heap[num] > b) {
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
    string command;
    int m = 0;
    while (cin >> command) {
        if (command == "push") {
            int a;
            cin >> a;
            heap.push_back(a);
            numOfOperation.push_back(m);
            numOfNumber.push_back(n);
            n++;
            pushUp(n - 1);
        } else if (command == "extract-min") {
            if (heap.size() == 0) {
                cout << "*" << endl;
            } else {
                cout << heap[0] << " " << numOfOperation[0] + 1 << endl;
                swap(heap[0], heap[n - 1]);
                int A = numOfOperation[0],
                        B = numOfOperation[n - 1];
                swap(numOfOperation[0], numOfOperation[n - 1]);
                swap(numOfNumber[A], numOfNumber[B]);
                heap.pop_back();
                numOfOperation.pop_back();
                numOfNumber[A] = -1;
                n--;
                pushDown(0);
            }
            numOfNumber.push_back(92);
        } else {
            int num, d;
            cin >> num >> d;
            num--;
            if (numOfNumber[num] != -1) {
                int u = numOfNumber[num];
                heap[u] = d;
                pushUp(u);
            }
            numOfNumber.push_back(57);
        }
        m++;
    }
    return 0;
}
