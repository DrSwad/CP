#include <bits/stdc++.h>
using namespace std;

struct Data {
  int type;
  string name;
  double value;
  Data(int type, string name, double value) {
    this->type = type;
    this->name = name;
    this->value = value;
  }
};

Data parseData(string raw) {
  int type = 1;
  string name;
  string valstr;
  double value;

  for (char ch : raw) {
    if (ch != '%') {
      if (valstr.empty() and ch != '+') name += ch;
      else valstr += ch;
    }
    else type = 2;
  }

  value = atof(valstr.c_str());
  if (type == 2) value = value / 100.0;

  return {type, name, value};
}

void handleData(Data d, double &atk, double &atkr, double &cr, double &cdr) {
  if (d.name == "ATK") {
    assert(d.type == 1);
    atk += d.value;
  }
  else if (d.name == "ATK Rate") {
    assert(d.type == 2);
    atkr += d.value;
  }
  else if (d.name == "Crit Rate") {
    assert(d.type == 2);
    cr += d.value;
    cr = min(1.0, cr);
  }
  else if (d.name == "Crit DMG Rate") {
    assert(d.type == 2);
    cdr += d.value;
    cdr = min(1.0, cdr);
  }
}

void armArtifact(double &atk, double &atkr, double &cr, double &cdr) {
  for (int i = 0; i < 5; i++) {
    string line;
    getline(cin, line);

    Data d = parseData(line);
    handleData(d, atk, atkr, cr, cdr);
  }
}

int main() {
  double atk = 1500, atkr = 0, cr = .05, cdr = .5;

  for (int i = 0; i < 5; i++) {
    armArtifact(atk, atkr, cr, cdr);
  }

  atk += 1500 * (1 + atkr);
  double damage = atk * (1 - cr) + atk * (1 + cdr) * cr;

  cout << fixed << setprecision(10) << damage << endl;

  return 0;
}