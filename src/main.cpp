
#include "adjacency-list.cpp"

int main()
{
  Adj_List_Graph<int> adjGraph1("../include/input-graph.txt");
  adjGraph1.dijkstra(3, 1);
  std::cout << "PRINTING GRAPH 1" << std::endl;
  adjGraph1.PrintGraph();

  printf("\n");

  Adj_List_Graph<char> adjGraph2("../include/canada.txt");
  adjGraph2.dijkstra('t', 't');
  adjGraph2.dijkstra('t', 'm');
  adjGraph2.dijkstra('e', 't');

  std::cout << "PRINTING GRAPH 2" << std::endl;
  adjGraph2.PrintGraph();
  return 0;
}
