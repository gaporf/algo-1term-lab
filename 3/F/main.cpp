#include <bits/stdc++.h>

using namespace std;

struct operation {
    int type, a, b, ans;
};

int n, m, k;
vector<int> p, ran;
vector<operation> arr;

int getNext(int v) {
    if (p[v] == v) {
        return p[v];
    } else {
        return p[v] = getNext(p[v]);
    }
}

void unite(int a, int b) {
    a = getNext(a);
    b = getNext(b);
    if (ran[a] < ran[b]) {
        swap(a, b);
    }
    p[a] = b;
    if (ran[a] == ran[b]) {
        ran[a]++;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> m >> k;
    p.resize(n);
    ran.resize(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
        ran[i] = 0;
    }
    while (m--) {
        int a, b;
        cin >> a >> b;
    }
    arr.resize(k);
    for (int i = 0; i < k; i++) {
        string command;
        int a, b;
        cin >> command >> a >> b;
        a--;
        b--;
        if (command == "ask") {
            arr[i].type = 0;
            arr[i].a = a;
            arr[i].b = b;
        } else {
            arr[i].type = 1;
            arr[i].a = a;
            arr[i].b = b;
        }
    }
    reverse(arr.begin(), arr.end());
    for (int i = 0; i < k; i++) {
        if (arr[i].type == 0) {
            int A = getNext(arr[i].a),
                    B = getNext(arr[i].b);
            arr[i].ans = A == B;
        } else {
            unite(arr[i].a, arr[i].b);
        }
    }
    reverse(arr.begin(), arr.end());
    for (int i = 0; i < k; i++) {
        if (arr[i].type == 0) {
            if (arr[i].ans == 0) {
                cout << "NO" << endl;
            } else {
                cout << "YES" << endl;
            }
        }
    }
    return 0;
}
