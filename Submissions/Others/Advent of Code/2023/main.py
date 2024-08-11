import sys
from collections import Counter, defaultdict

ans = 0
pref_sum = defaultdict(int)
pref_sum[1] = 1

for line in sys.stdin.readlines():
  card_label, data = line.split(':')

  label, card_number = card_label.split()
  card_number = int(card_number)
  pref_sum[card_number] += pref_sum[card_number - 1]

  ans += pref_sum[card_number]

  winning, have = data.split('|')
  winning_values = list(map(int, winning.split()))
  have_values = list(map(int, have.split()))
  
  winning_values_counter = Counter(winning_values)
  cnt = 0

  for val in have_values:
    if val in winning_values_counter:
      cnt += 1
  
  pref_sum[card_number + 1] += pref_sum[card_number]
  pref_sum[card_number + cnt + 1] -= pref_sum[card_number]

print(ans)