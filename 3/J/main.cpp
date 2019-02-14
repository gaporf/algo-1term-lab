#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll p = (ll) 1e6 + 3;

struct man {
    int read, p, sum, rang;
};

vector<man> arr;
ll zerg = 0;
int n;

int getNext(int v) {
    if (arr[v].p == v) {
        return v;
    } else {
        int y = getNext(arr[v].p);
        if (y != arr[v].p) {
            arr[v].sum += arr[arr[v].p].sum;
        }
        arr[v].p = y;
        return y;
    }
}

void unite(int v, int u) {
    v = getNext(v);
    u = getNext(u);
    if (v != u) {
        zerg = (13 * zerg + 11) % p;
        if (arr[v].rang < arr[u].rang) {
            swap(v, u);
        } else if (arr[v].rang == arr[u].rang) {
            arr[v].rang++;
        }
        arr[u].sum -= arr[v].sum;
        arr[u].p = v;
    }
}

ll getAns(int v) {
    int V = getNext(v);
    ll q = arr[v].sum - arr[v].read;
    if (v != V) {
        q += arr[V].sum;
    }
    arr[v].read += (int) q;
    return q;
}

int main() {
    ios_base::sync_with_stdio(false);
    int m;
    cin >> n >> m;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        arr[i].p = i;
        arr[i].read = arr[i].sum = arr[i].rang = 0;
    }
    while (m--) {
        int type;
        cin >> type;
        int i, j;
        switch (type) {
            case 1: {
                cin >> i;
                i = (i + (int) zerg) % n;
                zerg = (30 * zerg + 239) % p;
                i = getNext(i);
                arr[i].sum++;
            }
                break;
            case 2: {
                cin >> i >> j;
                i = (i + (int) zerg) % n;
                j = (j + (int) zerg) % n;
                unite(i, j);
            }
                break;
            case 3: {
                cin >> i;
                i = (i + (int) zerg) % n;
                ll q = getAns(i);
                cout << q << endl;
                zerg = (100500 * zerg + q) % p;
            }
                break;
            default:
                cout << "Привет, Нияз!" << endl;
                break;
        }
    }
    return 0;
}
