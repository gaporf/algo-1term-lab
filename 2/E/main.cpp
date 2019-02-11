#include <bits/stdc++.h>

using namespace std;

int n, m, k;
vector<string> arr;

void mySort(int index) {
    vector<int> chars[26];
    vector<string> newArr;
    for (int i = 0; i < n; i++) {
        chars[arr[i][index] - 'a'].push_back(i);
    }
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < (int) chars[i].size(); j++) {
            newArr.push_back(arr[chars[i][j]]);
        }
    }
    arr = newArr;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m >> k;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i <= k; i++) {
        mySort(m - i);
    }
    for (int i = 0; i < n; i++) {
        cout << arr[i] << endl;
    }
    return 0;
}
