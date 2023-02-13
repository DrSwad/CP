const int PRIME_SZ = ;
int prime[PRIME_SZ], prime_sz;
bitset<N> mark;

void sieve(){
  for(int i = 2; i < N; ++i){
    if(!mark[i])prime[prime_sz++] = i;
    for(int j = 0; j < prime_sz and i * prime[j] < N and (!j or j and i % prime[j - 1]); ++j){
      mark[i * prime[j]] = true;
    }
  }
}