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
        void initializeFace()
        {
            int i,j,k;
            counter=1;
            facerec.push_back(make_pair(VL[0],EL[VL[0]]));
            facerec.push_back(make_pair(VL[0],rEL[VL[0]]));
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
            //cout<<"hey"<<endl;
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
    vert u,v;
    u = make_pair(0,4);
    v = make_pair(4,4);
    d.addEdge(u,v);
    u = make_pair(4,4);
    v = make_pair(0,2);
    d.addEdge(u,v);
    u = make_pair(0,2);
    v = make_pair(4,2);
    d.addEdge(v,u);

    cout<<"********************************"<<endl;
    d.printEdge();
    d.printVert();
    d.printFace();
    //d.initialize
}
