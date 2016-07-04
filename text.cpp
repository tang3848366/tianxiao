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
typedef complex<double> point;
double eps=1e-10;
const double PI=acos(-1.0);
double det(point a,point b){return (conj(a)*b).imag();}
double dot(point a,point b){return (a*conj(b)).real();}
inline int sgn(double n){return abs(n)<eps?0:(n<0?-1:1);}
int cross(point s,point a,point b)
{
    point u=a-s;
    point v=b-s;
    if(sgn(det(u,v))>0) return 1;
    if(sgn(det(u,v))<0) return -1;
    if(sgn(dot(u,v))<=0) return 0;
    if(sgn(abs(u)-abs(v))>0) return 2;
    return -2;
}
double Ang;
point O=point(0,0);
struct line: public vector<point>
{
    double k;
    line(){}
    line(point a,point b){
        push_back(a),push_back(b);
        k=atan2((b-a).imag(),(b-a).real());
    }
};
point vec(line a){return a[1]-a[0];}
point vec(point a){return a/abs(a);}
point InterLL(const line u,const line v)
{
    double a=det(vec(u),vec(v));
    double b=det(vec(u),u[1]-v[0]);
    if(sgn(a)==0) return v[0];
    point temp=v[0]+(b/a)*vec(v);
//    cout<<temp.real()<<" "<<temp.imag()<<endl;
    return v[0]+b/a*vec(v);
}
bool operator < (const line& a,const line& b)
{
    line t=line(O,point(cos(Ang),sin(Ang)));
    return sgn(  abs(InterLL(t,a) ) - abs(InterLL(t,b) ) )<0;
}
bool operator == (const line& a,const line& b)
{
    line t=line(O,point(cos(Ang),sin(Ang)));
    return sgn(  abs(InterLL(t,a) ) - abs(InterLL(t,b) ) )==0;
}
int S,W,K;
#define MAXN 101000
point kid[MAXN];
line wall[MAXN];
line seg[2*MAXN];
struct node{
    int id,kind;
    double ang;
    node(int _id=0,int _kind=0,double _ang=0):id(_id),kind(_kind),ang(_ang){}
    bool operator <(const node &a)const{
        if(sgn(ang-a.ang)!=0)
            return ang<a.ang;
        return kind < a.kind;
    }
}event[5*MAXN];
double getAng(point a){ return atan2(a.imag(),a.real());}
int num;
set<line> q;
int solve()
{
    int ret=0;
    num=0;
    for(int i=1;i<K;i++)
    {
        event[num++]=node(i,1,getAng(kid[i]-kid[0]));
    }
    for(int i=0;i<W;i++)
    {
        seg[i]=line(wall[i][0]-kid[0],wall[i][1]-kid[0]);
        if(getAng(seg[i][0])>getAng(seg[i][1]))
            swap(seg[i][0],seg[i][1]);
        int flag=1;
        point t;
        if(sgn(det(vec(seg[i]),point(-1,0)))!=0)
        {
            t=InterLL(seg[i],line(O,point(-1,0)));
            if(sgn(abs(getAng(seg[i][0])-getAng(seg[i][1]))-PI)>0)
                flag=0;
        }
        if(flag)
        {
            event[num++]=node(i,0,getAng(seg[i][0]));
            event[num++]=node(i,2,getAng(seg[i][1]));
        }
        else{
            event[num++]=node(i,0,-PI);
            event[num++]=node(i,2,getAng(seg[i][0]));
            event[num++]=node(i,0,getAng(seg[i][1]));
            event[num++]=node(i,2,PI);
        }
    }
    sort(event,event+num);
    q.clear();
    for(int i=0;i<num;i++)
    {
        Ang=event[i].ang;
        if(event[i].kind==1)
        {
            if(q.empty() || sgn(  abs( InterLL(line(O,point(cos(Ang),sin(Ang))),*q.begin() ) )- abs(kid[event[i].id]-kid[0]) )>0 )
                ret++;
        }
        else{
            if(event[i].kind==0)
                q.insert(seg[event[i].id]);
            else {
                q.erase(seg[event[i].id]);
            }
        }
    }
    return ret;
}

int main()
{
    freopen("in.txt","r",stdin);
    while(~scanf("%d%d%d",&S,&K,&W))
    {
        for(int i=0;i<K;i++)
        {
            double x,y;
            scanf("%lf%lf",&x,&y);
            kid[i]=point(x,y);
        }
        for(int i=0;i<W;i++)
        {
            double x1,y1,x2,y2;
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            wall[i]=line(point(x1,y1),point(x2,y2));
        }
        for(int i=0;i<S;i++)
        {
            swap(kid[0],kid[i]);
            printf("%d\n",solve());
        }
    }
    return 0;
}
