#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> vert;
typedef pair<vert,vert> edge;

int  main()
{
    int i,j,k;
    int n;
    pair<int,int> x,y;
    map<int,edge> mp;
    mp[1] = make_pair(make_pair(1,3),make_pair(4,5));
    mp[3] = make_pair(make_pair(3,4),make_pair(8,2));
    mp[6] = make_pair(make_pair(6,8),make_pair(5,5));
    mp[7] = make_pair(make_pair(7,3),make_pair(4,5));
    map<int,edge>::iterator it;
    it = mp.upper_bound(4);
    it--;
    cout<<it->first<<" ("<<it->second.first.first<<","<<it->second.first.second<<") "<<"("<<it->second.second.first<<","<<it->second.second.second<<")"<<endl;
    //using key_type = pair<int, edge>;
    //set<pair<int, edge> > s;
    //s.insert(make_pair(1,make_pair(make_pair(1,3),make_pair(4,5) ) ));
    //s.insert(3,5)
    //s.insert(make_pair(3,make_pair(make_pair(3,4),make_pair(8,2))));
    //s.insert(make_pair(6,make_pair(make_pair(6,8),make_pair(5,5))));
    //s.insert(make_pair(7,make_pair(make_pair(7,3),make_pair(4,5))));
    //set<pair<int,edge> >::iterator pos;
    //pos = std::find_if(s.end(), s.begin(),[5](std::pair<int, edge> const &b) {
     //                       return b.first<5;
     //                   });
    //it = s.lower_bound(make_pair(3,make_pair(make_pair(0,0),make_pair(0,0))));
    //it = s.upper_bound (key_type (5, std::numeric_limits<edge>::min ()));
    //while(it!=s.begin())
    //{
        //cout<<it->first<<" ("<<it->second.first.first<<","<<it->second.first.second<<") "<<"("<<it->second.second.first<<","<<it->second.second.second<<")"<<endl;
    //    it--;
    //}



}
