#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 999999937;
ll n;
vector<vector<ll> > matrix;

vector<vector<ll> > multiply(vector<vector<ll> > a, vector<vector<ll> > b) {
    vector<vector<ll> > c;
    c.resize(5);
    for (int i = 0; i < 5; i++) {
        c[i].resize(5, 0);
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return c;
}

vector<vector<ll> > myPow(ll a) {
    if (a == 1) {
        return matrix;
    } else {
        vector<vector<ll> > newMatrix = myPow(a / 2);
        newMatrix = multiply(newMatrix, newMatrix);
        if (a % 2 == 1) {
            newMatrix = multiply(newMatrix, matrix);
        }
        return newMatrix;
    }
}

void solve() {
    if (n == 1) {
        cout << 5 << endl;
        return;
    }
    vector<vector<ll> > newMatrix = myPow(n - 1);
    ll ans = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            ans = (ans + newMatrix[i][j]) % MOD;
        }
    }
    cout << ans << endl;
}

int main() {
    freopen("sequences.in", "r", stdin);
    freopen("sequences.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    matrix.resize(5);
    for (int i = 0; i < 5; i++) {
        matrix[i].resize(5, 1);
    }
    matrix[2][3] = matrix[2][4] = matrix[4][3] = matrix[4][4] = 0;
    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }
        solve();
    }
    return 0;
}
