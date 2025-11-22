#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int N = 100010;
struct Matrix {
    long long a, b, c, d;
    Matrix() : a(1), b(0), c(0), d(1) {} // Identity
    Matrix(long long a, long long b, long long c, long long d) 
        : a(a%MOD), b(b%MOD), c(c%MOD), d(d%MOD) {}
};
Matrix multiply(const Matrix& m1, const Matrix& m2) {
    return Matrix(
        (m1.a * m2.a % MOD + m1.b * m2.c % MOD) % MOD,
        (m1.a * m2.b % MOD + m1.b * m2.d % MOD) % MOD,
        (m1.c * m2.a % MOD + m1.d * m2.c % MOD) % MOD,
        (m1.c * m2.b % MOD + m1.d * m2.d % MOD) % MOD
    );
}
struct Instruction {
    int type;
    Matrix mat;
};
int n, m;
Instruction instructions[N];
// Function to simulate the execution of instructions
Matrix executeInstructions(int l, int r) {
    deque<pair<Matrix, int>> dq; // (matrix, insertion timestamp)
    int timestamp = 0;

    for (int i = l; i <= r; i++) {
        timestamp++;

        if (instructions[i].type == 1) {
            // Insert at the front
            dq.push_front({instructions[i].mat, timestamp});
        } else if (instructions[i].type == 2) {
            // Insert at the back
            dq.push_back({instructions[i].mat, timestamp});
        } else { // type == 3
            // Delete the last inserted item
            if (!dq.empty()) {
                // Find the item with the largest timestamp
                int maxIdx = 0;
                for (int j = 1; j < dq.size(); j++) {
                    if (dq[j].second > dq[maxIdx].second) {
                        maxIdx = j;
                    }
                }
                dq.erase(dq.begin() + maxIdx);
            }
        }
    }

    // Multiply all matrices from left to right
    if (dq.empty()) {
        return Matrix(); // Identity Matrix
    }

    Matrix result = dq[0].first;
    for (int i = 1; i < dq.size(); i++) {
        result = multiply(result, dq[i].first);
    }

    return result;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> instructions[i].type;
        if (instructions[i].type == 1 || instructions[i].type == 2) {
            long long a, b, c, d;
            cin >> a >> b >> c >> d;
            instructions[i].mat = Matrix(a, b, c, d);
        }
    }

    for (int i = 0; i < m; i++) {
        int type;
        cin >> type;

        if (type == 1) {
            int pos;
            cin >> pos;
            cin >> instructions[pos].type;
            if (instructions[pos].type == 1 || instructions[pos].type == 2) {
                long long a, b, c, d;
                cin >> a >> b >> c >> d;
                instructions[pos].mat = Matrix(a, b, c, d);
            }
        } else {
            int l, r;
            cin >> l >> r;
            Matrix res = executeInstructions(l, r);
            cout << res.a << " " << res.b << " " << res.c << " " << res.d << "\n";
        }
    }

    return 0;
}
