#include<bits/stdc++.h>
#define ll long long
#define int long long
#define pb push_back

using namespace std;

struct query {
    int x1;
    int x2;
    ll y;
    int ans;
    int pos;
};

struct Point {
    int x;
    int y;
    bool start;
};

bool comp(Point p1, Point p2) {
    return p1.y < p2.y;
}

bool comp2(query q1, query q2) {
    return q1.y < q2.y;
}

bool comp3(query q1, query q2) {
    return q1.pos < q2.pos;
}

void add(vector<int> &tree, int idx, int val) {
    while(idx < tree.size()) {
        tree[idx] += val;
        idx += idx & (-idx);
    }
}

int get(vector<int> &tree, int idx) {
    int result = 0;
    while(idx) {
        result += tree[idx];
        idx -= idx & (-idx);
    }
    return result;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--) {
        int n, q;
        cin>>n>>q;
        vector<ll> y(n+1, 0);
        vector<ll>mapy;
        for(int i=1; i<=n; ++i) {
            cin>>y[i];
            mapy.pb(y[i]);
        }
        vector<query> qr(q);
        for(int i=0; i<q; ++i) {
            cin>>qr[i].x1>>qr[i].x2>>qr[i].y;
            qr[i].pos = i;
            mapy.pb(qr[i].y);
            qr[i].ans = 0;
        }

        sort(mapy.begin(), mapy.end());
        mapy.erase(unique(mapy.begin(), mapy.end()), mapy.end());

        for(int i=1; i<=n; ++i) {
            int p = lower_bound(mapy.begin(), mapy.end(), y[i]) - mapy.begin();
            y[i] = p+1;
        }
        for(int i=0; i<q; ++i) {
            int p = lower_bound(mapy.begin(), mapy.end(), qr[i].y) - mapy.begin();
            qr[i].y = p+1;
        }

        vector<Point> p;
        for(int i=2; i<=n; ++i) {
            Point p1, p2;
            p1.x = i-1;
            p2.x = i-1;
            p1.y = y[i-1];
            p2.y = y[i];
            if(p1.y < p2.y) {
                p1.start = true;
            }
            else
                p1.start = false;
            p2.start = !p1.start;
            p.pb(p1);
            p.pb(p2);
        }
        sort(p.begin(), p.end(), comp);
        sort(qr.begin(), qr.end(), comp2);

        vector<int> active(n+10, 0);
        int i = 0, j = 0;
        for(int cy=0; cy<=mapy.size(); ++cy) {
            int ti = i;
            while(ti < p.size() && p[ti].y <= cy) {
                if(p[ti].start) {
                    add(active, p[ti].x, 1);
                }
                ++ti;
            }
            while(j < qr.size() && qr[j].y <= cy) {
                if(qr[j].y == cy) {
                    int l = get(active, qr[j].x1-1);
                    int r = get(active, qr[j].x2-1);
                    qr[j].ans = r - l;
                }
                ++j;
            }
            while(i < p.size() && p[i].y <= cy) {
                if(!p[i].start) {
                    add(active, p[i].x, -1);
                }
                ++i;
            }
        }

        sort(qr.begin(), qr.end(), comp3);
        for(int i=0; i<q; ++i)
            cout<<qr[i].ans<<endl;
    }  
}
