/*
   Computes primes and multiplicative function values in O(n).

   Here, a multiplicative function is considered `easy` if
   f(i * p) can be determined `easily` from f(i) given p | i.
   The function is considered `hard` otherwise.

   The function `func` in the following code is defined as:
    Easy: func(x) = phi(x),
              since phi(i * p) = phi(i) * p given p | i
    Hard: func(x) = multiplication of the exponents in
              x's prime factorization
 */

vector<int> prime;
bool is_composite[MAXN];
// int func[MAXN], cnt[MAXN];

void sieve(int n) { // primes in range [1, n)
  fill(is_composite, is_composite + n, false);
  // func[1] = 1; // Initialize for 1

  for (int i = 2; i < n; i++) {
    if (!is_composite[i]) {
      prime.push_back(i);

      // Initialize func function for primes
      // func[i] = i - 1; // easy example func
      // func[i] = 1; // hard example func

      // For hard multiplicative functions:
      // cnt[i] = 1; // Initialize cnt function for primes
    }
    for (int j = 0; j < prime.size() && i * prime[j] < n; j++) {
      is_composite[i * prime[j]] = true;
      if (i % prime[j] == 0) { // prime[j] divides i
        // Initialize func function for composites of first type
        // func[i * prime[j]] = func[i] * prime[j]; // easier example func
        // func[i * prime[j]] = func[i] / cnt[i] * (cnt[i] + 1); // hard example func

        // For hard multiplicative functions:
        // cnt[i * prime[j]] = cnt[i] + 1;
        break;
      }
      else { // prime[j] does not divide i
        // Initialize func function for composites of first type
        // func[i * prime[j]] = func[i] * func[prime[j]];

        // For hard multiplicative functions:
        // cnt[i * prime[j]] = 1;
      }
    }
  }
}