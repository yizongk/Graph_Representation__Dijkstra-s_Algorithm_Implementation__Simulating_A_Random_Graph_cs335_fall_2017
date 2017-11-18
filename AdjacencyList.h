#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <list>
#include <map>
#include <utility>
#include "GraphNode.h"
#include "Vertex.h"
#include "Stat.h"

  // Assumes Comparable is int.
template <typename Comparable>
class AdjacencyList {
 public:
    // Defaults at size 0.
  AdjacencyList() : size_( 0 ) {

  }

  void insert( Comparable a ) {
    map_.insert( std::pair<Comparable, Vertex<Comparable>>( a, Vertex<Comparable>( a ) ) );
    ++size_;
  }

  void insert( Comparable a, std::list<GraphNode<Comparable>> & list ) {
    map_[a] = Vertex<Comparable>( a, list );
    ++size_;
  }

  void insert( Vertex<Comparable> a ) {
    map_[a.getKey()] = a;
    ++size_;
  }

  void makeEmpty() {
    map_.clear();
    size_ = 0;
  }

  friend std::ostream & operator<< ( std::ostream & out, const AdjacencyList<Comparable> rhs ) {
    for( typename std::map<Comparable , Vertex<Comparable>>::const_iterator itr = rhs.map_.begin(); itr != rhs.map_.end(); ++itr ) 
      out << "Index:" << itr->first << " | " << itr->second << std::endl;
    
    return out;
  }

  bool contains( const Comparable & a ) const {
    return( map_.count(a) );
  }

    // No chechkig if a is in-fact in map_, must be checked by contains() before calling this.
  Vertex<Comparable> & access( const Comparable & a ) {
    return map_[a];
  }

  Vertex<Comparable> & access( Vertex<Comparable> & a ) {
    return map_[a.getKey()];
  }
  
  // Checks if Vertex A(In graphNode form, not actualy Vertex) is connected to Vertex Key. Return true if connected, else false. Assumes key is in map_.
  bool edgeDetect( const Comparable & key, const Comparable a ) const {
    typename std::map<Comparable, Vertex<Comparable>>::const_iterator itr = map_.find( key );
    return itr->second.contains( a );
  }

    // Returns the weight of A being connected to key. No checking if A's in map_[key], it's should be checked by map_[key].contains() before calling this.
  const double giveWeight( const Comparable & key, const Comparable a ) const {
    typename std::map<Comparable, Vertex<Comparable>>::const_iterator itr = map_.find( key );
    return itr->second.giveWeight( a );
  }

    // This fct returns the map as a way to iterate through this class, but I will code the actualy iterator later on and not use this fct later on. This is just a temp solution.
  std::map<Comparable, Vertex<Comparable>> & getMap() {
    return map_;
  }

    // Add a directed edge pointing from Vertex(with key source) to Vertex(with key adj). Directed(single direction) connection check, not undirected(Bi-directional).
  bool addDirectedEdge( Comparable & source, Comparable & adj) {
    // Chk if both edge exist in graph. return false if either exist
    if( !contains(source) or !contains(adj) )
      return false;
    // Chk if source is already connected to adj, return false if so. edgeDetect returns true if the two vertex are indeed connected, checks one way, directed check.
    if( edgeDetect( source, adj ) ) 
      return false;
    // Add the edge
std::cout<<"for source: "<< source<< ", adj: "<<adj << std::endl;
    map_[source].addConnection(adj);

    return true;
  }

    // Add a undirected edge, point both way
  bool addUndirectedEdge( Comparable & source, Comparable & adj, Stat & program_stat ) {
    if( !addDirectedEdge( source, adj ) )  // If this fct call returned false, return false on this current fct as well.
      return false;
    if( !addDirectedEdge( adj, source ) )
      return false;
    ++program_stat.num_edges_in_graph;
    return true;
  }

  unsigned int size() {
    return size_;
  }

 private:
  std::map<Comparable, Vertex<Comparable>> map_;  //use a map, to simulate an array by using int-key as index.
  unsigned int size_;

};

#endif
