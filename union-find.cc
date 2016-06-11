#include <iostream>
#include <vector>
#include <assert.h>
#include <memory>

class UF 
{
public:
    explicit UF(int nMax):
        m_ids(nMax),
        m_sz(nMax, 1)
    {
        for (int i = 0; i < nMax; ++i)
        {
            m_ids[i] = i;
        }
    }	
    
    ~UF()
    {
    }

    int Root(int val)
    {
        while (m_ids[val] != val) 
        {
            m_ids[val] = m_ids[m_ids[val]];
            val = m_ids[val];
        } 
        return val;
    }

    bool IsUnion(int x, int y)
    {
        assert(x < m_ids.size() && y < m_ids.size());
        return Root(x) == Root(y);
    }

    void dump()
    {
        std::cout << "ids: ";
        for (size_t i = 0; i < m_ids.size(); ++i)
        {
            std::cout << m_ids[i] << ", "; 
        }
        std::cout << std::endl;

        std::cout << "size: ";
        for (size_t i = 0; i < m_sz.size(); ++i)
        {
            std::cout << m_sz[i] << ", "; 
        }
        std::cout << std::endl;
    }

    void Merge(int x, int y)
    {
        assert(x < m_ids.size() && y < m_ids.size());
        int rootX = Root(x);  
        int rootY = Root(y);  

        if (rootX == rootY)
        {
            return;
        }
         
        if (m_sz[rootX] < m_sz[rootY])
        {
            m_ids[rootX] = rootY;
            m_sz[rootY] += m_sz[rootX];
        } 
        else
        {
            m_ids[rootY] = rootX;
            m_sz[rootX] += m_sz[rootY];
        } 
    }

private:
    std::vector<int> m_ids;
    std::vector<int> m_sz;
};

int main()
{
    std::cout << "Enter max num: ";
    int nMax = 10;
    std::cin >> nMax;
    UF uf(nMax);
    std::pair<int, int> ob;
    while (true)
    {
        if (std::cin >> ob.first >> ob.second) 
        {
            uf.Merge(ob.first, ob.second);
            uf.dump();
        }    
    }
    return 0;
}
