#include <bits/stdc++.h>
using namespace std;
/*
 * Segment Tree (0 based indexing)
 * Point Update and Range Query O(log N)
 * Usage:
    * Pass Size of Array and Neutral Value in the constructor
    * Modify the merge function
 */
template <typename T>
class SegTree
{
private:
    int len;
    vector<T> segtree;
    const T NEUTRAL_VALUE;
    T merge(T a, T b) { return a + b; } // (merge function)
public:
    SegTree(int len, int nv) : len(len), segtree(2 * len), NEUTRAL_VALUE(nv) {}
    void set(int ind, T val)
    {
        for (segtree[ind += len] = val; ind > 1; ind >>= 1)
            segtree[ind >> 1] = merge(segtree[ind], segtree[ind ^ 1]);
    }
    T query(int from, int to) // [from, to]
    {
        ++to;
        auto res = NEUTRAL_VALUE;
        for (from += len, to += len; from < to; from >>= 1, to >>= 1)
        {
            if ((from & 1) != 0)
                res = merge(res, segtree[from++]);
            if ((to & 1) != 0)
                res = merge(res, segtree[--to]);
        }
        return res;
    }
};
