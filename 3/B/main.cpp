#include <bits/stdc++.h>

using namespace std;

struct DSU {
    DSU *parrent;
    int minimum, maximum, number, rank;

    explicit DSU(int a) {
        parrent = this;
        minimum = maximum = a;
        number = 1;
        rank = 0;
    }
};

typedef DSU *ptrDSU;

int n;
vector<ptrDSU> arr;

ptrDSU getNext(ptrDSU v) {
    if (v->parrent == v) {
        return v;
    } else {
        return v->parrent = getNext(v->parrent);
    }
}

void unite(ptrDSU v, ptrDSU u) {
    if (v->rank < u->rank) {
        swap(v, u);
    }
    u->parrent = v->parrent;
    v->number += u->number;
    v->maximum = max(v->maximum, u->maximum);
    v->minimum = min(v->minimum, u->minimum);
    if (v->rank == u->rank) {
        v->rank++;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    arr.resize(static_cast<unsigned long>(n));
    for (int i = 0; i < n; i++) {
        arr[i] = new DSU(i);
    }
    string command;
    while (cin >> command) {
        if (command == "get") {
            int v;
            cin >> v;
            v--;
            ptrDSU V = getNext(arr[v]);
            cout << V->minimum + 1 << " " << V->maximum + 1 << " " << V->number << endl;
        } else {
            int v, u;
            cin >> v >> u;
            v--;
            u--;
            ptrDSU V = getNext(arr[v]),
                    U = getNext(arr[u]);
            if (V != U) {
                unite(V, U);
            }
        }
    }
    return 0;
}
