#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
template <typename T>
class OrderedSet {
private:
    tree< T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update> st;
public:
    int countElementsLessThanX(T x) {
        return st.order_of_key(x);
    }

    int countElementsAtleastX(T x) {
        return st.size() - countElementsLessThanX(x);
    }

    T getKthElement(int k) {
        return *st.find_by_order(k);
    }
    
    void insert(T x) {
        st.insert(x);
    }
    
    void erase(T x) {
        st.erase(x);
    }
};
