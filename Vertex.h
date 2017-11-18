#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <limits>
#include <list>
#include "GraphNode.h"

  // Comparable will be int.
template <typename Comparable>
class Vertex {
 public:
  Vertex() : dist_from_source_( std::numeric_limits<double>::max() ), 
             known_( false ),
             path_( nullptr ) {

  }
  Vertex( Comparable & a ) : id_( a, 0 ), 
                             dist_from_source_( std::numeric_limits<double>::max() ),
                             known_( false ),
                             path_( nullptr ) {
   
  }
    // In our program, only this constructor is being called.
  Vertex( Comparable & a, std::list<GraphNode<Comparable>> & list ) : id_( a , 0 ),
                                                             connections_( list ), 
                                                             dist_from_source_( std::numeric_limits<double>::max() ),
                                                             known_( false ),
                                                             path_( nullptr ) {

  }
  
    // No checking if already contained, have to find out if std::list keep uniqueness or not.
  void addConnection( GraphNode<Comparable> & a ) {
    connections_.push_back( a );
  }
    // No checking if already contained, have to find out if std::list keep uniqueness or not.
  void addConnection( Comparable & a ) {
    GraphNode<Comparable> b(a);
    connections_.push_back(b);
std::cout<<"adding "<<b.item_<<std::endl;
  }
    // No checking if already contained, have to find out if std::list keep uniqueness or not.
  void  removeConnection( GraphNode<Comparable> & a ) {
    //connections_.remove...;
  } 

  const Comparable & getKey() {
    return id_.getKey();
  }

  friend std::ostream & operator<< ( std::ostream & out, const Vertex<Comparable> rhs ) {
    out << "Node: " << rhs.id_ << ", dist: " << rhs.dist_from_source_ << ", known ( 1 true, 2 false ): " << rhs.known_ << " ... connections-> ";
    if( rhs.connections_.empty() ) {
      out << "No Connections. ";
    }   
  
    for( typename std::list<GraphNode<Comparable>>::const_iterator itr = rhs.connections_.begin(); itr != rhs.connections_.end(); ++itr ) {
      out << *itr;
    }
    return out;
  }
  
  bool contains( const Comparable & a ) const {
    typename std::list<GraphNode<Comparable>>::const_iterator itr = connections_.begin();

    for( ; itr != connections_.end(); ++itr ) 
      if( itr->item_ == a )
        return true;

    return false;
  }

  const double giveWeight( const Comparable & a ) const {
    typename std::list<GraphNode<Comparable>>::const_iterator itr = connections_.begin();

    for( ; itr != connections_.end(); ++itr ) 
      if( itr->item_ == a )
        return itr->weight_;

      // This should never return 0, because it will be checked by contains() first, will run if it's in connections_;
    return 0;
  }

  bool operator==( const Vertex<Comparable> & rhs ) const {
    return( this->id_ == rhs.id_ );
  }

  bool operator!=( const Vertex<Comparable> & rhs ) const {
    return( this->id_ != rhs.id_ );
  }

  bool operator<( const Vertex<Comparable> & rhs ) const {
    return( this->dist_from_source_ < rhs.dist_from_source_ );
  }

  void setDist( double dist ) {
    dist_from_source_ = dist;
    return;
  }

  void setKnown( bool known ) {
    known_ = known;
    return;
  }

  const double & getDist() {
    return dist_from_source_;
  }

  const bool & getKnown() {
    return known_;
  }

  std::list<GraphNode<Comparable>> & getConnection() {
    return connections_;
  }

  Vertex<Comparable> * getPath() {
    return path_;
  }

  void setPath( Vertex<Comparable> * a ) {
    path_ = a;
  }

  int getConnectionSize() {
    return connections_.size();
  }

 private:
  GraphNode<Comparable> id_;
  std::list<GraphNode<Comparable>> connections_;
  double dist_from_source_;
  bool known_;
  Vertex<Comparable> * path_;
};

#endif
