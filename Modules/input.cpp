#include<bits/stdc++.h>
using namespace std;
int main()
{
    int i,j,k;
    ifstream infile("inp.txt");
    int n;
    infile>>n;
    int a,b;
    vector<pair<int,int> > v;
    while(infile>>a>>b)
    {
        v.push_back(make_pair(a,b));
    }
    cout<<n<<endl;
    for(i=0;i<v.size();i++)
    {
        cout<<v[i].first<<" "<<v[i].second<<endl;
    }
}
