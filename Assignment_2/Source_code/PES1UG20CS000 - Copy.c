#include "header.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// ANY STATIC FUNCTIONS ARE UP HERE

static void append(int *queue, int v, int *pqr) 
{
    ++(*pqr);
    queue[*pqr] = v;
}
static int delete(int *queue, int *pqr) 
{
    int res = queue[0];

    for (int i = 0; i < *pqr; ++i) 
    {
        queue[i] = queue[i + 1];
    }
    --(*pqr);
    return res;
}
static void dfs_helper(int n, const connection_t connections[n][n], int vertex, int *visited) 
{
    // Mark node as visited and display
    visited[vertex] = 1;

    // Call dfs_helper on all of its unvisited connections
    for (int i = 0; i < n; ++i) 
    {
        if ( (connections[vertex][i].time > 0 && connections[vertex][i].distance > 0) && visited[i] == 0) 
        {
            dfs_helper(n, connections, i, visited);
        }
    }
}
static void swap(airport_t* a, airport_t* b)
{
    airport_t t = *a;
    *a = *b;
    *b = t;
}
  
/* This function is same in both iterative and recursive*/
static int partition(int (*predicate_func)(const airport_t *, const airport_t *), airport_t airport[], int l, int h)
{
    airport_t x = airport[h];
    int i = (l - 1);
  
    for (int j = l; j <= h - 1; j++) 
    {
        if (predicate_func(&airport[j],&x))
       // if (airport[j].airport_name <= x) 
        {
            i++;
            swap(&airport[i], &airport[j]);
        }
    }
    swap(&airport[i + 1], &airport[h]);
    return (i + 1);
}
static void quickSort(int (*predicate_func)(const airport_t *, const airport_t *), airport_t airport[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(predicate_func, airport, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(predicate_func,airport, low, pi - 1);
        quickSort(predicate_func,airport, pi + 1, high);
    }
}


// A utility function to get maximum of two integers
static int max (int a, int b) 
{ 
    return (a > b)? a: b; 
}

// The preprocessing function for Boyer Moore's bad character heuristic
static void badCharHeuristic(const char *str, int x, int n,int badchar[n])
{
	int i;

	// Initialize all occurrences as -1
	for (i = 0; i < 256 ; i++)
		badchar[i] = -1;

	// Fill the actual value of last occurrence of a character
	for (i = 0; i < x; i++)
		badchar[(int) str[i]] = i;
}

static int dfs(int node, int n, int trip_order[n - 1], const connection_t connections[n][n], int visited[n], int ind, int dist, int source)
{
    visited[node] = 1;
    trip_order[ind] = node;
    if (ind == n - 2)
    {
        visited[node] = 0;
        if (connections[node][source].distance != INT_MAX)
            return (dist + connections[node][source].distance);
        else
            return INT_MAX;
    }
    int curr_trip[n - 1];
    memcpy(curr_trip, trip_order, (n - 1) * sizeof(int));
    int min_dist = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0 && connections[node][i].distance != INT_MAX)
        {
            int temp_trip[n - 1];
            memcpy(temp_trip, trip_order, (n - 1) * sizeof(int));
            int temp = dfs(i, n, temp_trip, connections, visited, ind + 1, dist + connections[node][i].distance, source);
            
            if (temp < min_dist)
            {
                min_dist = temp;
                memcpy(curr_trip, temp_trip, (n - 1) * sizeof(int));
            }
        }
    }

    if (min_dist != INT_MAX)
    {
        memcpy(trip_order, curr_trip, (n - 1) * sizeof(int));
        
    }
    visited[node] = 0;
    return min_dist;
}
static int minKey(int n, int key[], bool mstSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < n; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
 
    return min_index;
}

static void dijkstra(int n,const connection_t Graph[n][n], int start,int *hash) 
{
    int cost[n][n], distance[n];
    int visited[n], count, mindistance, nextnode, i, j;

    for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
        if (Graph[i][j].time == 0)
            cost[i][j] = INT_MAX;
        else
            cost[i][j] = Graph[i][j].time;

    for (i = 0; i < n; i++) 
    {
        distance[i] = cost[start][i];   
        visited[i] = 0;
    }

    distance[start] = 0;
    visited[start] = 1;
    count = 1;

    while (count < n - 1) 
    {
        mindistance = INT_MAX;

        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i]) 
            {
                mindistance = distance[i];
                nextnode = i;
            }

        visited[nextnode] = 1;
        for (i = 0; i < n; i++)
            if (!visited[i])
            if (mindistance + cost[nextnode][i] < distance[i]) 
                distance[i] = mindistance + cost[nextnode][i];
        count++;
    }

    for (i = 0; i < n; i++)
        if (i != start) {
            hash[i]  = distance[i];
    }
}


// YOUR SOLUTIONS BELOW

int q1(int n, const connection_t connections[n][n])
{
    int *visited;

    int i;
    for(i = 0; i<n ; i++)
    {
        // Initialise visited list and set to 0s
        visited = (int *) calloc(n, sizeof(int));
        
        // Out of bounds
        if (i < 0 || i >= n) 
            return 0;

        // Call recursive function
        dfs_helper(n, connections, i, visited);

        for(int k = 0; k < n ;k++)
        {
            if (visited[k] == 0)
                return 0;
        }
        // Free memory used by visited
        free(visited);
    }
    return 1;
}

int q2(const airport_t *src, const airport_t *dest, int n, int k, const connection_t connections[n][n])
{
    int i,count,src_id,dest_id;
    src_id = src->num_id;
    dest_id = dest->num_id;
    if((connections[src_id][dest_id].distance != INT_MAX && connections[src_id][dest_id].time != INT_MAX) || (connections[src_id][dest_id].time != 0 && connections[src_id][dest_id].time != 0))
        return 1;
    else
    {
        for(i = 0; i<n ; i++)
        {
            if((connections[src_id][i].distance != INT_MAX && connections[src_id][i].time != INT_MAX) || (connections[src_id][i].time != 0 && connections[src_id][i].time != 0))
            {
                count++;
                if(((connections[i][dest_id].distance != INT_MAX && connections[i][dest_id].time != INT_MAX) || (connections[i][dest_id].time != 0 && connections[i][dest_id].time != 0)) && (count<=n))
                    return 1;
            }
        }
    }
    return 0;
}

int q3(const airport_t *src, int n, const connection_t connections[n][n])
{
    int *visited, *queue, qr = -1;

    int src_id = src->num_id;

    // Initialise visited list and queue (init 0)
    visited = (int *) calloc(n, sizeof(int));
    queue = (int *) calloc(n, sizeof(int));

    // Out of bounds
    if (src_id < 0 || src_id >= n) 
        return 0;

    // Loop
    append(queue, src_id, &qr);
    visited[src_id] = 1;

    // While queue is not empty
    while (qr != -1) 
    {
        src_id = delete(queue, &qr);
        for (int i = 0; i < n; ++i) 
        {
            if ((connections[src_id][i].time > 0 && connections[src_id][i].distance > 0) && visited[i] == 0) 
            {
                visited[i] = 1;
                append(queue, i, &qr);
                if(connections[i][src_id].time == INT_MAX || connections[i][src_id].distance == INT_MAX)
                    return 0;
            }
            
        }
    }
    // Free memory used by visited and queue
    free(visited);
    free(queue);
    return 1;
}

void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *), airport_t airport_list[n])
{
    quickSort(predicate_func, airport_list, 0, n - 1);   
}

pair_t q5(int n, airport_t airports[n])
{
    pair_t ans = {-1, -1};

    int ind_1=-1, ind_2=-1, count, count1 = 0, id_1=-1, id_2 =-1;
    for(int i = 0; i<n ; i++)
    {
        for(int j = i+1; j<n ;j++)
        {
            count = 0;
            for(int k = 0; k<strlen(airports[i].airport_name) ; k++)
            {
                //if(arr[i][k]==arr[j][k])
                if(airports[i].airport_name[k] == airports[j].airport_name[k])
                {
                    count++;
                    if(count>=count1)
                    {
                        ind_1 = airports[i].num_id;
                        ind_2 = airports[j].num_id;
                        count1 = count;
                    }
                }
            }
        }
        id_1 = ind_1;
        id_2 = ind_2;
    }
    ans.first = id_1;
    ans.second = id_2;
    return ans;
}

int q6(int n, int amount, const int entry_fee[n])
{
    int i, count =0;
    for(i =0; i<n ; i++)
    {
        if (amount >= entry_fee[i])
            count++;
    }
    if(count>0)
        return count;
    return 0;
}

void q7(int n, const char *pat, int contains[n], const airport_t airports[n])
{
    for(int i = 0; i < n; i++)
        contains[i] = 0;
    for(int i = 0; i<n ; i++)
    {
        int x = strlen(pat);
        int y = strlen(airports[i].airport_name);
        int badchar[256];   
        badCharHeuristic(pat, x, y, badchar);
        int s = 0; 
        while(s <= (y - x))
        {
            int j = x-1;
            while(j >= 0 && pat[j] == airports[i].airport_name[s+j])
                j--;

            if (j < 0)
            {
                s += (s+x < y)? x-badchar[(int)airports[i].airport_name[s+x]] : 1;
                contains[i] = 1;
            }
            else
               s += max(1, j - badchar[(int)airports[i].airport_name[s+j]]);
        }
    }
}

int q8(int n, int trip_order[n - 1], const connection_t connections[n][n])
{
    int visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    for (int i = 0; i < n - 1; i++)
        trip_order[i] = -1;
    int min_dist = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        int temp_trip[n - 1];
        memcpy(temp_trip, trip_order, (n - 1) * sizeof(int));
        int dist = dfs(i, n, temp_trip, connections, visited, 0, 0, i);
        if (dist < min_dist)
        {
            min_dist = dist;
            memcpy(trip_order, temp_trip, (n - 1) * sizeof(int));
        }
    }
    if (min_dist == INT_MAX)
        return -1;
    else
        return min_dist;
    return 0;
}

int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{

    // Array to store constructed MST
    int parent[n];
    // Key values used to pick minimum weight edge in cut
    int key[n];
    // To represent set of vertices included in MST
    bool mstSet[n];
 
    // Initialize all keys as INFINITE
    for (int i = 0; i < n; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }
    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex.
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST
 
    // The MST will have n vertices
    for (int count = 0; count < n - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(n, key, mstSet);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not yet included in MST
        for (int v = 0; v < n; v++)
 
            // graph[u][v] is non zero only for adjacent vertices of m mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (connections[u][v].time && mstSet[v] == false && connections[u][v].time < key[v])
                parent[v] = u, key[v] = connections[u][v].time;
    }
 
    int result = 0;
    for (int i = 1; i < n; i++)
    {
        edges[i-1].first = parent[i];
        edges[i-1].second = i;
        result += key[i];
    }
    return result;
}

void q10(int n, int k, const airport_t *src, const connection_t connections[n][n], const int destinations[k], int costs[k])
{
    int hash[n];
    dijkstra(n, connections, src->num_id, hash);
    int i = 0;
    while(i != k)
    {
        costs[i] = hash[destinations[i]];
        i++;
    }
}

// END
