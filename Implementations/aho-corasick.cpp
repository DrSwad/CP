struct AhoCorasick {
	const int A = 14;
	vector<vector<int>> trie;
	vector<int> parent, parent_char;
	vector<int> suffix_link;
	vector<vector<int>> suffix_jump;
	// vector<bool> cost_at_vis;
	// vector<ll> cost_at;
	// vector<vector<bool>> cost_jump_vis;
	// vector<vector<ll>> cost_jump;

	AhoCorasick() {
		trie.push_back(vector<int>(A, -1));
		parent.push_back(0);
		parent_char.push_back(-1);
		suffix_link.push_back(-1);
		suffix_jump.push_back(vector<int>(A, -1));
		// cost_at_vis.push_back(false);
		// cost_at.push_back(0);
		// cost_jump_vis.push_back(vector<bool>(A, false));
		// cost_jump.push_back(vector<ll>(A, 0));
	}
	void insert(const string& s, int cost) {
		int at = 0;
		for (int i = 0; i < s.length(); i++) {
			if (trie[at][s[i] - 'a'] == -1) {
				trie[at][s[i] - 'a'] = trie.size();

				trie.push_back(vector<int>(A, -1));
				parent.push_back(at);
				parent_char.push_back(s[i] - 'a');
				suffix_link.push_back(-1);
				suffix_jump.push_back(vector<int>(A, -1));
				// cost_at_vis.push_back(false);
				// cost_at.push_back(0);
				// cost_jump_vis.push_back(vector<bool>(A, false));
				// cost_jump.push_back(vector<ll>(A, 0));
			}
			at = trie[at][s[i] - 'a'];
		}
		// cost_at[at] += cost;
	}
	int suffixLink(int at) {
		if (suffix_link[at] != -1) return suffix_link[at];
		if (at == 0 || parent[at] == 0) return suffix_link[at] = 0;
		return suffix_link[at] = suffixJump(suffixLink(parent[at]), parent_char[at]);
	}
	int suffixJump(int at, int ch) {
		if (suffix_jump[at][ch] != -1) return suffix_jump[at][ch];
		if (trie[at][ch] != -1) return suffix_jump[at][ch] = trie[at][ch];
		if (at == 0) return suffix_jump[at][ch] = 0;
		return suffix_jump[at][ch] = suffixJump(suffixLink(at), ch);
	}
	// ll costAt(int at) {
	// 	if (cost_at_vis[at]) return cost_at[at];
	// 	cost_at_vis[at] = true;
	// 	return cost_at[at] += costAt(suffixLink(at));
	// }
	// ll costJump(int at, int ch) {
	// 	if (cost_jump_vis[at][ch]) return cost_jump[at][ch];
	// 	cost_jump_vis[at][ch] = true;
	// 	return cost_jump[at][ch] = costAt(suffixJump(at, ch));
	// }
} aho;