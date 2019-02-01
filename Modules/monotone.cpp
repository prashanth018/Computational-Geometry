#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int> > v;
typedef pair<int,int> vert;
typedef pair<vert,vert> edge;
vector<edge> e;
map<vert,int> mp;
map<vert,int> findind;
map<edge,vert> helper;
map<int,edge> T;
class Compare
{
public:
    bool operator() (pair<int,int> x,pair<int,int> y)
    {
        if(x.second<y.second)
            return true;
        else if(x.second==y.second)
        {
            if(x.first>y.first)
                return true;
        }
        return false;
    }
};

void check(vert x,vert y,vert z)
{
    int x1,y1,x2,y2,x3,y3;
    x1 = x.first;
    y1 = x.second;
    x2 = y.first;
    y2 = y.second;
    x3 = z.first;
    y3 = z.second;
    // 1 START VERTEX
    // 2 END VERTEX
    // 3 MERGE VERTEX
    // 4 SPLIT VERTEX
    // 5 REGULAR VERTEX
    if((y.second > x.second && z.second > y.second) || (y.second < x.second && z.second < y.second))
        mp[y]=5;
    else if(y.second >= x.second && y.second >= z.second )
    {
        if((y2 - y1)*(x3 - x2) - (y3 - y2)*(x2 - x1) < 0)
            mp[y] = 1;
        else
            mp[y] = 4;
    }
    else if(y.second < x.second && y.second < z.second)
    {
        if((y2 - y1)*(x3 - x2) - (y3 - y2)*(x2 - x1) > 0)
            mp[y] = 3;
        else
            mp[y] = 2;
    }
}
int main()
{
    int i,j,k;
    int n;
    cin>>n;
    int x,y;
    pair<int,int> p,q;
    priority_queue<pair<int,int>,vector<pair<int,int> > , Compare > pq;
    for(i=0;i<n;i++)
    {
        cin>>x>>y;
        v.push_back(make_pair(x,y));
        pq.push(make_pair(x,y));
        if(i>0)
        {
            e.push_back(make_pair(v[i-1],v[i]));
        }
        findind[v[i]]=i;
    }
    e.push_back(make_pair(v[n-1],v[0]));
    for(i=0;i<v.size();i++)
    {
        if(i==0)
            check(v[n-1],v[0],v[1]);
        else if(i==n-1)
            check(v[n-2],v[n-1],v[0]);
        else
            check(v[i-1],v[i],v[i+1]);
    }
    while(!pq.empty())
    {
        vert a = pq.top();
        pq.pop();
        if(mp[a]==1)
        {
            int i = findind[a];
            T[v[i].first] = e[i];
            helper[e[i]] = v[i];
        }
        else if(mp[a]==2)
        {
            int i = findind[a];
            if(mp[helper[e[i-1]]]==3)
            {
                //insert into DCEL diag from vi to helper(e i-1)
            }
            T.erase(e[i-1].first.first);
        }
        else if(mp[a]==4)
        {
            int i = findind[a];
            int xval = a.first;
            map<int,edge>::iterator it;
            it = T.upper_bound(a.first);
            it--;
            edge z = it->second;
            //insert into DCEL diag from vi to helper(z)
            T[v[i].first] = e[i];
            helper[e[i]] = v[i];
        }
        else if(mp[a]==3)
        {
            int i = findind[a];
            if(mp[helper[e[i-1]]]==3)
            {
                //insert into DCEL diag from vi to helper(e i-1)
                T.erase(e[i-1].first.first);
                int xval = a.first;
                map<int,edge>::iterator it;
                it = T.upper_bound(a.first);
                it--;
                edge z = it->second;
                if(mp[helper[z]]==3)
                {
                    //insert helper[z] to vi
                    helper[z] = v[i];
                }
            }
        }
        else if(mp[a]==5)
        {
            int i = findind[a];
            int xval = a.first;
            map<int,edge>::iterator it = T.end();
            it--;
            if(T.find(v[i].first)!=it)
            {
                if(mp[helper[e[i-1]]]==3)
                {
                    //insert diag from vi to e i-1
                    T.erase(e[i-1].first.first);
                    T[v[i].first] = e[i];
                    helper[e[i]] = v[i];
                }
                else
                {
                    map<int,edge>::iterator it;
                    it = T.upper_bound(a.first);
                    it--;
                    edge z = it->second;
                    if(mp[helper[z]]==3)
                    {
                        //insert diag a to helper[z]
                    }
                    helper[z] = a;
                }
            }
        }
    }
}
