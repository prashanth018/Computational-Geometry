#include "PolygonTriangulation.h"
int main()
{
    int i,j,k;
    ifstream infile("inp.txt");
    int n;
    infile>>n;
    int x,y;
    int a,b;
    pair<int,int> p,q;
    priority_queue<pair<int,int>,vector<pair<int,int> > , Compare > pq;
    for(i=0;i<n;i++)
    {
        infile>>x>>y;
        v.push_back(make_pair(x,y));
        pq.push(make_pair(x,y));
        VL.push_back(make_pair(x,y));
        if(i>0)
        {
            EL[VL[i]] = VL[i-1];
            rEL[VL[i-1]] = VL[i];
            e.push_back(make_pair(v[i-1],v[i]));
        }
        findind[v[i]]=i;
    }
    rEL[VL[n-1]] = VL[0];
    EL[VL[0]] = VL[n-1];
    e.push_back(make_pair(v[n-1],v[0]));

    DCEL d;
    d.initializeFace();
    d.initializeEdge();
    d.initializeVert();

    //UNCOMMENT THE BELOW LINES TO SEE THE DCEL PRIOR TO THE EXECUTION
    //d.printEdge();
    //d.printVert();
    //d.printFace();

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
                d.addEdge(v[i],helper[e[i-1]]);
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
            d.addEdge(v[i],helper[z]);
            T[v[i].first] = e[i];
            helper[e[i]] = v[i];
        }
        else if(mp[a]==3)
        {
            int i = findind[a];
            if(mp[helper[e[i-1]]]==3)
            {
                //insert into DCEL diag from vi to helper(e i-1)
                d.addEdge(v[i],helper[e[i-1]]);
                T.erase(e[i-1].first.first);
            }
            int xval = a.first;
            map<int,edge>::iterator it;
            it = T.upper_bound(a.first);
            it--;
            edge z = it->second;
            if(mp[helper[z]]==3)
            {
                //insert helper[z] to vi
                d.addEdge(v[i],helper[z]);
            }
            helper[z] = v[i];
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
                    d.addEdge(v[i],helper[e[i-1]]);
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
                        d.addEdge(a,helper[z]);
                        //insert diag a to helper[z]
                        helper[z] = a;
                    }
                }
            }
        }
    }
    before_iter = d.counter;
    d.MonotoneTriangulation();

    //UNCOMMENT THE BELOW LINES OF CODE TO SEE THE DCEL CONTENT AFTER THE MONOTONEPARTITION AND TRIANGULATION.
    d.printEdge();
    d.printVert();
    d.printFace();
    return 0;
}

