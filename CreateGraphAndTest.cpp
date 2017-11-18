#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "AdjacencyList.h"
#include "Vertex.h"
#include "GraphNode.h"

using namespace std;

  // Takes in input_line in A0, A1 and on are the arguement that will store meaningful info extracted from input_line. Returns true, if any meaningful data was extracted.
template <typename Comparable>
bool ExtractContentFromInputLine( const string & line, Comparable & key, list<GraphNode<Comparable>> & temp_connection ) {
  if( line == "" )
    return false;

  string line_bits = "";
    // Take in the node data. Assumes leading chars are not ' ' for this to work.
  std::string::const_iterator itr = line.begin();
  for( ; *itr != ' ' and itr != line.end(); ++itr ) {
    line_bits += *itr;
  }
    // set the node key, advance pass the first space, and reset line_bits.
  key = std::stoi( line_bits );
  line_bits = "";
  if( itr == line.end() )   // If rest of line is empty, will just return, with a key, and empty temp_connection.
    return true;
  ++itr; 

    // Take in rest of data, which is info about connections to our node. 
  Comparable temp_key = 0;
  double temp_weight = 0;
  for( unsigned int n_th_data_after_key = 1; itr != line.end(); ++itr ) {
    if( *itr != ' ' )
      line_bits += *itr;
    if( *itr == ' ' or itr + 1 == line.end() ) {
      if( line_bits.find('.') == string::npos ) 
        temp_key = stoi( line_bits );
      else 
        temp_weight = stod( line_bits );
     
      if( n_th_data_after_key % 2 == 0 ) {
        // Construct graph node and insert into list of connections. So long that input file is in correct format. it's safe to assume that when weight is taken in, there is already something in the key. So we can safely construct a GraphNode.
        GraphNode<Comparable> temp_graph_node( temp_key, temp_weight );
        temp_connection.push_back( temp_graph_node );
      }

      line_bits = "";
      ++n_th_data_after_key;
    }
  }
  
  return true;
}

  // Comparable is assumed to be Int.
template <typename Comparable>
bool CreateGraph( AdjacencyList<Comparable> & adj_list, const string & input_filename ) {
  cout << "Creating graph base on input file..." << endl;
  cout << "Input graph file: " << input_filename << endl << endl;
  adj_list.makeEmpty();
  
  ifstream input_file;
  input_file.open( input_filename.c_str() );
  if( input_file.fail() ) {
    cout << input_filename << " doesn't exists." << endl;
    cout << "Terminating routine..." << endl;
    return false;
  }
  
  string line = "";
  for( unsigned int i = 1; std::getline( input_file, line ); ++i ) {
    //Extract information.
    Comparable key;
    list<GraphNode<Comparable>> temp_connection;
    if( ExtractContentFromInputLine( line, key, temp_connection ) ) {
      //Insert into Adjacency List, will auto convert data into Vertex then insert.
      adj_list.insert( key, temp_connection);
    }
    else 
      cout << input_filename << ": Corrupt data at line " << i << endl;
  }  
  input_file.close();
  return true;
}

  // Assumes Comparable to be int.
template <typename Comparable>
bool ExtractContentFromQueryLine( const string & line, Comparable & key, Comparable & second_key ) {
  if( line == "" )
    return false;
  
  string::const_iterator itr = line.begin();
  string data = "";
  for( unsigned int n_th_data = 0; itr != line.end(); ++itr ) {
    if( *itr != ' ' )
      data += *itr;
    
    if( *itr == ' ' or itr + 1 == line.end() ) {
      if( n_th_data == 0 )
        key = stoi( data );
      else
        second_key = stoi( data );
    
      ++n_th_data;
      data = "";
    }
  }
 
  return true;
}

template <typename Comparable>
bool Test( const AdjacencyList<Comparable> & list, const string & test_filename ) {
  cout << "Detecting edges base on input file..." << endl;
  cout << "Input file: " << test_filename << endl << endl;

  ifstream input_file;
  input_file.open( test_filename.c_str() );
  if( input_file.fail() ) {
    cout << test_filename << " doesn't exists." << endl;
    cout << "Terminating routine..." << endl;
    return false;
  }

  string line = "";
  for( unsigned int i = 1; std::getline( input_file, line ); ++i ) {
    Comparable key;
    Comparable second_key;
    if( !ExtractContentFromQueryLine( line, key, second_key ) ) {
      cout << test_filename <<": Corrupt data at line " << i << endl;
      continue;
    }

    if( list.contains( key ) ) {
      if( list.edgeDetect( key, second_key ) ) {
        cout << key << " " << second_key << ": Connected, weight of edge is " << list.giveWeight( key, second_key ) << endl;
      }
      else
        cout << key << " " << second_key << ": Not connected" << endl;
    }
    else
      cout << key << " is not in the graph. This vertex doesn't exist in the graph." << endl;
  }

  return true;
}

int main( int argc, char **argv ) {
  if( argc != 3 ) {
    cout << "Usage: ./CreateGraphAndTest [Graph File, typically Graph1.txt] [Query File, typically AdjacencyQueries1.txt]" << endl;
    return 0;
  }

  const string graph_file( argv[1] );
  const string queries_file( argv[2] );

  AdjacencyList<int> list;
 
  if( CreateGraph( list, graph_file ) ) {
    if( !Test( list, queries_file ) )
      return 0;
  }  
  else
    return 0;

  return 0;
}
