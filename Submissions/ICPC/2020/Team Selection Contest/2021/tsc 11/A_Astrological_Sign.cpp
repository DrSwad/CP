#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<string> signs{"Aries",       "Taurus",    "Gemini",   "Cancer",
                       "Leo",         "Virgo",     "Libra",    "Scorpio",
                       "Sagittarius", "Capricorn", "Aquarius", "Pisces",
                       "Aries"};
  vector<string> months{"Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct",
                        "Nov", "Dec", "Jan", "Feb", "Mar", "Apr"};
  vector<int> dates{20, 20, 21, 22, 22, 21, 22, 22, 21, 20, 19, 20, 20};

  int t;
  cin >> t;

  while (t--) {
    int d;
    scanf("%d", &d);

    string m;
    cin >> m;

    int ansI;
    for (ansI = 0; ansI < signs.size(); ansI++) {
      if (m == months[ansI]) {
        if (d <= dates[ansI]) break;
        ansI++;
        break;
      }
    }

    cout << signs[ansI] << "\n";
  }

  return 0;
}
