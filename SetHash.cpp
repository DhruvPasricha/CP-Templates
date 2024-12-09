struct SetHash
{
    const int k, h, mod;
 
    int hash = 0;
 
    SetHash(int k, int h, int mod) : k(k), h(h), mod(mod) { }
 
    void insert(int num)
    {
        hash += power(num + k, h, mod);
        hash %= mod;
    }
 
    void remove(int num)
    {
        hash -= power(num + k, h, mod);
        hash %= mod;
        hash += mod;
        hash %= mod;
    }
};