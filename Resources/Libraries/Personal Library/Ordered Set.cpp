#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
    tree_order_statistics_node_update>
    ordered_set;
// find_by_order(k) : iterator to the k'th element (0-indexed)
// order_of_key(k) : number of items strictly smaller than k
// auto cmp = [](int a, int b) { return a < b; };
// tree<int, null_type, decltype(cmp)> x(cmp);
// tree<int, null_type, function<bool(int, int)>> y(
//     [](int a, int b) { return a < b; });