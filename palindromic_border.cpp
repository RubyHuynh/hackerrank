#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N=1e5+5,mo=1e9+7,Inv=500000004;
typedef long long LL;
int n,m,Last,e[N][8],Fail[N],Len[N],Cnt[N],ans,tot;
char S[N];
int getfail(int x)
{
    for (;S[m-Len[x]-1]!=S[m];x=Fail[x]);
    return x;
}
void Add(int x)
{
    Last=getfail(Last);
    if (e[Last][x]==0)
    {
        Len[++tot]=Len[Last]+2;
        Fail[tot]=e[getfail(Fail[Last])][x];
        e[Last][x]=tot;
    }
    Last=e[Last][x];
    Cnt[Last]++;
}
int main()
{
    scanf("%s",S+1);
    n=strlen(S+1);
    Len[1]=-1; Fail[0]=1; tot=1; Last=0;
    for (m=1;m<=n;m++) Add(S[m]-'a');
    m=0;
    ans=0;
    for (int i=tot;i>1;i--)
    {
        Cnt[Fail[i]]+=Cnt[i];
        ans=(ans+(LL)Cnt[i]*(Cnt[i]-1)%mo*Inv%mo)%mo;
    }
    printf("%d\n",ans);
    return 0;
}
