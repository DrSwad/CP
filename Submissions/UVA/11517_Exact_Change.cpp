#include <bits/stdc++.h>
using namespace std;

const int INF = 1e7;

struct Coin
{
  int value;
  int multiplicity;

  Coin() { }

  Coin(int _value, int _multiplicity)
  {
    value = _value;
    multiplicity = _multiplicity;
  }

  bool operator <(const Coin &n)const
  {
    bool definitionOperator = false;
    if (value < n.value || (value == n.value && multiplicity < n.multiplicity)) definitionOperator = true;
    return definitionOperator;
  }
};

Coin dp[10005][105];
bool vi[10005][105];
int coins[105];
int n, price;

void init()
{
  for (int i = 0; i < 10005; i++)
    for (int j = 0; j < 105; j++) vi[i][j] = false;
}

Coin getAns(int amount, int i)
{
  if (amount >= price) return Coin(amount, 0);
  if (i >= n) return Coin(INF, INF);

  if (vi[amount][i]) return dp[amount][i];

  Coin ans1 = getAns(amount, i + 1);
  Coin ans2 = getAns(amount + coins[i], i + 1);
  ans2.multiplicity++;

  Coin ans = min(ans1, ans2);
  dp[amount][i] = ans;
  vi[amount][i] = true;
  return dp[amount][i];
}

int main()
{
  int t;
  cin >> t;
  //FILE *fp = fopen("out.txt", "w");
  while (t--)
  {
    init();
    cin >> price;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> coins[i];
    Coin ans = getAns(0, 0);
    //fprintf(fp, "%d %d\n", ans.value, ans.multiplicity);
    cout << ans.value << " " << ans.multiplicity << endl;
  }
  return 0;
}