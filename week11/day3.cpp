// 1434
#include <iostream>
#include <string>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        ll a = 0, b = 0, c = 0, d = 0, e = 0;
        for (char ch : s) {
            if (ch == 'E') {
                a = (a + 1) % MOD;
            } else if (ch == 'D') {
                b = (b + a) % MOD;
            } else if (ch == 'G') {
                c = (c + b) % MOD;
            } else if (ch == 'N') {
                d = (d + c) % MOD;
            } else if (ch == 'B') {
                e = (e + d) % MOD;
            }
        }
        cout << e << '\n';
    }
    return 0;
}
