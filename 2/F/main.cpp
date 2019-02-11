#include <bits/stdc++.h>

using namespace std;

vector<int> ans;
int n, a;

void solve(int l, int r) {
    if (l + 1 == r) {
        ans[l] = 1;
        ans[r] = 2;
        return;
    }
    int mid = (l + r) / 2;
    solve(l, r - 1);
    ans[r] = a++;
    swap(ans[mid], ans[r]);
}

int main() {
    cin >> n;
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    a = 3;
    ans.resize(static_cast<unsigned long>(n + 1));
    solve(1, n);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
