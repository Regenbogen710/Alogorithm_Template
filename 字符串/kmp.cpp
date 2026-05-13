#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll nxt[1000010], n, m;
char s1[10000010], s2[1000010];

int main() {
    scanf("%s", s2 + 1);
    m = strlen(s2 + 1);
    scanf("%s", s1 + 1);
    n = strlen(s1 + 1);
    for (ll i = 2, j = 0; i <= n; i++) {
        while (j && s1[j + 1] != s1[i])j = nxt[j];
        if (s1[j + 1] == s1[i])j++;
        nxt[i] = j;
    }
    for (ll i = 1, j = 0; i <= m; i++) {
        while (j && s1[j + 1] != s2[i])j = nxt[j];
        if (s1[j + 1] == s2[i])j++;
        if (j == n) { printf("%lld\n", i - n + 1); }
    }
    for (ll i = 1; i <= n; i++)printf("%lld ", nxt[i]);
    return 0;
}
