#ifndef SPARSE_GRAPH_H
#define SPARSE_GRAPH_H

#include <vector>
#include <array>
#include <limits>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>

template <typename T, size_t ADJ_MAX, bool Directed, bool CalcDistances>
class SparseGraphNodes;

template <typename T, size_t ADJ_MAX, bool Directed, bool CalcDistances>
class SparseGraphNodesIterator;

template <typename T, size_t ADJ_MAX, bool Directed>
class SparseGraphEdgesIterator;

template <typename T, size_t ADJ_MAX, bool Directed>
class SparseGraph {
private:
    friend class SparseGraphNodes<T, ADJ_MAX, Directed, true>;
    friend class SparseGraphNodes<T, ADJ_MAX, Directed, false>;
    friend class SparseGraphEdgesIterator<T, ADJ_MAX, Directed>;

    std::vector<std::array<T, ADJ_MAX>> _edges;

    static constexpr std::array<T, ADJ_MAX> blank_array() {
        std::array<T, ADJ_MAX> blank{};
        for (auto & b: blank) { b = EMPTY; }
        return blank;
    }

public:
    static constexpr T EMPTY = std::numeric_limits<T>::max();
    static constexpr std::array<T, ADJ_MAX> BLANK = blank_array();

    SparseGraph() : _edges{} {
        _edges.reserve(900);
    }

    SparseGraph(const SparseGraph &) = default;
    SparseGraph(SparseGraph &&) = default;
    SparseGraph & operator=(const SparseGraph &) = default;
    SparseGraph & operator=(SparseGraph &&) = default;

    auto nodes() const {
        return SparseGraphNodes<T, ADJ_MAX, Directed, false>(*this);
    }

    auto nodes_with_distances() const {
        return SparseGraphNodes<T, ADJ_MAX, Directed, true>(*this);
    }

    size_t size() const noexcept { return _edges.size(); }

    void resize(size_t count) {
        _edges.resize(count, BLANK);
    }

    void remove_edge(T from, T to) {
        auto it = std::find(std::begin(_edges[from]), std::end(_edges[from]), to);

        if constexpr (!Directed) {
            assert( it != std::end(_edges[from]) );
            *it = EMPTY;
        }
        else {
            if (it != end(_edges[from])) { *it = EMPTY; }
        }
    };

    // removes all edges adjacent with certain node
    void remove_node(T index) {
        for (auto & e: _edges[index]) {
            if (e == EMPTY) { continue; }

            if constexpr (!Directed) { remove_edge(e, index); }
            e = EMPTY;
        }

        if constexpr (Directed) {
            for (T from = 0; from < _edges.size(); ++from) {
                remove_edge(from, index);
            }
        }
    }

    void insert_edge(T ind1, T ind2) {
        auto perform_insertion = [=](T ind1, T ind2){
            for (auto & e: _edges[ind1]) {
                if (e == ind2)  { break; }
                if (e == EMPTY) { e = ind2; break; }
            }
        };

        perform_insertion(ind1, ind2);

        if constexpr (!Directed) {
            perform_insertion(ind2, ind1);
        }
    }

    // returns signal flags, indicated which of the nodes are available from the start node
    std::vector<bool> check_if_passable(const T start, const std::vector<T> & nodes) const {
        auto grnodes = this->nodes();
        std::for_each(grnodes.begin(start), grnodes.end(), [](auto){}); // just iterate

        std::vector<bool> result(nodes.size(), false);
        for (size_t i = 0; i < nodes.size(); ++i) {
            if (grnodes.visited(nodes[i])) { result[i] = true; }
        }
        return result;
    }

    // realized only for directed graphs
    void remove_impassable(std::vector<T> & start_indexes) {
        if constexpr (!Directed) return;

        auto nodes = this->nodes();
        std::for_each(nodes.begin(start_indexes), nodes.end(), [](auto){}); // just iterate

        for (size_t i = 0; i < _edges.size(); i++) {
            if (!nodes.visited(i)) { _edges[i] = BLANK; }
        }
    }

    void transpose() {
        // if graph is not directed, it is already symmetric
        if constexpr (!Directed) { return; }

        SparseGraph<T, ADJ_MAX, Directed> newgraph;
        newgraph.resize(_edges.size());

        for (size_t i = 0u; i < _edges.size(); i++) {
            for (auto & ind: _edges[i]) {
                if (ind != EMPTY) {
                    newgraph.insert_edge(ind, static_cast<T>(i));
                }
            }
        }

        std::swap(*this, newgraph);
    }

    auto edges_begin(size_t index) const {
        return SparseGraphEdgesIterator<T, ADJ_MAX, Directed>(*this, index);
    }

    auto edges_end() const {
        return SparseGraphEdgesIterator<T, ADJ_MAX, Directed>();
    }

    void print() const {
        using namespace std;
        for (size_t i = 0; i < _edges.size(); i++) {
            if (edges_begin(i) == edges_end()) { continue; }

            cout << setw(3) << i << ": ";
            for (auto it = edges_begin(i); it != edges_end(); ++it) {
                cout << setw(4) << *it;
            }
            cout << '\n';
        }
    }
};

#include "sparse_graph_nodes.h"
#include "sparse_graph_nodes_iterator.h"
#include "sparse_graph_edges_iterator.h"

#endif
