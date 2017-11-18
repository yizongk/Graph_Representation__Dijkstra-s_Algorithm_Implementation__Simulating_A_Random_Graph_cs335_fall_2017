#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Vertex.h"
#include "AdjacencyList.h"
#include "DisjSets.h"
#include "Stat.h"
#include "DijkstrasAlgorithm.h" // For testing purposes, to see if graph is truely have full connectivity.

using namespace std;

// Checks if argv argument is a integer, courtesy of niyasc on StackOverFlow answering a question posted by 0aslam0, asking "C: Checking command line argument is integer or not?"
bool isNumber(char program_argument[])
{
    int i = 0;

    //checking for negative numbers
    if (program_argument[0] == '-')
        i = 1;
    for (; program_argument[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(program_argument[i]))
            return false;
    }
    return true;
}

  // returns a number that ranges from 'start' and 'range'. Assumes input are not negative.
unsigned int RandomNumberRange( const unsigned int & range , const unsigned int & start = 0 ) {
  unsigned int true_range = range - start;
  srand( time(0) );
  unsigned int random_variable = rand() % true_range;
  random_variable += start;

  return random_variable;
}

template <typename Comparable>
void TestRandomGraph( AdjacencyList<Comparable> & graph, DisjSets & sets, const unsigned int & range, Stat & program_stat ) {
  unsigned int reps_for_jesus = 0; // keeps track of how many reps it takes to fall through to the bottom of the following while loop.
  while( sets.getSetNum() != 1 ) {
      // Get random pair
    std::pair<int,int> random_pair;
    random_pair.first = RandomNumberRange( range );
    random_pair.second = RandomNumberRange( range );
    ++program_stat.num_random_pair_generated;
    ++reps_for_jesus;
 
      // Check if random pair both int are same, continue(skip one iteration) if so
    if( random_pair.first == random_pair.second ) {
      ++program_stat.num_random_pair_both_val_same;
      continue;
    }

      // Check if random pair both int are in graph, continue(skip one iteration) if so
    if( !graph.contains( random_pair.first ) or !graph.contains( random_pair.second ) ) {
      ++program_stat.num_random_pair_not_in_graph;
      continue;
    }

      // Check if random pair both int are in the same union, continue(skip one iteration) if so
    if( sets.find( random_pair.first ) == sets.find( random_pair.second ) ) {
      ++program_stat.num_random_pair_are_alrdy_connected;
      continue;
    }

      // connection the two vertex, and update union set data struct
    graph.addUndirectedEdge( random_pair.first, random_pair.second, program_stat );
    sets.unionSets( sets.find(  random_pair.first ), sets.find( random_pair.second ) );
cout<<" num of separate set left:  "<<sets.getSetNum() << endl;

      // Stat gathering.
    program_stat.num_random_pair_generated_per_block.push_back( reps_for_jesus );
    reps_for_jesus = 0;
  }

  return;
}

template <typename Comparable>
void getStatDegreeEdge( AdjacencyList<Comparable> graph, Stat & program_stat ) {
  typename std::map<Comparable,Vertex<Comparable>>::iterator itr = graph.getMap().begin();
  program_stat.sm_out_degree_vertex = itr->second.getConnectionSize();  // Gives some default value that is from the graph (so those val are useful) to use for comparing.
  program_stat.lg_out_degree_vertex = itr->second.getConnectionSize();
  unsigned int accumulator = 0;

  for( ; itr != graph.getMap().end(); ++itr ) {
    unsigned int cur_num_connections = itr->second.getConnectionSize();
    accumulator += cur_num_connections;
    if( cur_num_connections < program_stat.sm_out_degree_vertex )
      program_stat.sm_out_degree_vertex = cur_num_connections;
    if( program_stat.lg_out_degree_vertex < cur_num_connections )
      program_stat.lg_out_degree_vertex = cur_num_connections;
  }

  program_stat.avg_out_degree_vertex = double(accumulator)/double(graph.size());

  return;
}

int main( int argc, char **argv ) {  
  if( argc != 2 ) {
    cout << "Usage: ./TestRandomGraph [Some Interger, typically 100]" << endl;
    return 0;
  }

  if( !isNumber( argv[1] ) ) {
    cout << argv[1] << " is not a interger!" << endl;
    cout << "Usage: ./TestRandomGraph [Some Interger, typically 100]" << endl;
    return 0;
  }
  
  //set const varabile from input
  const int number_of_vertex = stoi( argv[1] );
  //create graph of size variable 
  AdjacencyList<int> list;
  DisjSets sets( number_of_vertex );// Assumed to be of type int, should make this template.
    // Populates list.
  for( int i = 0; i < number_of_vertex; ++i ) {
    list.insert( Vertex<int>(i) );    
  }

    // Test random graph by connecting random vertex.
  Stat program_stat;
  TestRandomGraph( list, sets, number_of_vertex, program_stat );  

  cout<<endl;
  getStatDegreeEdge( list, program_stat);
  cout<<program_stat<<endl;

  return 0;
}
