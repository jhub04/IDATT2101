import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class SCC {

  // Main method to find strongly connected components
  public List<List<Integer>> findSCC(List<Integer>[] graph) {
    int vertex = graph.length;
    boolean[] visited = new boolean[vertex];

    // Step 1: Get the order of vertices after DFS finishes
    List<Integer> order = orderOfGraph(graph, visited);

    // Step 2: Reverse the original graph
    List<Integer>[] reverse = reverseGraph(graph);

    visited = new boolean[vertex]; // Reset visited array for second DFS search
    List<List<Integer>> result = new ArrayList<>();
    // Step 3: Run DFS on the reversed graph
    for (int v : order) {
      if (!visited[v]) {
        List<Integer> component = new ArrayList<>();
        depthFirstSearch(reverse, v, visited, component);
        result.add(component);
      }
    }
    return result;
  }

  // Permorms the first DFS to determine the finishing order of the vertices
  public List<Integer> orderOfGraph(List<Integer>[] graph, boolean[] visited) {
    int vertex = graph.length;
    List<Integer> order = new ArrayList<>();

    for (int i = 0; i < vertex; i++) {
      if (!visited[i]) {
        depthFirstSearch(graph, i, visited, order);
      }
    }
    // Reverse the order
    Collections.reverse(order);
    return order;
  }

  // Creates the reverse graph
  public List<Integer>[] reverseGraph(List<Integer>[] graph) {
    int vertex = graph.length;
    List<Integer>[] reverseGraph = new List[vertex];

    // Initialize each vertex's adjacency list
    for (int i = 0; i < vertex; i++) {
      reverseGraph[i] = new ArrayList<>();
    }

    // If there is edge from v to u, reverse it to u to v
    for (int v = 0; v < vertex; v++) {
      for (int u = 0; u < graph[v].size(); u++) {
        reverseGraph[graph[v].get(u)].add(v);
      }
    }
    return reverseGraph;
  }

  // DFS algorithm to traverse the graph
  public void depthFirstSearch(List<Integer>[] graph, int vertex, boolean[] visited, List<Integer> component) {
    // Mark current vertex as visited
    visited[vertex] = true;

    // Explore all neighbor vertices of the current vertex
    for (int i = 0; i < graph[vertex].size(); i++) {
      int neighbor = graph[vertex].get(i);
      if (!visited[neighbor]) {
        depthFirstSearch(graph, neighbor, visited, component);
      }
    }

    component.add(vertex);
  }



  public static void main(String[] args) {
    String filename = "ø5g5.txt";
    List<Integer>[] graph = null;
    try {
      BufferedReader br = new BufferedReader(new FileReader(filename));
      // Read the first line which contains the number of vertices and edges
      String[] firstLine = br.readLine().trim().split("\\s+");
      int vertex = Integer.parseInt(firstLine[0]);
      int edge = Integer.parseInt(firstLine[1]);

      graph = new List[vertex];
      // Initialize each vertex's adjacency list
      for (int i = 0; i < vertex; i++) {
        graph[i] = new ArrayList<>();
      }

      // Read from-vertex to-vertex lines
      String line;
      while ((line = br.readLine()) != null) {
        line = line.trim();
        String[] edgeInfo = line.split("\\s+");
        int head = Integer.parseInt(edgeInfo[0]);
        int tail = Integer.parseInt(edgeInfo[1]);
        graph[head].add(tail);
      }
      br.close();

    } catch (IOException e) {
      e.printStackTrace();
    }

    SCC scc = new SCC();
    List<List<Integer>> scComponents = scc.findSCC(graph);

    System.out.println("Components | Vertices in component");
    for (int comp = 0; comp < scComponents.size(); comp++) {
      System.out.println((comp + 1) + "            " + scComponents.get(comp));
    }

  }

}
