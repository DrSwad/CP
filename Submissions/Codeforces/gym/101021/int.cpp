#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Input { int n; } input;
ostream& operator<<(ostream &out, Input input) {
  return out << input.n;
}
void generate_input() {
  input.n = rnd.next(1, (int)1e6);
}

struct Answer { int val; } answer;
ostream& operator<<(ostream &out, Answer answer) {
  return out << answer.val;
}
void generate_answer() {
  answer.val = rnd.next(1, input.n);
}

struct Query { string type; int val; } query;
void check_query_validity() {
  assert(1 <= query.val and query.val <= input.n);
}
void receive_query() {
  cin >> query.val;
  check_query_validity();
}
void respond_to_query() {
  if (answer.val < query.val) cout << "<" << endl;
  else cout << ">=" << endl;
}

struct Output { int val; } output;
ostream& operator<<(ostream &out, Output output) {
  return out << output.val;
}
void receive_output() {
  cin >> output.val;
}
void check_output() {
  if (output.val == answer.val) {
    return;
  }
  cerr << "wrong, answer " << answer << ", output " << output << "\n";
  exit(1);
}

bool handle_query() {
  string type;
  cin >> type;
  if (type == "?") {
    query.type = type;
    receive_query();
    respond_to_query();
  } else if (type == "!") {
    receive_output();
    check_output();
    return true;
  } else {
    cerr << "Unrecognized query type \"" << type << "\"\n";
    exit(3);
  }
  return false;
}

void interact() {
  generate_input();
  cout << input << endl;

  generate_answer();

  int max_queries = ceil(log2(input.n));
  ++max_queries;

  while (max_queries--) {
    bool finished = handle_query();
    if (finished) return;
  }

  cerr << "query limit exceeded\n";
  exit(2);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int t = 3;
  println(t);
  while (t--) {
    interact();
  }

  return 0;
}