#include<bits/stdc++.h>
using namespace std;

#define v vector
/*
 *  DSU (0 based indexing)
 *  Usage:
    * Pass N to the constructor
 */
struct DSU
{
    v<int> parent, size;
    DSU(int n) {
        parent.assign(n, 0);
        size.assign(n, 1);
        for(int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    int get(int x) {
        return (parent[x] == x) ? x : parent[x] = get(parent[x]);
    }
    int join(int a, int b) {
        a = get(a);
        b = get(b);
        if(a == b) return 0;
        if(size[a] < size[b]) swap(a, b);
        size[a] += size[b];
        parent[b] = a;
        return 1;
    }
};
