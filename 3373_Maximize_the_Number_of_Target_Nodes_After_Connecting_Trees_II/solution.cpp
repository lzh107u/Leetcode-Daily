class Solution {
public:

    void dfs( int node, int parent, int color, vector<int>& colors, const vector<vector<int>>& graph ) {
        // Set the color for the current node
        colors[ node ] = color;

        // Search all its neighbors
        for ( int neighbor : graph[ node ] ) {
            // Make sure the neighbor here is not the parent,
            // because it will cause cycle problem
            if ( neighbor != parent ) {
                dfs( neighbor, node, 1 - color, colors, graph );
            }
        }
    }

    vector<int> searching( vector<vector<int>>& edges ) {
        // Number of nodes
        int N = edges.size() + 1;

        // Build the graph
        vector<vector<int>> graph( N );
        
        for ( const auto& edge : edges ) {
            // Extract 2 node ids from an edge
            int u = edge[ 0 ], v = edge[ 1 ];
            // Build the connection
            graph[ u ].push_back( v );
            graph[ v ].push_back( u );
        }

        // Describe this problem as an color problem, 
        // any adjacent nodes have different colors
        // Only 2 colors in total, 0 for even and 1 for odd
        vector<int> colors( N, -1 );
        // Search the graph, 
        // always starting from node 0, 
        // No parent node from the beginning
        dfs( 0, -1, 0, colors, graph );


        // Count the number of each color
        int count[ 2 ] = { 0, 0 };
        for ( int c : colors ) count[ c ]++;

        // For each node, its even-connection is the number of the nodes with the same color
        vector<int> result( N );
        for ( int i = 0; i < N; ++i ) {
            result[ i ] = count[ colors[ i ] ];
        }

        return result;
    }

    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        
        vector<int> answer;
        
        // Step 1: valid connection in tree 1
        vector<int> valid_tree1 = searching( edges1 );

        // Step 2: valid connection in tree 2
        vector<int> invalid_tree2 = searching( edges2 );

        // Step 3: turn valid connection is tree2 into invalid version,
        // pick a miximum invalid number in tree 2 and add them with valid number in tree 1
        int N = edges2.size() + 1;
        int maximum = 0;
        for ( int i = 0; i < invalid_tree2.size(); ++i ) {
            invalid_tree2[ i ] = N - invalid_tree2[ i ];
            if ( invalid_tree2[ i ] > maximum ) {
                maximum = invalid_tree2[ i ];
            }
        }

        for ( int i = 0; i < valid_tree1.size(); ++i ) {
            answer.push_back( valid_tree1[ i ] + maximum );
        }

        return answer;
    }

    
};