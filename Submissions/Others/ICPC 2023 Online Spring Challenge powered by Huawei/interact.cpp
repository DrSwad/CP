#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// const int MAX_TENANTS = 10;
const int MAX_TENANTS = 2;
// const int MAX_BUFFER_SIZE = 1e6;
const int MAX_BUFFER_SIZE = 1e3;
const int MAX_OPERATIONS = 1e6;
// const int MAX_OPERATIONS = 10;
const int MAX_BAD_PRIORITY = 10;
// const int MAX_DB_SIZE = 1e5;
const int MAX_DB_SIZE = 1e2;
// const int MAX_TENANT_BUFFER_SIZE = 1e5;
const int MAX_TENANT_BUFFER_SIZE = 5e1;

int hits = 0;

struct Input {
  int total_tenants;
  int total_buffer_size;
  int total_operations;

  int bad_priorities[MAX_TENANTS + 1];
  int db_sizes[MAX_TENANTS + 1];

  int buffer_min_sizes[MAX_TENANTS + 1];
  int buffer_base_sizes[MAX_TENANTS + 1];
  int buffer_max_sizes[MAX_TENANTS + 1];
} input;
ostream& operator<<(ostream &out, Input input) {
  out << input.total_tenants;
  out << " " << input.total_buffer_size;
  out << " " << input.total_operations << endl;

  for (int t = 1; t <= input.total_tenants; t++) {
    if (t > 1) out << " ";
    out << input.bad_priorities[t];
  }
  out << endl;

  for (int t = 1; t <= input.total_tenants; t++) {
    if (t > 1) out << " ";
    out << input.db_sizes[t];
  }
  out << endl;

  for (int t = 1; t <= input.total_tenants; t++) {
    if (t > 1) out << " ";
    out << input.buffer_min_sizes[t];
    out << " " << input.buffer_base_sizes[t];
    out << " " << input.buffer_max_sizes[t];
  }
  out << endl;

  return out;
}
void generate_input() {
  // input.total_tenants = rnd.next(1, MAX_TENANTS);
  // input.total_buffer_size = rnd.next(input.total_tenants, MAX_BUFFER_SIZE);
  // input.total_operations = rnd.next(1, MAX_OPERATIONS);
  input.total_tenants = MAX_TENANTS;
  input.total_buffer_size = MAX_BUFFER_SIZE;
  input.total_operations = MAX_OPERATIONS;

  for (int t = 1; t <= input.total_tenants; t++) {
    input.bad_priorities[t] = rnd.next(1, MAX_BAD_PRIORITY);
  }

  for (int t = 1; t <= input.total_tenants; t++) {
    input.db_sizes[t] = rnd.next(1, MAX_DB_SIZE);
  }

  int total_buffer_min_sizes = 0;

  for (int t = 1; t <= input.total_tenants; t++) {
    input.buffer_min_sizes[t] = rnd.next(1, min(MAX_TENANT_BUFFER_SIZE, input.total_buffer_size - total_buffer_min_sizes - (input.total_tenants - t)));
    input.buffer_base_sizes[t] = rnd.next(1, MAX_TENANT_BUFFER_SIZE);
    input.buffer_max_sizes[t] = rnd.next(input.buffer_min_sizes[t], MAX_TENANT_BUFFER_SIZE);

    total_buffer_min_sizes += input.buffer_min_sizes[t];
  }

  assert(total_buffer_min_sizes <= input.total_buffer_size);
}

struct Query {
  int tenant;
  int page;
} query;
ostream& operator<<(ostream &out, Query query) {
  return out << query.tenant << " " << query.page;
}
void generate_query() {
  query.tenant = rnd.next(1, input.total_tenants);
  query.page = rnd.next(1, input.db_sizes[query.tenant]);
}

int tenant_current_buffer_size[MAX_TENANTS + 1];
pair<int, int> page_at_buffer_position[MAX_BUFFER_SIZE + 1];
int page_position_in_buffer[MAX_TENANTS + 1][MAX_DB_SIZE + 1];

struct Answer {
  int buffer_position;
} answer;
ostream& operator<<(ostream &out, Answer answer) {
  return out << answer.buffer_position;
}
void receive_answer() {
  cin >> answer.buffer_position;
}
void respond_to_answer() {
  if (answer.buffer_position < 1 or input.total_buffer_size < answer.buffer_position) {
    cerr << "answer out of buffer bounds\n";
    exit(1);
  }

  if (page_position_in_buffer[query.tenant][query.page]) {
    if (page_position_in_buffer[query.tenant][query.page] != answer.buffer_position) {
      cerr << "page reallocated despite already existing in the buffer\n";
      exit(2);
    }
    hits++;
    return;
  }

  auto [prv_tenant, prv_page] = page_at_buffer_position[answer.buffer_position];

  if (prv_tenant != 0) {
    tenant_current_buffer_size[prv_tenant]--;
    page_position_in_buffer[prv_tenant][prv_page] = 0;
  }

  tenant_current_buffer_size[query.tenant]++;
  page_position_in_buffer[query.tenant][query.page] = answer.buffer_position;

  page_at_buffer_position[answer.buffer_position] = make_pair(query.tenant, query.page);

  if (prv_tenant != 0 and prv_tenant != query.tenant) {
    if (tenant_current_buffer_size[prv_tenant] < input.buffer_min_sizes[prv_tenant]) {
      cerr << "tenant buffer size went lower than the allowed minimum\n";
      exit(2);
    }
  }

  if (tenant_current_buffer_size[query.tenant] > input.buffer_max_sizes[query.tenant]) {
    cerr << "tenant buffer size went higher than the allowed maximum\n";
    exit(2);
  }
}

void handle_query() {
  generate_query();
  cout << query << endl;

  receive_answer();
  respond_to_answer();
}

void interact() {
  generate_input();
  cout << input << endl;

  for (int i = 0; i < input.total_operations; i++) {
    handle_query();
  }

  cout << "Result: " << (double)hits / input.total_operations * 100 << "%" << endl;
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  rnd.setSeed(785988939223LL);

  interact();

  return 0;
}
