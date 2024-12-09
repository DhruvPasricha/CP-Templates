struct Node
{
    int mn;
    Node(int mn = INT_MAX) : mn(mn) {}
};

Node operator + (Node a, Node b)
{
    return Node(min(a.mn, b.mn));
}

template<typename T>
struct SegTree
{
    T *tree;
    const int n;
    const T identity;

private:
#define mid         ((tL + tR) >> 1)
#define lcId        ((tId << 1) + 1)
#define rcId        lcId + 1
#define leftChild   lcId, tL, tM
#define rightChild  rcId, tM + 1, tR

    void update(int tId, int tL, int tR, int idx, T val)
    {
        if(tL == tR)
        {
            tree[tId] = val;
            return;
        }

        int tM = mid;

        if(idx <= mid)
            update(leftChild, idx, val);
        else
            update(rightChild, idx, val);

        tree[tId] = tree[lcId] + tree[rcId];
    }    

    T query(int tId, int tL, int tR, int l, int r)
    {
        if(l > tR or r < tL) return identity;
        if(l <= tL and tR <= r) return tree[tId];
        int tM = mid;
        return query(leftChild, l, r) + query(rightChild, l, r);
    }

#undef mid 
#undef lcId
#undef rcId    
#undef leftChild 
#undef rightChild 
public:
    SegTree(int n, T identity) : n(n), identity(identity)
    {
        tree = new T[4 * n];
        for(int i = 0; i < 4 * n; ++i)
        {
            tree[i] = identity;
        }
    }

    void update(int idx, T val)
    {
        update(0, 0, n - 1, idx, val);
    }

    T query(int l, int r)
    {
        return query(0, 0, n - 1, l, r);
    }
};
