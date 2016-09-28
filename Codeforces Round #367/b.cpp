#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int a[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", a + i);
  sort(a, a + n);
  int q;
  scanf("%d", &q);
  while (q--) {
    int v;
    scanf("%d", &v);
    int p = upper_bound(a, a + n, v) - a;
    printf("%d\n", p);
  }

  return 0;
}
