To compile on terminal type
  make all

To delete executables and object file type
  make clean

//***********************************

i.   All part of the assignment were completed.
ii.  No bugs were encountered
iii. Be at the correct directory on the terminal, type in "make all" without quotes.
     This will generate three program with it's own way of command line:
         ./CreateGraphAndTest [Graph File, typically Graph1.txt] [Query File, typically AdjacencyQueries1.txt]
                            
         ./FindPaths [Graph File, typically Graph1.txt] [Starting Vertex, typically an interger like 1]
                       
         ./TestRandomGraph [Some Interger, typically 100]

iv.  Input files are four:
         "Graph1.txt", "Graph2.txt", "Graph3.txt" to populate the graph.
         "AdjacencyQueries1.txt", "AdjacencyQueries2.txt" to test whehter vertex are connected.

NOTES:
  * ./TestRandomGraph takes a bit to generate random pair of vertex to connect in the graph. Populating the edges for a graph of 100 vertex took about 3 min.
