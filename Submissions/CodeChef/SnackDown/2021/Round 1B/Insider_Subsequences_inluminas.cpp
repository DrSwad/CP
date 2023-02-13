#include"bits/stdc++.h"
using namespace std;

#define ll long long
#define endl "\n"
#define fastio ios_base::sync_with_stdio(false)
#define inf LLONG_MAX

const int lmt=1e5+10;
int sum[3*lmt],sz,n;
set<int>s;

void build(int at,int L,int R){
  if(L==R){
    sum[at]=0;
    return;
  }
  int mid=(L+R)>>1;
  build(at*2,L,mid);
  build(at*2+1,mid+1,R);
  sum[at]=0;
}

void update(int at,int L,int R,int pos,int u){
  if(L==R){
    sum[at]+=u;
    return;
  }
  int mid=(L+R)>>1;
  if(pos<=mid) update(at*2,L,mid,pos,u);
  else update(at*2+1,mid+1,R,pos,u);
  sum[at]=sum[at*2]+sum[at*2+1];
}

int query(int at,int L,int R,int l,int r){
  if(r<l || R<l || r<L) return 0;
  if(l<=L && R<=r) return sum[at];
  int mid=(L+R)>>1;
  int x=query(at*2,L,mid,l,r);
  int y=query(at*2+1,mid+1,R,l,r);
  return x+y;
}

void check(int id){
  if(!query(1,1,n,id,id)) return;
  if(s.empty()){
    update(1,1,n,id,-1);
    return;
  }
  auto it=s.lower_bound(id);
  if(it==s.end()){
    it--;
    int pre=(*it);
    int x=query(1,1,n,pre+1,n);
    update(1,1,n,id,-1);
    //cout<<id<<endl;
    if(x && !query(1,1,n,pre+1,n)) sz--;
    return;
  }

  if(it==s.begin()){
    int suf=(*it);
    int x=query(1,1,n,1,suf-1);
    update(1,1,n,id,-1);
    //cout<<id<<endl;
    if(x && !query(1,1,n,1,suf-1)) sz--;
    return;
  }

  int suf=(*it);
  it--;
  int pre=(*it);

  int x=query(1,1,n,pre+1,suf-1);
  update(1,1,n,id,-1);
  //cout<<id<<endl;
  if(x && !query(1,1,n,pre+1,suf-1)){
    sz-=2;
    s.erase(pre);
  }

  return;

  /*int x=query(1,1,n,pre+1,id-1),y=query(1,1,n,id+1,suf-1);
  if(!x && !y){
    sz-=2;
    s.erase(pre);
  }*/
  return;
}

void solve(){
  cin>>n;
  int a[n+1];
  s.clear();
  sz=0;
  build(1,1,n);
  vector<int>ks;
  deque<pair<int,int>>b;
  for(int i=1;i<=n;i++){
    cin>>a[i];
    update(1,1,n,i,1);
    b.push_back({a[i],i});
    ks.push_back(a[i]+1);
  }
  sort(ks.begin(),ks.end());
  sort(b.begin(),b.end());
  ks.erase(unique(ks.begin(),ks.end()),ks.end());
  ll mnans[n+1],mxans[n+1];
  for(int i=1;i<=n;i++){
    mnans[i]=1e18;
    mxans[i]=-1e18;
  }
  for(int sta:ks){
    vector<int>idx;
    while(!b.empty() && b[0].first<sta){
      idx.push_back(b[0].second);
      check(b[0].second);
      b.pop_front();
    }
    vector<pair<int,int>>sem;
    while(!b.empty() && b[0].first==sta){
      sem.push_back(b[0]);
      check(b[0].second);
      b.pop_front();
    }
    for(int id:idx){
      if(s.empty()){
        s.insert(id);
        sz++;
        if(query(1,1,n,1,id-1)) sz++;
        if(query(1,1,n,id+1,n)) sz++;
        continue;
      }
      auto it=s.lower_bound(id);
      if(it==s.end()){
        it--;
        int pre=(*it);
        if(query(1,1,n,pre+1,id-1)){
          sz++;
          s.insert(id);
          if(query(1,1,n,id+1,n)) sz++;
        }
        continue;
      }
      if(it==s.begin()){
        int suf=(*it);
        if(query(1,1,n,id+1,suf-1)){
          sz++;
          s.insert(id);
          if(query(1,1,n,1,id-1)) sz++;
        }
        continue;
      }
      int suf=(*it);
      it--;
      int pre=(*it);
      int x=query(1,1,n,pre+1,id-1),y=query(1,1,n,id+1,suf-1);
      if(!x && !y){
        sz-=2;
        s.erase(pre);
      }else if(x && y){
        sz+=2;
        s.insert(id);
      }
    }
    mnans[sz]=min(mnans[sz],(ll)sta);
    //cout<<sta<<" "<<sz<<endl;
    for(auto x:sem){
      b.push_front(x);
    }
  }
  for(int i=n-1;i>0;i--) mnans[i]=min(mnans[i],mnans[i+1]);
  for(int i=1;i<=n;i++){
    if(mnans[i]==1e18) mnans[i]=-1;
  }
  for(int i=2;i<=n;i++) cout<<mnans[i]<<" ";
  cout<<endl;



  




  s.clear();
  sz=0;
  b.clear();
  ks.clear();
  build(1,1,n);
  for(int i=1;i<=n;i++){
    b.push_back({a[i],i});
    ks.push_back(a[i]-1);
    update(1,1,n,i,1);
  }
  sort(ks.begin(),ks.end());
  sort(b.begin(),b.end());
  ks.erase(unique(ks.begin(),ks.end()),ks.end());
  reverse(ks.begin(),ks.end());
  for(int sta:ks){
    vector<int>idx;
    while(!b.empty() && b.back().first>sta){
      idx.push_back(b.back().second);
      check(b.back().second);
      b.pop_back();
    }
    vector<pair<int,int>>sem;
    while(!b.empty() && b.back().first==sta){
      sem.push_back(b.back());
      check(b.back().second);
      b.pop_back();
    } 
    for(int id:idx){
      if(s.empty()){
        s.insert(id);
        sz++;
        if(query(1,1,n,1,id-1)) sz++;
        if(query(1,1,n,id+1,n)) sz++;
        continue;
      }
      auto it=s.lower_bound(id);
      if(it==s.end()){
        it--;
        int pre=(*it);
        if(query(1,1,n,pre+1,id-1)){
          sz++;
          s.insert(id);
          if(query(1,1,n,id+1,n)) sz++;
        }
        continue;
      }
      if(it==s.begin()){
        int suf=(*it);
        if(query(1,1,n,id+1,suf-1)){
          sz++;
          s.insert(id);
          if(query(1,1,n,1,id-1)) sz++;
        }
        continue;
      }
      int suf=(*it);
      it--;
      int pre=(*it);
      int x=query(1,1,n,pre+1,id-1),y=query(1,1,n,id+1,suf-1);
      if(!x && !y){
        sz-=2;
        s.erase(pre);
      }else if(x && y){
        sz+=2;
        s.insert(id);
      }
    }
    mxans[sz]=max(mxans[sz],(ll)sta);
    //cout<<sta<<" "<<sz<<endl;
    for(auto x:sem){
      b.push_back(x);
    }
  }
  for(int i=n-1;i>0;i--){
    mxans[i]=max(mxans[i+1],mxans[i]);
  }
  for(int i=1;i<=n;i++){
    if(mxans[i]==-1e18) mxans[i]=-1;
  }
  for(int i=2;i<=n;i++) cout<<mxans[i]<<" ";
  cout<<endl;
  return;
}



int main(){
  fastio;

  int t;
  cin>>t;
  while(t--) solve();
}