#ifndef DIJKSTRAS_ALGORITHM_H
#define DIJKSTRAS_ALGORITHM_H

#include <iostream>
#include <map>
#include <list>
#include <stack>
#include "BinaryHeap.h"
#include "AdjacencyList.h"

void DijkstrasAlgorithm( AdjacencyList<int> & graph, Vertex<int> & source ) {
  BinaryHeap< Vertex<int> > q;

  // Make sure all vertex is set to INFINITY distance and false known, and pointer is to null.
  for( map<int, Vertex<int>>::iterator itr = graph.getMap().begin(); itr != graph.getMap().end(); ++itr  ) {
    itr->second.setDist( std::numeric_limits<double>::max() );
    itr->second.setKnown( false );
    itr->second.setPath( nullptr );
  }

  source.setDist(0);   // source is a reference vertex from graph, so it's being modified in the graph as well.
  q.insert( source );  // equvalent of enqueue.

  while( !q.isEmpty() ) {  // I think this mean that there i still an unknown distnace vertex. got to check slide and make sure.
    Vertex<int> v;
    q.deleteMin( v );  // equvalent of dequeue.
    graph.access( v ).setKnown( true );
    
      // for each Vertex W adjacent to v. Itr points to W which is ajacencent to V.
    for( std::list<GraphNode<int>>::iterator itr = v.getConnection().begin(); itr != v.getConnection().end(); ++itr ) {
        //if( !w.known )
      if( graph.access( itr->getKey() ).getKnown() != true ) { 
        if( graph.access(v).getDist() + itr->getWeight() < graph.access( itr->getKey() ).getDist() ) { // if v.dist + cvw < w.dist. cvw = cost of going from v to w. v.dist is total cost from source to v, and w.dist is total cost from source to w. w = *itr.
          // Update w. Decrease w.dist to v.dist + cvw. And update path pointer.
          graph.access( itr->getKey() ).setDist( graph.access(v).getDist() + itr->getWeight() );
          graph.access( itr->getKey() ).setPath( &graph.access(v) );
          // Enqueue it.
          q.insert( graph.access( itr->getKey() ) );
        }
      }
    }
  }

  return;
}

  // Assumes input graph has been touched by DijkstrasAlgorithm(). This will print out shortest path to v. Assume that the path exists.
void PrintPathSingleVertex( AdjacencyList<int> & graph, Vertex<int> & source, Vertex<int> & destination ) {
  Vertex<int> * path = &destination;
  double total_cost = destination.getDist();
  std::stack<int> path_stack;
    // Uses stack, cuz I am going backward from desitnation to source, then print the opposite direction, first in last out is great for stack.
  while( path != nullptr ) {
    path_stack.push(path->getKey());
    path = path->getPath();
  }
    
  std::cout << destination.getKey() << ": ";
  while( !path_stack.empty() ) {
    std::cout << path_stack.top() << ", ";
    path_stack.pop();
  }
  if( total_cost != std::numeric_limits<double>::max() )
    std::cout << "Total Cost: " << total_cost << std::endl;
  else
    std::cout << "Not Connected to " << source.getKey() << std::endl;

  return;
}

void PrintPathAllVertex( AdjacencyList<int> & graph, Vertex<int> & source ) {
  for( map<int, Vertex<int>>::iterator itr = graph.getMap().begin(); itr != graph.getMap().end(); ++itr ) {
    PrintPathSingleVertex( graph, source, itr->second );
  }
   
  return;
}



#endif
