+ How to Compile:------------------------------------------------------
$ g++ Program4-sg0440.cpp -o Graph


+ How to Run-----------------------------------------------------------:
* Pass algorithm & filename as arguments

// BFS
$ ./Graph bfs bfs1.in 
// DFS
$ ./Graph dfs dfs1.in
// TS
$ ./Graph ts ts1.in


+ Note------------------------------------------------------------------
-> The program gives prints output on the screen as well as on the file. 
-> The output on the screen is seperated by [tab] for better human readability
-> The output on the file has only been seperated by a white space [ ] for better machine readability 
-> All of the outputs were manually checked except for ts1000.in


+ Algorithms------------------------------------------------------------
> BFS : 


* Start with the first vertex and push it into an empty queue.

* Keep track of visited nodes with a visited map to avoid infinite loop incase of cyclic graphs.

* Pop a vertex from the queue and add all the unvisited adjacent vertices of that popped vertex into the queue and mark them as visited.

* Repeat the last step till the queue is empty

* Initially had weight ++; to calculate weight in each iteration, which was wrong! Realized it when testing with complex case study
-> It did gave the same result for all of the BFS


> DFS : 


* Start with the first vertex and print and mark it as visited.

* Recursively call DFS for all the unvisited adjacent vertices.


-> It did gave the same result for all of the DFS

> TS :


* TS is similar to DFS except the vertex should be printed before it's adjacent vertices in all case

* We use a temporary stack in addition to the call stack of DFS

* We don't first print the vertex, instead we call topological sort recursively for all the unvisited adjacent vertices and then push it to stack.

* A vertex is pushed to the stack only when all of it's adjacent vertices are already in the stack
* Finally print the contents of the stack.


-> It did gave the same result for all of the Topological Sort

> Cycle detection : 


* To detect cycle, we can check for cycle by checking back edges.

* To detect a back edge, we can keep track of vertices currently in recursion stack of function for DFS traversal. 

* If we reach a vertex that is already in the recursion stack, then there is a cycle.



> To check connectivity : 


* Do a DFS of an arbitrary vertex and see if all the vertices are visited. If it's not, the graph is not connected.

* If it's all visited, reverse the graph(transpose) and mark all the vertices as unvisited

* Do a DFS traversal of reversed graph starting from same vertex. If DFS traversal doesn’t visit all vertices, the graph is not connected, else it is connected