#include <bits/stdc++.h>
using namespace std;

#define v vector

/*
    *   BinaryLifting: just pass parent array to the constructor (0 based indexing)
    *   Methods: KthAncestor, LCA, Dist
    *   PreComputation: O(N*LogN)
    *   Query: O(LogN)
*/ 
class BinaryLifting
{
private:
    int n, LOGN, root;
    v<v<int>> up;
    v<int> depth;
    v<v<int>> adj;
    void init(v<int> &parent)
    {
        LOGN = log2(n) + 1;
        up.assign(n, v<int>(LOGN, -1));
        depth.assign(n, 0);
        adj.resize(n);
        
        for (int i = 0; i < n; ++i)
            up[i][0] = parent[i];
        
        for (int i = 0; i < n; ++i)
        {
            if (parent[i] != -1)
                adj[parent[i]].push_back(i);
            else
                root = i;
        }
    }
    void buildDfs(int node, int d)
    {
        for(int i = 1; i < LOGN and up[node][i - 1] != -1; ++i)
        {
            int node_ = up[node][i - 1];
            if(node_ != -1) up[node][i] = up[node_][i - 1];
        }

        depth[node] = d;
        for (int child : adj[node])
            buildDfs(child, d + 1);
        
    }
public:
    BinaryLifting(v<int> &parent)
    {
        n = parent.size();
        init(parent);
        buildDfs(root, 0);
    }
    int getKthAncestor(int node, int k)
    {
        for (int i = LOGN - 1; i >= 0 and node != -1; --i)
        {
            if (k & (1 << i))
                node = up[node][i];
        }
        return node;
    }
    int getLCA(int node1, int node2)
    {
        if (depth[node1] < depth[node2])
            swap(node1, node2);
        node1 = getKthAncestor(node1, depth[node1] - depth[node2]);
        if (node1 == node2)
            return node1;
        for (int i = LOGN - 1; i >= 0; --i)
        {
            int node1_ = up[node1][i], node2_ = up[node2][i];
            if (node1_ != node2_)
                node1 = node1_, node2 = node2_;
        }
        return getKthAncestor(node1, 1);
    }
    int getDist(int node1, int node2)
    {
        return depth[node1] + depth[node2] - 2 * depth[getLCA(node1, node2)];
    }
};
