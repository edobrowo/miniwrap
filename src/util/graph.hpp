#ifndef __UTIL_GRAPH__
#define __UTIL_GRAPH__

#include <map>
#include <numeric>
#include <vector>

template <typename T>
class Graph {
public:
    Graph() {
        m_adjLists();
    }

    size_t nodeCount() const noexcept {
        return m_adjLists.size();
    }

    size_t edgeCount() const noexcept {
        return std::accumulate(
            m_adjLists.begin(),
            m_adjLists.end(),
            0,
            [](size_t sum, const std::vector<T>& v) {
                return sum + v.size();
            });
    }

    // Add a new node to the adjacency list map
    void add(T node) {
        //
    }

    // Connect a parent to a child node
    void connect(T parent, T child) {
        //
    }

    // Add then connect a node
    void append(T parent, T node) {
        //
    }

    // TODO : BFS iterator
    // TODO : DFS iterator
    // TODO : neighbours iterator

    // TODO : weights? might not be necessary since T could provide that metric
    //  e.g., for FABRIK, Euclidean distance can just be computed for each neighbour

    // TODO : undirected vs. directed? template parameter feels easiest

private:
    std::map<T, std::vector<T>> m_adjLists;
};

#endif
