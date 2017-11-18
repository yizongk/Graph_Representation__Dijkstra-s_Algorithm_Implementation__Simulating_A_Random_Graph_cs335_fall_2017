#ifndef STAT_H
#define STAT_H

#include <iostream>
#include <list>

// Struct to contain some statistic
struct Stat {
  unsigned int num_edges_in_graph = 0;
  unsigned int sm_out_degree_vertex = 0;
  unsigned int lg_out_degree_vertex = 0;
  double       avg_out_degree_vertex = 0; 

 // Operation Stat.
  unsigned int num_random_pair_generated = 0;
  unsigned int num_random_pair_both_val_same = 0;
  unsigned int num_random_pair_not_in_graph = 0;
  unsigned int num_random_pair_are_alrdy_connected = 0;
  std::list<unsigned int> num_random_pair_generated_per_block;
};

std::ostream & operator<<( std::ostream & out, const Stat & rhs ) {
  out << "Number of Edges graph contains: " << rhs.num_edges_in_graph << std::endl;
  out << "Smallest out-degree for a vertex: " << rhs.sm_out_degree_vertex << std::endl;
  out << "Largest out-degree for a vertex: " << rhs.lg_out_degree_vertex << std::endl;
  out << "Average out-degree for a vertex: " << rhs.avg_out_degree_vertex << std::endl;
  //out << "num_random_pair_generated: " << rhs.num_random_pair_generated << std::endl;
  //out << "num_random_pair_both_val_same: " << rhs.num_random_pair_both_val_same << std::endl;
  //out << "num_random_pair_not_in_graph: " << rhs.num_random_pair_not_in_graph << std::endl;
  //out << "num_random_pair_are_alrdy_connected: " << rhs.num_random_pair_are_alrdy_connected << std::endl;
  //out << "Number of random pair generated for each block..." << std::endl;
  //std::list<unsigned int>::const_iterator itr = rhs.num_random_pair_generated_per_block.begin();
  //for( int i = 0; itr != rhs.num_random_pair_generated_per_block.end(); ++itr, ++i ) {
  //  out << "Block " << i << ": " << *itr << std::endl;
  //}
  return out;
}

#endif
