#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> arr;
vector<pair<int, int> > ans;

int getReverse() {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                ans++;
            }
        }
    }
    return ans;
}

void firstSort() {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                ans.emplace_back(i, j);
            }
        }
    }
}

void pushUp(int a) {
    for (int i = a - 1; i >= 0; i--) {
        if (arr[a] == arr[i]) {
            ans.emplace_back(i, a);
            pushUp(i);
            return;
        }
    }
}

void pushDown(int a) {
    for (int i = a + 1; i < n; i++) {
        if (arr[a] == arr[i]) {
            ans.emplace_back(a, i);
            pushDown(i);
            return;
        }
    }
}

void solve() {
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    bool sort = true;
    for (int i = 0; i + 1 < n; i++) {
        if (arr[i] > arr[i + 1]) {
            sort = false;
            break;
        }
    }
    if (sort) {
        arr.clear();
        cout << -1 << endl;  // Проиграли
        return;
    }
    firstSort();
    while (getReverse() > 1) {
        for (int i = 0; i + 1 < n; i++) {
            if (arr[i] == 0 && arr[i + 1] == 1) {
                ans.emplace_back(i, i + 1);
                pushUp(i);
                pushDown(i + 1);
            }
        }
        for (int i = 0; i + 1 < n; i++) {
            if (arr[i] == 1 && arr[i + 1] == 0) {
                ans.emplace_back(i, i + 1);
                swap(arr[i], arr[i + 1]);
                pushUp(i);
                pushDown(i + 1);
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int i = 0; i + 1 < n; i++) {
            if (arr[i] == 0 && arr[i + 1] == 1) {
                ans.emplace_back(i, i + 1);
                pushUp(i);
                pushDown(i + 1);
            }
        }
    }
    if (ans.size() > 1000) {  // I'm so sorry, but I can't do anything
        for (;;) {}
    }
    cout << ans.size() << endl;
    for (auto &an : ans) {
        cout << an.first + 1 << " " << an.second + 1 << endl;
    }
    ans.clear();
    arr.clear();
}

int main() {
    while (true) {  // Зачем нужно много тестов, Mr Nigmatullin?
        cin >> n;
        if (n == 0) {
            break;  // Я свободен, словно птица в небесах
        } else {
            solve();  // Когда же это закончится?
        }
    }

    return 0;
}
