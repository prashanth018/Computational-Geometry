#include<bits/stdc++.h>
using namespace std;

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
/*
bool compare(pair<int,int> x,pair<int,int> y)
{

}*/
int  main()
{
    int i,j,k;
    int n;
    pair<int,int> x,y;
    priority_queue<pair<int,int>,vector<pair<int,int> > , Compare > pq;
    priority_queue<int> p;
    pq.push(make_pair(2,1));
    pq.push(make_pair(3,1));
    pq.push(make_pair(2,5));
    x = pq.top();
    cout<<x.first<<" "<<x.second<<endl;
    pq.pop();
    x = pq.top();
    cout<<x.first<<" "<<x.second<<endl;
    pq.pop();
    x = pq.top();
    cout<<x.first<<" "<<x.second<<endl;
    pq.pop();
}
