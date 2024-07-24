#ifndef __UTIL_GRAPH__
#define __UTIL_GRAPH__

#include <map>
#include <numeric>

enum class Directedness {
    Directed = 0,
    Undirected = 1,
};

typedef size_t Handle;

template <typename W>
class Edge {
public:
    explicit Edge(Handle node) : m_node{node}, m_weight{} {}
    Edge(Handle node, W weight) : m_node{node}, m_weight{weight} {}

    Handle node() const noexcept {
        return m_node;
    }

    const W& weight() const noexcept {
        return m_weight;
    }

private:
    Handle m_node;
    W m_weight;
};

template <typename T, typename W>
class AdjacencyList {
public:
    AdjacencyList() : m_data{}, m_edges{} {}
    explicit AdjacencyList(T data) : m_data{data}, m_edges{} {}
    AdjacencyList(T data, std::vector<Edge>&& edges) : m_data{data}, m_edges{std::move(edges)} {}

    const T& data() const noexcept {
        return m_data;
    }

    // TODO : edge iterator

    void add(Handle node) {
        m_edges.emplace_back(node);
    }

    void add(Handle node, W weight) {
        m_edges.emplace_back(node, weight);
    }

    void add(Handle node, W&& weight) {
        m_edges.emplace_back(node, std::move(weight));
    }

    void remove(Handle node) {
        m_edges.erase(node);
    }

private:
    T m_data;
    std::vector<Edge> m_edges;
};

template <typename T, typename W, Directedness d>
class Graph {
public:
    typedef Edge<W> Edge;
    typedef AdjacencyList<T, W> AdjacencyList;

    Graph() : m_adjacencyLists{}, m_nodeCount{0}, m_edgeCount{0} {};

    size_t nodeCount() const noexcept {
        return m_nodeCount;
    }

    size_t edgeCount() const noexcept {
        return m_edgeCount;
    }

    Handle add(T node_data) {
        m_adjacencyLists.emplace_back(node_data);
        Handle handle = static_cast<Handle>(m_nodeCount);
        ++m_nodeCount;
        return handle;
    }

    void connect(Handle parent, Handle child) {
        m_adjacencyLists[parent].add(child);
        ++m_edgeCount;
    }

    void attach(Handle parent, T node) {
        Handle handle = add(node);
        connect(parent, handle);
    }

    void disconnect(Handle parent, Handle child) {
        m_adjacencyLists[parent].remove(child);
    }

private:
    std::vector<AdjacencyList> m_adjacencyLists;
    size_t m_nodeCount;
    size_t m_edgeCount;
};

#endif
