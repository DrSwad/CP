inv[1] = fact[0] = ifact[0] = 1;
for (int i = 2; i < N; i++) inv[i] = mul(inv[mod % i], (mod - mod / i));
for (int i = 1; i < N; i++) fact[i] = mul(fact[i - 1], i);
for (int i = 1; i < N; i++) ifact[i] = mul(ifact[i - 1], inv[i]);
