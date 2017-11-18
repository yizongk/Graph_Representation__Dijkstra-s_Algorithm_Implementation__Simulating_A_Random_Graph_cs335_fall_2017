#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "AdjacencyList.h"
#include "Vertex.h"
#include "GraphNode.h"
#include "BinaryHeap.h"
#include "DijkstrasAlgorithm.h"

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

int main( int argc, char ** argv ) {
  if( argc != 3 ) {
    cout << "Usage: ./FindPaths [Graph File, typically Graph1.txt] [Starting Vertex, typically an interger like 1]" << endl;
    return 0;
  }
  if( !isNumber( argv[2] ) ) {
    cout << argv[2] << " is not a interger!" << endl;
    cout << "Usage: ./FindPaths [Graph File, typically Graph1.txt] [Starting Vertex, typically an interger like 1]" << endl;
    return 0;
  }
    //Assumes argv[2] is a number.
  const string graph_file( argv[1] );
  const int start_vertex_key( stoi( argv[2] ) );

  AdjacencyList<int> list;
 
  if( !CreateGraph( list, graph_file ) ) 
    return 0;

  if( !list.contains( start_vertex_key ) ) {
    cout << " The vertex " << start_vertex_key << " is NOT in the graph created from " << graph_file << "." << endl;
    return 0;
  }

  DijkstrasAlgorithm( list, list.access(start_vertex_key) ); 
  PrintPathAllVertex( list, list.access(start_vertex_key)  );

  return 0;
}
