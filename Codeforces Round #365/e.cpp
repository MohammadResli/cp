#include <bits/stdc++.h>

using namespace std;

const int N = 1005;
const int V = 1e6 + 5;
const int inf = 1e9;
const long long INF = 1e18;

vector<int> p, need;
long long a[N];

vector<int> prime;
bool is[V];

vector<pair<int, long long>> dp[N];
vector<int> to[N], pake[N];

int main() {
  for (int i = 2; i < N; i++) {
    if (!is[i]) {
      prime.push_back(i);
      for (long long j = 1LL * i * i; j < N; j += i) {
        is[j] = 1;
      }
    }
  }
  long long pol = 1e12;
  long long cc = 1, cnt = 0;
  for (auto it : prime) {
    if (cc * it < pol) {
      cc *= it;
      cnt++;
    }
  }
  cout << cnt << endl;
  
  int n;
  long long k;
  scanf("%d %I64d", &n, &k);
  for (int i = 1; i <= n; i++) scanf("%I64d", a + i);
  if (k == 1) {
    long long mn = INF;
    int ans = -1;
    for (int i = 1; i <= n; i++) if (a[i] < mn) {
      mn = a[i];
      ans = i;
    }
    printf("1 %d\n", ans);
    return 0;
  }
  for (auto it : prime) {
    if (k % it == 0) {
      p.push_back(it);
      need.push_back(0);
      while (k % it == 0) {
        need.back()++;
        k /= it;
      }
    }
  }
  if (k > 1) {
    p.push_back(k);
    need.push_back(1);
  }
  assert(k == 1);
  int state = 1;
  for (auto it : need) state *= (it + 1);
  for (int i = 0; i < N; i++) {
    dp[i].assign(state, {inf, INF});
    to[i].assign(state, -1);
    pake[i].assign(state, 0);
  }
  dp[0][0] = {0, 0};
  int ada[p.size()];
  int v[p.size()];
  //for (auto it : need) printf("%d ", it); printf("\n");
  for (int i = 1; i <= n; i++) {
    memset(v, 0, sizeof(v));
    long long val = a[i];
    for (int k = 0; k < p.size(); k++) {
      while (val % p[k] == 0) {
        //printf("%I64d %d\n", val, v[k]);
        v[k]++;
        val /= p[k];
      }
      //printf("%d ", v[k]);
    }
    //printf("\n");
    for (int j = 0; j < state; j++) {
      if (dp[i - 1][j].first == inf) continue;
      memset(ada, 0, sizeof(ada));
      int mask = j;
      for (int k = 0; k < p.size(); k++) {
        ada[k] = mask % (need[k] + 1);
        mask /= need[k] + 1;
      }
      assert(mask == 0);
      for (int k = 0; k < p.size(); k++) {
        ada[k] = min(need[k], ada[k] + v[k]);
      }
      int tj = 0, mul = 1;
      for (int k = 0; k < p.size(); k++) {
        tj += ada[k] * mul;
        mul *= need[k] + 1;
      }
      assert(tj < state);
      pair<int, long long> cur = {dp[i-1][j].first + 1, dp[i-1][j].second + a[i]};
      if (cur < dp[i][tj]) {
        dp[i][tj] = cur;
        to[i][tj] = j;
        pake[i][tj] = 1;
      }
      if (dp[i-1][j] < dp[i][j]) {
        dp[i][j] = dp[i-1][j];
        to[i][j] = j;
        pake[i][j] = 0;
      }
    }
  }
  if (dp[n][state - 1].first == inf) {
    puts("-1");
    return 0;
  }
  printf("%d\n", dp[n][state - 1].first);
  int now = n, st = state - 1;
  while (now) {
    if (pake[now][st]) {
      printf("%d ", now);
    }
    st = to[now][st];
    now--;
  }
  return 0;
}
