#include "DisjSets.h"

/**
 * Construct the disjoint sets object.
 * numElements is the initial number of disjoint sets.
 */
DisjSets::DisjSets( int numElements ) : s( numElements, -1 ), set_num_( numElements )
{
}

/**
 * Union two disjoint sets.
 * For simplicity, we assume root1 and root2 are distinct
 * and represent set names.
 * root1 is the root of set 1.
 * root2 is the root of set 2.
 * 
 * Added by me (yi zong kuang), if root1 and root2 are same, means they access same index, means both element are part of same set, will not change anything. This 
 * condition has been checked before calling this fct.
 */
void DisjSets::unionSets( int root1, int root2 )
{
    if( root1 == root2 )           // root1 and root2 is same, means it's in same set, nothing should be change in this case.
      return;
    if( s[ root2 ] < s[ root1 ] )  // root2 is deeper
        s[ root1 ] = root2;        // Make root2 new root
    else
    {
        if( s[ root1 ] == s[ root2 ] )
            --s[ root1 ];          // Update height if same
        s[ root2 ] = root1;        // Make root1 new root
    }
    
    --set_num_;
}


/**
 * Perform a find.
 * Error checks omitted again for simplicity.
 * Return the set containing x.
 */
int DisjSets::find( int x ) const
{
    if( s[ x ] < 0 )
        return x;
    else
        return find( s[ x ] );
}


/**
 * Perform a find with path compression.
 * Error checks omitted again for simplicity.
 * Return the set containing x.
 */
int DisjSets::find( int x )
{
    if( s[ x ] < 0 )
        return x;
    else
        return s[ x ] = find( s[ x ] );
}

/**
 * Returns the number of disconnected sets.
 * 1 means all element are in the same set, meaning the graph is now fully connected.
 */
int DisjSets::getSetNum() 
{
    return set_num_;
}
