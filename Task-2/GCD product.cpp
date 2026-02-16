#include <stdio.h>

#define P 1000000007
#define Pm1 1000000006
#define MIN(x, y) ((x) < (y) ? (x) : (y))

// Use static to move large arrays out of the stack to the data segment
static int nex[15000001];
static char is_prime[15000001];

long long mypower(long long a, long long b, long long c) {
    long long ret = 1;
    a %= c;
    while (b > 0) {
        if (b & 1) ret = (ret * a) % c;
        a = (a * a) % c;
        b >>= 1;
    }
    return ret;
}

void findprime(int range) {
    for (int i = 2; i <= range; i++) is_prime[i] = 1;
    int head = 0, last = 0;
    for (int i = 2; i <= range; i++) {
        if (is_prime[i]) {
            if (head == 0) head = i;
            if (last != 0) nex[last] = i;
            last = i;
            if ((long long)i * i <= range) {
                for (int j = i * i; j <= range; j += i) is_prime[j] = 0;
            }
        }
    }
    nex[last] = 0;
    nex[0] = head; // Store start of list in nex[0]
}

int main() {
    long long M, N;
    if (scanf("%lld %lld", &M, &N) != 2) return 0;

    int range = (M < N) ? (int)M : (int)N;
    findprime(range);

    long long ret = 1;
    for (int p = nex[0]; p != 0; p = nex[p]) {
        long long m = M / p, n = N / p;
        long long s = 0;
        while (m > 0 && n > 0) {
            s = (s + (m * n)) % Pm1;
            m /= p;
            n /= p;
        }
        ret = (ret * mypower(p, s, P)) % P;
    }

    printf("%lld\n", ret);
    return 0;
}