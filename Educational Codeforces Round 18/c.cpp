#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int inf = 1e9;

char s[N];
int dp[N][3][3], used[N][3][3];
pair<int, int> back[N][3][3];
// 0 berarti belum sama sekali
// 1 nol sekali
// 2 bebas

void upd(int i, int j, int k, int ti, int tj, int tk, int val) {
  int temp = val;
  val += dp[ti][tj][tk];
  if (val < dp[i][j][k]) {
    dp[i][j][k] = val;
    back[i][j][k] = {tj, tk};
    used[i][j][k] = !temp;
  }
}

void dfs(int i, int j, int k) {
  if (i == 0) return;
  pair<int, int> tmp = back[i][j][k];
  dfs(i - 1, tmp.first, tmp.second);
  if (used[i][j][k]) printf("%c", s[i]);
}

int main() {
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        dp[i][j][k] = inf;
      }
    }
  }
  dp[0][0][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        upd(i, j, k, i-1, j, k, 1);
      }
      if (s[i] == '0') {
        upd(i, j, 1, i-1, j, 0, 0);
        upd(i, j, 2, i-1, j, 2, 0);
      } else {
        upd(i, (j + s[i] - '0') % 3, 2, i-1, j, 0, 0);
        upd(i, (j + s[i] - '0') % 3, 2, i-1, j, 2, 0);
      }
    }
  }
  int ans = inf, p = -1;
  for (int k = 1; k < 3; k++) {
    if (dp[n][0][k] < ans) {
      ans = dp[n][0][k];
      p = k;
    }    
  }
  if (ans == inf) {
    puts("-1");
    return 0;
  }
  dfs(n, 0, p); printf("\n");
  return 0;
}
