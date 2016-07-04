#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<complex>
#include<set>
#include<assert.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+30;
const ll M = 1e11 + 100;
int vs[maxn] , pri[maxn] , si;

void init(){
    memset(vs,0,sizeof vs);
    si=0;
    for(int i=2;(ll)i*i<M;i++)if(!vs[i]){
        pri[si++] = i;
        for(ll j=(ll)i*i;j<maxn;j+=i)
            vs[j] = 1;
    }
    printf("si %d\n",si);
}

double solve(ll n){

}

int main()
{
//    freopen("in.txt","r",stdin);
    init();
    int T;ll n;
    scanf("%d",&T);
    while(T--){
        scanf("%lld",&n);
        printf("Case #%d: %lf\n",++CASE,solve(n));
    }
    return 0;
}
