#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int> > VL;
typedef pair<int,int> vert;
typedef pair<vert,vert> edge;
map<vert,vert> rEL,EL;
//struct Face
//{
//    vector<vert> v;
//};
//typedef struct Face face;
int before_iter;
struct HalfEdge
{
    vert origin;
    edge twin;
    int left;
    edge next,prev;
};
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
        void initializeFace()
        {
            int i,j,k;
            counter=1;
            facerec.push_back(make_pair(VL[0],EL[VL[0]]));
            facerec.push_back(make_pair(VL[0],rEL[VL[0]]));
            counter++;
        }
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
            for(i=1;i<counter;i++)
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
                for(j=0;j<ver.size();j++)
                {
                    /*if(ver[j]>ma)
                    {
                        ma = ver[j];
                        x=j;
                    }
                    else if(ver[j]<mi)
                    {
                        mi = ver[j];
                        y=j;
                    }*/
                    prev1 = ma;
                    ma = max(ver[j],ma,Compare());
                    if(prev1!=ma)
                        x=j;
                    prev2 = mi;
                    mi = min(ver[j],mi,Compare());
                    if(prev2!=mi)
                        y=j;
                }
                cout<<"@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
                cout<<x<<" "<<y<<endl;
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
                cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                cout<<ver[x].first<<" "<<ver[x].second<<endl;
                cout<<ver[y].first<<" "<<ver[y].second<<endl;
                /*
                else if(ver[(x+1)%n].first > ver[x].first)
                {
                    for(j=y;j<=x;j++)
                    {
                        lr[ver[j]]=1;
                    }
                    //sort(lc.begin(),lc.end());
                    for(j=0;j<ver.size();j++)
                    {
                        if(j<=y || j>=x)
                            lr[ver[j]]=2;
                    }
                    //sort(rc.begin(),rc.end());
                }
                */
                priority_queue<pair<int,int>,vector<pair<int,int> > , Compare > pq(ver.begin(),ver.end());
                //while(!pq.empty())
                //{
                //    cout<<pq.top().first<<" "<<pq.top().second<<" "<<lr[pq.top()]<<endl;
                //    pq.pop();
                //}
                //return;
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
                        break;
                    if(lr[s.top()]!=lr[z])
                    {
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
                while(!s.empty())
                {
                    cout<<s.top().first<<" "<<s.top().second<<endl;
                    s.pop();
                }
                return;

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
                edgerec[it].left = counter;
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
    i=0;
    int n;
    cin>>n;
    int x,y;
    for(i=0;i<n;i++)
    {
        cin>>x>>y;
        VL.push_back(make_pair(x,y));
        if(i>0)
        {
            EL[VL[i]] = VL[i-1];
            rEL[VL[i-1]] = VL[i];
        }
    }
    rEL[VL[n-1]] = VL[0];
    EL[VL[0]] = VL[n-1];
    DCEL d;
    d.initializeFace();
    d.initializeEdge();
    d.initializeVert();
    d.printEdge();
    d.printVert();
    d.printFace();
    before_iter = d.counter;
    d.MonotoneTriangulation();


    //d.printEdge();
    //d.printVert();
    //d.printFace();

    //vert u,v;
    //u = make_pair(2,2);
    //v = make_pair(0,0);
    //d.addEdge(u,v);













    cout<<"********************************"<<endl;
    d.printEdge();
    d.printVert();
    d.printFace();
    //d.initialize
}
