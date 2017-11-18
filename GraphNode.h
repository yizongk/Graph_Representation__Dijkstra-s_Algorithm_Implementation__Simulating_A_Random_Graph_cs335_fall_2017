#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <iostream>

  // Starts off with infinite weight. THis is only ever refering to copies of connections, not the actual vertex, this will waste extra space. Comparable will be int.
template <typename Comparable>
struct GraphNode {
  GraphNode() {
    weight_ = 0;
  }
  GraphNode( Comparable & item, double weight = 1 ) : item_( item ),
                                          weight_( weight ) {

  }
  const Comparable & getKey() {
    return item_;
  }
  const double & getWeight() {
    return weight_;
  }
  bool operator==( const GraphNode<Comparable> & rhs ) const {
    return( this->item_ == rhs.item_ );
  }
  bool operator!=( const GraphNode<Comparable> & rhs ) const {
    return( this->item_ != rhs.item_ );
  }
  bool operator<( const GraphNode<Comparable> & rhs ) const {
    return( this->item_ < rhs.item_ );
  }

  Comparable item_;
  double weight_;
};

template <typename Comparable>
std::ostream & operator<< ( std::ostream & out, const GraphNode<Comparable> & rhs ) {
  out << "(Key: " << rhs.item_ << ", Weight: " << rhs.weight_ << ")";
  return out;
}

#endif
