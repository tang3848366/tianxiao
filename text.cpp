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
#include<bitset>
using namespace std;
#define MAXN 300
int equ,var;
int a[MAXN][MAXN];
int d[MAXN];
int free_d[MAXN];
int free_num;
int Gause()
{
    int max_r,col,k;
    free_num=0;
    for(k=0,col=0;k<equ&&col<var;k++,col++)
    {
        max_r=k;
        for(int i=k+1;i<equ;i++)
            if( abs(a[i][col]) > abs(a[max_r][col]))
                max_r=i;
        if(a[max_r][col] == 0)
        {
            k--;
            free_d[free_num++] =col;
            continue;
        }
        if(max_r != k)
        {
            for(int j=col;j<var+1;j++)
                swap(a[k][j],a[max_r][j]);
        }
        for(int i=k+1;i<equ;i++)
        {
            if(a[i][col]!=0)
            {
                for(int j=col;j<var+1;j++)
                    a[i][j]^=a[k][j];
            }
        }
    }
    for(int i=k;i<equ;i++)
        if(a[i][col]!=0)
            return -1;
    if(k<var) return var-k;
    for(int i=var-1;i>=0;i--)
    {
        d[i]=a[i][var];
        for(int j=i+1;j<var;j++)
            d[i]^=(a[i][j] && d[j]);
    }
    return 0;
}
int x[MAXN],y[MAXN];
int main()
{
    freopen("in.txt","r",stdin);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&x[i]);
        for(int i=0;i<n;i++)
            scanf("%d",&y[i]);
        int p,q;
        memset(a,0,sizeof a);
        while(~scanf("%d%d",&p,&q))
        {
            if(p==0&&q==0)
                break;
           a[q-1][p-1]=1;
        }
        for(int i=0;i<n;i++)
            a[i][i]=1,a[i][n]=(x[i]^y[i]);
        equ=var=n;
        int res=Gause();
        if(res<0)printf("Oh,it's impossible~!!\n");
        else{
            printf("%d\n",1<<res);
        }
    }
}
