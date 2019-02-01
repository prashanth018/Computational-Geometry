/** @file PolygonTriangulation.h
    @brief A Library containing the utility and core functions of computational geometry algorithm.
    @author Prashanth Duvvuri
    @version 1.0
    @since 2017-04-08
*/
#include<bits/stdc++.h>
using namespace std;
/** @var vector<pair<int,int> > VL
    @brief a vector which holds vertices.
*/
vector<pair<int,int> > VL;
/** @var vert
    @brief a shortname for datastructure holding vertices.
*/
typedef pair<int,int> vert;
/** @var edge
    @brief a shortname for datastructure holding edges.
*/

typedef pair<vert,vert> edge;
/** @var map<vert,vert> rEL,EL
    @brief rEL is reverse map of edges and EL is forward map of edgelist.
*/
map<vert,vert> rEL,EL;
/**
    @var int before_iter
    @brief value of iterator before triangulation of monotones.
*/
int before_iter;
/**
    @var vector<pair<int,int> > v
    @brief same as VL.
    @see vector<pair<int,int> > VL
*/
vector<pair<int,int> > v;
/**
    @var vector<edge> e
    @brief datastructure to hold edges.
*/
vector<edge> e;
/**
    @var map<vert,int> mp
    @brief a map from vertices to type of vertex it is (split or merge or start or end or regular).
*/
map<vert,int> mp;
/**
    @var map<vert,int> findind
    @brief finds the index corresponding to the vertex.
*/
map<vert,int> findind;
/**
    @var map<edge,vert> helper
    @brief used to hold the helper of an edge(holds a vertex).
*/
map<edge,vert> helper;
/**
    @var map<int,edge> T
    @brief it is a status queue which holds all the edges cut by the sweep line at a particular orientation.
*/
map<int,edge> T;
/**
    A Comparator class. 
    It is used to customize the storage ordering in the priority queue.
*/
class Compare
{
public:
    /**
    A member function taking 2 vertices as input and gives true if y is greater than x else false.
    @param x vertex 1
    @param y vertex 2
    @see operator()
    @return bool
    */
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
// 1 START VERTEX
// 2 END VERTEX
// 3 MERGE VERTEX
// 4 SPLIT VERTEX
// 5 REGULAR VERTEX

/**
A function taking 3 vertices as input and checks if they form a right turn a left turn.
@param x vertex 1
@param y vertex 2
@param z vertex 3
@see check()
@return void
*/

void check(vert x,vert y,vert z)
{
    int x1,y1,x2,y2,x3,y3;
    x1 = x.first;
    y1 = x.second;
    x2 = y.first;
    y2 = y.second;
    x3 = z.first;
    y3 = z.second;
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
/**
A struct.
It is a data structure for storing the details of a Halfedge.
*/
struct HalfEdge
{
    vert origin;    /**< struct value origin */
    edge twin;      /**< struct value twin */
    int left;       /**< struct value left */
    edge next,prev; /**< struct value next,prev */
};
typedef struct HalfEdge hedge;

/**
A DCEL class.
A DataStructure to store topology of a polygon.
*/
class DCEL
{
public:
        map<vert,edge> vertrec;     /** Stores record of vertices. */
        vector<edge> facerec;       /** Stores record of faces. */
        map<edge,hedge> edgerec;    /** Stores record of edges. */
        int counter;                /** Stores value of count of number of faces formed till now. */
public:

/**
@fn vert source(edge e)
@brief A function which returns source of an edge.
@param e edge
@see source()
@return vert
*/
        vert source(edge e)         
        {
            return e.first;
        }
/**
@fn vert target(edge e)
@brief A function which returns destination of an edge.
@param e edge
@see target()
@return vert
*/

        vert target(edge e)
        {
            return e.second;
        }

/**
@fn int face(edge e)
@brief A function which returns face incident on the halfedge.
@param e edge
@see face()
@return int
*/
        int face(edge e)
        {
            hedge h = edgerec[e];
            return h.left;
        }

/**
@fn edge twin(edge e)
@brief A function which returns twin of an edge.
@param e edge
@see twin()
@return edge
*/
        edge twin(edge e)
        {
            hedge h = edgerec[e];
            return h.twin;
        }

/**
@fn edge next_he(edge e)
@brief A function which returns next halfedge of an edge.
@param e 
@see next_he()edge
@return edge
*/
        edge next_he(edge e)
        {
            hedge h = edgerec[e];
            return h.next;
        }

/**
@fn edge he(vert v) 
@brief A function which returns prev halfedge of an edge.
@param e edge
@see he()
@return edge
*/
        edge he(vert v)
        {
            edge e = vertrec[v];
            e = edgerec[e].prev;
            return e;
        }
/**
@fn vector<vert> iterFace(int x)
@brief A function which iterates over a face and returns vertices given the value of face.
@param e edge
@see iterFace()
@return vector<vert>
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
            return vertices;
        }

/**
@fn void MonotoneTriangulation()
@brief A function which Triangulates monotone polygon.
@see MonotoneTriangulation()
@return void
*/
        void MonotoneTriangulation()
        {
            int i,j,k;
            for(i=1;i<=before_iter;i++)
            {
                vector<vert> ver = iterFace(i);
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
                    prev1 = ma;
                    ma = max(ver[j],ma,Compare());
                    if(prev1!=ma)
                        x=j;
                    prev2 = mi;
                    mi = min(ver[j],mi,Compare());
                    if(prev2!=mi)
                        y=j;
                }
                if(x>y)
                {
                    for(j=x;(j)<=y+n;j++)
                    {
                        lr[ver[j%n]]=1;
                    }
                    for(j=y;(j)<=(x);j++)
                    {
                            lr[ver[j%n]]=2;
                    }
                }
                else
                {
                    for(j=x;(j)<=y;j++)
                    {
                        lr[ver[j%n]]=1;
                    }
                    for(j=y;(j)<=(x+n);j++)
                    {
                            lr[ver[j%n]]=2;
                    }
                }
                priority_queue<pair<int,int>,vector<pair<int,int> > , Compare > pq(ver.begin(),ver.end());
                stack<pair<int,int> > s;
                s.push(pq.top());
                pq.pop();
                s.push(pq.top());
                pq.pop();
                vert z;
                while(!pq.empty())
                {
                    z = pq.top();
                    pq.pop();
                    if(pq.empty())
                        {
                            break;
                        }
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
                }
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
            }
        }
/**
@fn void initializeFace()
@brief A function which initializes the facerec of DCEL.
@see initializeFace()
@return void
*/
        void initializeFace()
        {
            int i,j,k;
            counter=1;
            facerec.push_back(make_pair(VL[0],EL[VL[0]]));
            facerec.push_back(make_pair(VL[0],rEL[VL[0]]));
        }

/**
@fn void initializeVert()
@brief A function which initializes the vertrev of DCEL.
@see initializeVert()
@return void
*/     
   void initializeVert()
        {
            int i,j,k;
            for(i=0;i<VL.size();i++)
            {
                vertrec[VL[i]] = make_pair(VL[i],rEL[VL[i]]);
            }
        }

/**
@fn void initializeEdge()
@brief  A function which initializes the edgerec of DCEL.
@see initializeEdge()
@return void
*/   
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

/**
@fn void printEdge()
@brief A function which prints the edgerec of DCEL.
@see printEdge()
@return void
*/
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
                cout<<"("<<it->second.twin.second.first<<","<<it->second.twin.second.second<<")"<<"\t";
                cout<<it->second.left<<"\t";
                cout<<"("<<it->second.next.first.first<<","<<it->second.next.first.second<<")"<<"---->";
                cout<<"("<<it->second.next.second.first<<","<<it->second.next.second.second<<")"<<"\t";
                cout<<"("<<it->second.prev.first.first<<","<<it->second.prev.first.second<<")"<<"---->";
                cout<<"("<<it->second.prev.second.first<<","<<it->second.prev.second.second<<")"<<"\t";
                cout<<endl;
            }
        }
/**
@fn void printFace()
@brief A function which prints the facerec of DCEL.
@see printFace()
@return void
*/
        void printFace()
        {
            int i;
            cout<<"Printing Face Record"<<endl;
            for(i=0;i<facerec.size();i++)
            {
                cout<<"("<<facerec[i].first.first<<","<<facerec[i].first.second<<")"<<"---->";
                cout<<"("<<facerec[i].second.first<<","<<facerec[i].second.second<<")"<<"\n";
            }
        }

/**
@fn void printVert()
@brief A function which prints the vertrec of DCEL.
@see printVert()
@return void
*/
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
            }
        }

/**
@fn void addEdge(vert u,vert v)
@brief A function which takes 2 vertices as input and adds the halfedges in the DCEL.
@param u vertex 1
@param v vertex 2
@see addEdge()
@return void
*/
        void addEdge(vert u,vert v)
        {
            edge h = vertrec[u];
            h = edgerec[h].prev;
            hedge h1,h2;
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

