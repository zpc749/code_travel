#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct BigInt {
    vector<int> d;   // 低位在前
    BigInt() {}
    BigInt(string s) {
        for (int i = s.size() - 1; i >= 0; --i)
            d.push_back(s[i] - '0');
        trim();
    }
    BigInt(int x) {
        if (x == 0) d.push_back(0);
        while (x) { d.push_back(x % 10); x /= 10; }
    }
    void trim() {
        while (d.size() > 1 && d.back() == 0) d.pop_back();
    }
    string toString() const {
        string s;
        for (int i = d.size() - 1; i >= 0; --i)
            s += char('0' + d[i]);
        return s;
    }
};

bool operator<(const BigInt& a, const BigInt& b) {
    if (a.d.size() != b.d.size()) return a.d.size() < b.d.size();
    for (int i = a.d.size() - 1; i >= 0; --i)
        if (a.d[i] != b.d[i]) return a.d[i] < b.d[i];
    return false;
}
bool operator==(const BigInt& a, const BigInt& b) { return a.d == b.d; }
bool operator>(const BigInt& a, const BigInt& b) { return b < a; }
bool operator<=(const BigInt& a, const BigInt& b) { return !(b < a); }
bool operator>=(const BigInt& a, const BigInt& b) { return !(a < b); }

BigInt operator+(const BigInt& a, const BigInt& b) {
    BigInt c;
    int carry = 0;
    for (int i = 0; i < a.d.size() || i < b.d.size() || carry; ++i) {
        int sum = carry;
        if (i < a.d.size()) sum += a.d[i];
        if (i < b.d.size()) sum += b.d[i];
        c.d.push_back(sum % 10);
        carry = sum / 10;
    }
    return c;
}

BigInt operator-(const BigInt& a, const BigInt& b) { // 要求 a >= b
    BigInt c;
    int borrow = 0;
    for (int i = 0; i < a.d.size(); ++i) {
        int sub = a.d[i] - borrow - (i < b.d.size() ? b.d[i] : 0);
        if (sub < 0) { sub += 10; borrow = 1; }
        else borrow = 0;
        c.d.push_back(sub);
    }
    c.trim();
    return c;
}

BigInt operator*(const BigInt& a, const BigInt& b) {
    BigInt c;
    c.d.assign(a.d.size() + b.d.size(), 0);
    for (int i = 0; i < a.d.size(); ++i)
        for (int j = 0; j < b.d.size(); ++j)
            c.d[i + j] += a.d[i] * b.d[j];
    for (int i = 0; i < c.d.size() - 1; ++i) {
        c.d[i + 1] += c.d[i] / 10;
        c.d[i] %= 10;
    }
    c.trim();
    return c;
}

BigInt divSmall(const BigInt& a, int b, int& r) {
    BigInt c;
    c.d.resize(a.d.size());
    r = 0;
    for (int i = a.d.size() - 1; i >= 0; --i) {
        int cur = r * 10 + a.d[i];
        c.d[i] = cur / b;
        r = cur % b;
    }
    c.trim();
    return c;
}

BigInt divBig(const BigInt& a, const BigInt& b, BigInt& rem) {
    BigInt c;
    c.d.assign(a.d.size(), 0);
    rem = BigInt(0);
    for (int i = a.d.size() - 1; i >= 0; --i) {
        rem.d.insert(rem.d.begin(), a.d[i]);
        rem.trim();
        int q = 0;
        for (int k = 9; k >= 0; --k) {
            BigInt tmp = b * BigInt(k);
            if (!(rem < tmp)) {
                q = k;
                rem = rem - tmp;
                break;
            }
        }
        c.d[i] = q;
    }
    c.trim();
    return c;
}

int main() {
    BigInt a("12345678901234567890");
    BigInt b("9876543210");
    cout << "a + b = " << (a + b).toString() << endl;
    cout << "a - b = " << (a - b).toString() << endl;
    cout << "a * b = " << (a * b).toString() << endl;

    int r;
    BigInt q1 = divSmall(a, 123, r);
    cout << "a / 123 = " << q1.toString() << " ... " << r << endl;

    BigInt rem;
    BigInt q2 = divBig(a, b, rem);
    cout << "a / b = " << q2.toString() << " ... " << rem.toString() << endl;
    return 0;
}
