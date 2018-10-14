/*

Hello, it's me
I was wondering if after all these weeks you'd like to meet
To go over everything
They say that time's supposed to heal ya
But I ain't done much healing

Hello, can you hear me
I'm here dreaming about who we used to be
When we were younger and free
I've forgotten how it felt before the world fell at our feet

There's such a difference between us
And a million miles

Hello from the other side
I must have called a thousand times
To tell you I'm sorry for everything that I've done
But when I call you never seem to be home

Hello from the outside
At least I can say that I've tried
To tell you I'm sorry for breaking your heart
But it don't matter it clearly doesn't tear you apart anymore

Hello, how are you?
It's so typical of me to talk about myself I'm sorry
I hope that you're well
Did you ever make it out of that town where nothing ever happened

It's no secret that the both of us
Are running out of time

So hello from the other side
I must have called a thousand times
To tell you I'm sorry for everything that I've done
But when I call you never seem to be home
Hello from the outside
At least I can say that I've tried
To tell you I'm sorry for breaking your heart
But it don't matter it clearly doesn't tear you apart anymore

Ooooohh, anymore
Ooooohh, anymore
Ooooohh, anymore
Anymore

Hello from the other side
I must have called a thousand times
To tell you I'm sorry for everything that I've done
But when I call you never seem to be home
Hello from the outside
At least I can say that I've tried
To tell you I'm sorry for breaking your heart
But it don't matter it clearly doesn't tear you apart anymore

*/

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

struct segtree {
  segtree() {}
  segtree(int n, vector<int> ori) : n(n), ori(ori) {
    num.resize(n << 2);
    push.resize(n << 2);
    build(1, 0, n - 1);
  }
  void build(int p, int l, int r) {
    if (l > r) return;
    if (l == r) {
      num[p] = ori[l];
      return;
    }
    int mid = (l + r) >> 1;
    build(p + p, l, mid);
    build(p + p + 1, mid + 1, r);
    num[p] = num[p + p] + num[p + p + 1];
  }
  void relax(int p, int l, int r) {
    if (push[p]) {
      if (l < r) {
        push[p + p] += push[p];
        push[p + p + 1] += push[p];
      }
      num[p] += (r - l + 1) * push[p];
      push[p] = 0;
    }
  }
  void combine(int p, int l, int r) {
    num[p] = num[p + p] + num[p + p + 1];
  }
  void add(int l, int r, int val) {
    if (l <= r) {
      add(1, 0, n - 1, l, r, val);
    }
  }
  void add(int p, int l, int r, int ll, int rr, int val) {
    relax(p, l, r);
    if (ll <= l && r <= rr) {
      push[p] += val;
      relax(p, l, r);
      return;
    }
    if (r < ll || rr < l) return;
    int mid = (l + r) >> 1;
    add(p + p, l, mid, ll, rr, val);
    add(p + p + 1, mid + 1, r, ll, rr, val);
    combine(p, l, r);
  }
  int find(int at) {
    return find(1, 0, n - 1, at);
  }
  int find(int p, int l, int r, int at) {
    relax(p, l, r);
    if (l == at && r == at) return num[p];
    if (r < at || at < l) return 0;
    int mid = (l + r) >> 1;
    int ret = find(p + p, l, mid, at) + find(p + p + 1, mid + 1, r, at);
    combine(p, l, r);
    return ret;
  }
  vector<int> num, push, ori;
  int n;
};

vector<int> edge[N];
vector<int> pre[2];
int h[N], lef[N][2], rig[N][2], a[N];

void dfs(int now, int bef) {
  lef[now][0] = pre[0].size();
  lef[now][1] = pre[1].size();
  pre[h[now] % 2].push_back(now);
  for (auto it : edge[now]) {
    if (it == bef) continue;
    h[it] = h[now] + 1;
    dfs(it, now);
  }
  rig[now][0] = (int) pre[0].size() - 1;
  rig[now][1] = (int) pre[1].size() - 1;
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", a + i);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(1, 0);
  vector<int> num[2];
  for (int j = 0; j < 2; j++) {
    for (auto it : pre[j]) {
      num[j].push_back(a[it]);
    }
  }
  segtree seg[2];
  seg[0] = segtree(pre[0].size(), num[0]);
  seg[1] = segtree(pre[1].size(), num[1]);
  while (m--) {
    int t, x, val;
    scanf("%d", &t);
    if (t == 1) {
      scanf("%d %d", &x, &val);
      int c = h[x] % 2;
      seg[c].add(lef[x][c], rig[x][c], val);
      seg[c^1].add(lef[x][c^1], rig[x][c^1], -val);
    } else {
      scanf("%d", &x);
      printf("%d\n", seg[h[x]%2].find(lef[x][h[x]%2]));
    }
  }

  return 0;
}
