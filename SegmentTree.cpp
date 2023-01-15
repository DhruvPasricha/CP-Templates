#include <bits/stdc++.h>
using namespace std;
/*
 *  Segment Tree (0 based indexing)
 *  Point Update and Range Query O(log N)
 *  Usage:
    *   Pass initial array and neutral value to the constructor
    *   Create a merge function outside the class
 */
#define v vector
template < typename T >
class SegmentTree {
    v < v < T >> Tree;
    T neutralValue;
    T query(int level, int idx, int treeLeft, int treeRight, int l, int r) {
        if (treeLeft > treeRight or treeRight < l or treeLeft > r or r < treeLeft or l > treeRight or level == Tree.size())
            return neutralValue;
        if (l <= treeLeft and treeRight <= r)
            return Tree[level][idx];
        int m = (treeLeft + treeRight) / 2;
        return merge(query(level + 1, 2 * idx, treeLeft, m, l, r), query(level + 1, 2 * idx + 1, m + 1, treeRight, l, r));
    }
public:
    SegmentTree(v < T > & A, T neutralValue) {
        this -> neutralValue = neutralValue;
        int n = A.size();
        Tree.push_back(v < T > (1, neutralValue));
        int prev = 1;
        while (prev < n) {
            Tree.push_back(v < T > (2 * prev, neutralValue));
            prev *= 2;
        }
        int levels = Tree.size();
        for (int i = 0; i < n; i++)
            Tree[levels - 1][i] = A[i];
        for (int i = levels - 2; i >= 0; i--)
            for (int j = 0; j < (1 << i); j++)
                Tree[i][j] = merge(Tree[i + 1][2 * j], Tree[i + 1][2 * j + 1]);
    }
    void update(int idx, T val) {
        int levels = Tree.size();
        Tree[levels - 1][idx] = val;
        idx /= 2;
        for (int i = levels - 2; i >= 0; i--, idx /= 2)
            Tree[i][idx] = merge(Tree[i + 1][2 * idx], Tree[i + 1][2 * idx + 1]);
    }
    T query(int l, int r) {
        return query(0, 0, 0, Tree.back().size() - 1, l, r);
    }
};
