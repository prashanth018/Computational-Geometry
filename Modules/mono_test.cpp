#include<bits/stdc++.h>
using namespace std;
int main()
{
    int i,j,k;
    int n;
    vector<int> v;
    v.push_back(6);
    v.push_back(9);
    v.push_back(1);
    v.push_back(4);
    v.push_back(10);
    priority_queue<int> pq(v.begin(),v.end());
    while(!pq.empty())
    {
        cout<<pq.top()<<endl;
        pq.pop();
    }

}
