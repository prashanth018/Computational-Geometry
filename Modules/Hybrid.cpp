#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int> > VL;
typedef pair<int,int> vert;
typedef pair<vert,vert> edge;
map<vert,vert> rEL,EL;
int before_iter;
//struct Face
//{
//    vector<vert> v;
//};
//typedef struct Face face;
vector<pair<int,int> > v;
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
    else if(y.second <= x.second && y.second <= z.second)
    {
        if((y2 - y1)*(x3 - x2) - (y3 - y2)*(x2 - x1) > 0)
            mp[y] = 3;
        else
            mp[y] = 2;
    }
}
struct HalfEdge
{
    vert origin;
    edge twin;
    int left;
    edge next,prev;
};
typedef struct HalfEdge hedge;
class DCEL
{
public:
        map<vert,edge> vertrec;
        vector<edge> facerec;
        map<edge,hedge> edgerec;
        int counter;
public:
        vert source(edge e)
        {
            return e.first;
        }
        vert target(edge e)
        {
            return e.second;
        }
        int face(edge e)
        {
            hedge h = edgerec[e];
            return h.left;
        }
        edge twin(edge e)
        {
            hedge h = edgerec[e];
            return h.twin;
        }
        edge next_he(edge e)
        {
            hedge h = edgerec[e];
            return h.next;
        }
        edge he(vert v)
        {
            edge e = vertrec[v];
            e = edgerec[e].prev;
            return e;
        }
/*
        void addvert(vert v)
        {
            map<vert,vert>::iterator it;
            it = EL.begin()
            for(;it!=EL.end();it++)
            {
                vert a,b;
                a = it->first;
                b = it->second;
                if(slope(a,b,v))
                {
                    edge p,q,pq;
                    pq = make_pair(a,b);
                    p = make_pair(a,v);
                    q = make_pair(v,b);
                    vertrec[v] = q;
                    hedge hp,hq;
                    hq.origin = v;
                    hq.next = edgerec[pq].next;
                    hq.prev = p;
                    edgerec[q] =
                }
            }
        }
*/
        vector<vert> iterFace(int x)
        {
            edge e,st;
            e = facerec[x];
            st=e;
            vector<vert> vertices;
            vertices.push_back(e.first);
            e = edgerec[e].next;
            while(e!=st)
            {
                vertices.push_back(e.first);
                e = edgerec[e].next;
            }
            int i;
            //for(i=0;i<vertices.size();i++)
            //    cout<<vertices[i].first<<" "<<vertices[i].second<<endl;
            return vertices;
        }
        void MonotoneTriangulation()
        {
            int i,j,k;
            //cout<<counter<<endl;
            //cout<<"val of bf_it "<<before_iter<<endl;
            for(i=1;i<=before_iter;i++)
            {
                vector<vert> ver = iterFace(i);
                //vector<vert> lc,rc;
                map<vert,int> lr;
                vert ma;
                ma.first=0;
                ma.second=0;
                vert mi;
                mi.first=10000000;
                mi.second=10000000;
                int x,y;
                int n = ver.size();
                vert prev1,prev2;
                //cout<<ver.size()<<endl;
                for(j=0;j<ver.size();j++)
                {
                    prev1 = ma;
                    ma = max(ver[j],ma,Compare());
                    if(prev1!=ma)
                        x=j;
                    prev2 = mi;
                    mi = min(ver[j],mi,Compare());
                    if(prev2!=mi)
                        y=j;
                }
                //cout<<"@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
                //cout<<x<<" "<<y<<endl;
                if(x>y)
                {
                    for(j=x;(j)<=y+n;j++)
                    {
                        lr[ver[j%n]]=1;
                    }
                    //sort(lc.begin(),lc.end());
                    for(j=y;(j)<=(x);j++)
                    {
                        //if(j<=x || j>=y)
                            lr[ver[j%n]]=2;
                    }
                    //sort(rc.begin(),rc.end());
                }
                else
                {
                    for(j=x;(j)<=y;j++)
                    {
                        lr[ver[j%n]]=1;
                    }
                    //sort(lc.begin(),lc.end());
                    for(j=y;(j)<=(x+n);j++)
                    {
                        //if(j<=x || j>=y)
                            lr[ver[j%n]]=2;
                    }
                }
                //cout<<ver[x].first<<" "<<ver[x].second<<endl;
                //cout<<ver[y].first<<" "<<ver[y].second<<endl;
                priority_queue<pair<int,int>,vector<pair<int,int> > , Compare > pq(ver.begin(),ver.end());
                stack<pair<int,int> > s;
                s.push(pq.top());
                pq.pop();
                s.push(pq.top());
                pq.pop();
                vert z;
                while(!pq.empty())
                {
                    //cout<<"hey"<<endl;
                    z = pq.top();
                    pq.pop();
                    if(pq.empty())
                        {
                            //cout<<"executed"<<endl;
                            break;
                        }
                    if(lr[s.top()]!=lr[z])
                    {
                        //cout<<"heyya"<<endl;
                        stack<vert> rev;
                        while(!s.empty())
                        {
                            rev.push(s.top());
                            s.pop();
                        }
                        vert p = rev.top();
                        rev.pop();
                        while(!rev.empty())
                        {
                            p = rev.top();
                            rev.pop();
                            //cout<<"This is rev.pop() "<<p.first<<" "<<p.second<<endl;
                            addEdge(p,z);
                        }
                        s.push(p);
                        s.push(z);
                    }
                    else
                    {
                        vert p = s.top();
                        s.pop();
                        if(lr[p]==1)
                        {
                            while(!s.empty())
                            {
                                p = s.top();
                                s.pop();
                                int x1,y1,x2,y2,x3,y3;
                                if(!s.empty())
                                {   x1 = s.top().first;
                                    y1 = s.top().second;
                                }
                                else
                                    break;
                                x2 = p.first;
                                y2 = p.second;
                                x3 = z.first;
                                y3 = z.second;

                                if((y2 - y1)*(x3 - x2) - (y3 - y2)*(x2 - x1) > 0)
                                {
                                    break;
                                }
                                addEdge(p,z);
                            }
                            s.push(p);
                            s.push(z);
                        }
                        else
                        {
                            while(!s.empty())
                            {
                                p = s.top();
                                s.pop();
                                int x1,y1,x2,y2,x3,y3;
                                if(!s.empty())
                                {   x1 = s.top().first;
                                    y1 = s.top().second;
                                }
                                else
                                    break;
                                x2 = p.first;
                                y2 = p.second;
                                x3 = z.first;
                                y3 = z.second;

                                if((y2 - y1)*(x3 - x2) - (y3 - y2)*(x2 - x1) > 0)
                                {
                                    break;
                                }
                                addEdge(p,z);
                            }
                            s.push(p);
                            s.push(z);
                        }
                    }
                    //printFace();
                }

                //while(!s.empty())
                //{
                    //cout<<s.top().first<<" "<<s.top().second<<endl;
                //    s.pop();
                //}
                //return;
                //cout<<"first = "<<z.first<<" second = "<<z.second<<endl;
                stack<vert> rev;
                s.pop();

                while(!s.empty())
                {
                    rev.push(s.top());
                    s.pop();
                }
                rev.pop();
                while(!rev.empty())
                {
                    addEdge(rev.top(),z);
                    rev.pop();
                }
                //sort(ver.begin(),ver.end());
            }
        }
        void initializeFace()
        {
            int i,j,k;
            counter=1;
            facerec.push_back(make_pair(VL[0],EL[VL[0]]));
            facerec.push_back(make_pair(VL[0],rEL[VL[0]]));
            //counter++;
        }
        void initializeVert()
        {
            int i,j,k;
            for(i=0;i<VL.size();i++)
            {
                vertrec[VL[i]] = make_pair(VL[i],rEL[VL[i]]);
            }
        }
        void initializeEdge()
        {
            int i,j,k;
            vert x,y;
            for(i=0;i<VL.size();i++)
            {
                x = VL[i];
                y = EL[VL[i]];
                edge ed = make_pair(x,y);
                hedge h;
                h.origin = VL[i];
                h.twin = make_pair(y,x);
                h.left = 0;
                h.next = make_pair(EL[VL[i]],EL[EL[VL[i]]]);
                h.prev = make_pair(rEL[VL[i]],VL[i]);
                edgerec[ed] = h;
            }
            for(i=0;i<VL.size();i++)
            {
                x = VL[i];
                y = rEL[VL[i]];
                edge ed = make_pair(x,y);
                hedge h;
                h.origin = VL[i];
                h.twin = make_pair(y,x);
                h.left = 1;
                h.next = make_pair(rEL[VL[i]],rEL[rEL[VL[i]]]);
                h.prev = make_pair(EL[VL[i]],VL[i]);
                edgerec[ed] = h;
            }
        }
        void printEdge()
        {
            int i,j,k;
            cout<<"Printing Edge Record"<<endl;
            map<edge,hedge>::iterator it;
            for(it=edgerec.begin();it!=edgerec.end();it++)
            {
                cout<<"("<<it->first.first.first<<","<<it->first.first.second<<")"<<"---->";
                cout<<"("<<it->first.second.first<<","<<it->first.second.second<<")"<<"\t";
                cout<<"("<<it->second.origin.first<<","<<it->second.origin.second<<")"<<"\t";
                cout<<"("<<it->second.twin.first.first<<","<<it->second.twin.first.second<<")"<<"---->";
                //cout<<"("<<it->second.origin.first<<" "<<it->second.origin.second<<")"<<"\t";
                cout<<"("<<it->second.twin.second.first<<","<<it->second.twin.second.second<<")"<<"\t";
                cout<<it->second.left<<"\t";
                cout<<"("<<it->second.next.first.first<<","<<it->second.next.first.second<<")"<<"---->";
                //cout<<"("<<it->second.origin.first<<" "<<it->second.origin.second<<")"<<"\t";
                cout<<"("<<it->second.next.second.first<<","<<it->second.next.second.second<<")"<<"\t";
                cout<<"("<<it->second.prev.first.first<<","<<it->second.prev.first.second<<")"<<"---->";
                //cout<<"("<<it->second.origin.first<<" "<<it->second.origin.second<<")"<<"\t";
                cout<<"("<<it->second.prev.second.first<<","<<it->second.prev.second.second<<")"<<"\t";
                cout<<endl;
            }
        }
        void printFace()
        {
            int i;
            cout<<"Printing Face Record"<<endl;
            for(i=0;i<facerec.size();i++)
            {
                cout<<"("<<facerec[i].first.first<<","<<facerec[i].first.second<<")"<<"---->";
                cout<<"("<<facerec[i].second.first<<","<<facerec[i].second.second<<")"<<"\n";
                //facerec[i].first.first
            }
        }
        void printVert()
        {
            int i,j,k;
            cout<<"Printing Vertex Record"<<endl;
            map<vert,edge>::iterator it;
            for(it=vertrec.begin();it!=vertrec.end();it++)
            {
                cout<<"("<<it->first.first<<","<<it->first.second<<")"<<"\t";
                cout<<"("<<it->second.first.first<<","<<it->second.first.second<<")"<<"---->";
                cout<<"("<<it->second.second.first<<","<<it->second.second.second<<")"<<"\n";
                //cout<<endl;
            }
        }
        //void addEdge()
        //{
        //    edge h1 =
        //}
        //void addEdge();
        void addEdge(vert u,vert v)
        {
            //hedge h = edgerec[edge];
            edge h = vertrec[u];
            h = edgerec[h].prev;
            hedge h1,h2;
            //h1.second = v;
            edge e1,e2;
            e1 = make_pair(u,v);
            e2 = make_pair(v,u);
            edgerec[h].next = e1;
            edgerec[e1].origin = u;
            edgerec[e1].twin = e2;
            edgerec[e2].twin = e1;
            edgerec[e2].origin = v;
            edgerec[e1].prev = h;
            edgerec[e1].next = vertrec[v];
            edge k = edgerec[vertrec[v]].prev;
            edgerec[vertrec[v]].prev = e1;
            edgerec[e1].left = edgerec[edgerec[e1].next].left;
            edgerec[e2].next = vertrec[u];
            edgerec[e2].prev = k;
            edgerec[k].next = e2;
            edgerec[vertrec[u]].prev = e2;

            edge it=e2;
            do
            {
                edgerec[it].left = counter+1;
                it = edgerec[it].next;
            }
            while(it!=e2);
            facerec[edgerec[e1].left] = e1;
            facerec.push_back(e2);
            vertrec[u] = e1;
            vertrec[v] = e2;
            counter++;
        }
};

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
        //cin>>x>>y;
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
    d.printEdge();
    d.printVert();
    d.printFace();

    for(i=0;i<v.size();i++)
    {
        if(i==0)
            check(v[n-1],v[0],v[1]);
        else if(i==n-1)
            check(v[n-2],v[n-1],v[0]);
        else
            check(v[i-1],v[i],v[i+1]);
    }
    //for(i=0;i<v.size();i++)
    //    cout<<v[i].first<<" "<<v[i].second<<"     "<<mp[v[i]]<<endl;
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
            //cout<<"ehy"<<endl;
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
    //cout<<"********************************"<<endl;

    //d.printEdge();
    //d.printVert();
    //d.printFace();
    before_iter = d.counter;
    d.MonotoneTriangulation();
    cout<<"********************************"<<endl;
    d.printEdge();
    d.printVert();
    d.printFace();
    return 0;
}

