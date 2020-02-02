#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = int(3e5) + 10;
const int M = 1505;

int n, m;
int r1[N], r2[N];
int c1[N], c2[N];
vector<int> event_coords;
vector<pair<int, bool>> events[M];
unordered_map<int, int> include_carpets[M], exclude_carpets[M];
int carpet_covers[N];
map<pii, int> pair_covers;
int total_covered, max_removal;

void reset() {
	event_coords.clear();
	for (int i = 1; i <= m + 1; i++) {
		events[i].clear();
		include_carpets[i].clear();
		exclude_carpets[i].clear();
	}
	for (int i = 1; i <= n; i++) carpet_covers[i] = 0;
	pair_covers.clear();
	total_covered = max_removal = 0;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			scanf("%d %d %d %d", &r1[i], &r2[i], &c1[i], &c2[i]);
		}

		for (int i = 1; i <= n; i++) {
			event_coords.push_back(c1[i]);
			events[c1[i]].push_back(make_pair(i, 1));

			event_coords.push_back(c2[i] + 1);
			events[c2[i] + 1].push_back(make_pair(i, 0));
		}

		sort(event_coords.begin(), event_coords.end());
		event_coords.resize(uint(unique(event_coords.begin(), event_coords.end())
							- event_coords.begin()));

		int prev_coord, at_coord;
		for (int i = 0; i < (int)event_coords.size(); i++) {
			at_coord = event_coords[(uint)i];

			if (i > 0) {
				int jump_len = at_coord - prev_coord;
				unordered_map<int, int> got_carpets;

				for (int at_row = 1; at_row <= m + 1; at_row++) {
					if ((int)got_carpets.size() > 0) total_covered += jump_len;

					if ((int)got_carpets.size() == 1) {
						int carpet_id = (*got_carpets.begin()).first;
						carpet_covers[carpet_id] += jump_len;
					}
					else if ((int)got_carpets.size() == 2) {
						vector<int> carpet_ids;
						for (pair<const int, int> &item : got_carpets) carpet_ids.push_back(item.first);
						pair_covers[make_pair(carpet_ids[0], carpet_ids[1])] += jump_len;
					}

					for (pair<const int, int> &item : include_carpets[at_row]) got_carpets[item.first] = 1;
					for (pair<const int, int> &item : exclude_carpets[at_row]) got_carpets.erase(item.first);
				}
			}

			for (pii event : events[at_coord]) {
				int carpet_id = event.x;
				bool is_starting = event.y;

				if (is_starting) {
					include_carpets[r1[carpet_id]][carpet_id] = 1;
					exclude_carpets[r2[carpet_id] + 1][carpet_id] = 1;
				}
				else {
					include_carpets[r1[carpet_id]].erase(carpet_id);
					exclude_carpets[r2[carpet_id] + 1].erase(carpet_id);
				}
			}

			prev_coord = at_coord;
		}

		int carpet_covers_max1 = 0, carpet_covers_max2 = 0;
		for (int i = 1; i <= n; i++) {
			if (carpet_covers[i] >= carpet_covers_max1) {
				carpet_covers_max2 = carpet_covers_max1;
				carpet_covers_max1 = carpet_covers[i];
			}
			else if (carpet_covers[i] >= carpet_covers_max2) {
				carpet_covers_max2 = carpet_covers[i];
			}
		}
		max_removal = max(max_removal, carpet_covers_max1 + carpet_covers_max2);

		for (auto item : pair_covers) {
			int carpet1 = item.x.x;
			int carpet2 = item.x.y;
			int covered = item.y + carpet_covers[carpet1] + carpet_covers[carpet2];
			max_removal = max(max_removal, covered);
		}

		printf("%d\n", total_covered - max_removal);

		// reset everything
		reset();
	}

	return 0;
}