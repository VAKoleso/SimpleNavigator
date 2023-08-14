#include <gtest/gtest.h>

#include "s21_graph_algorithms.h"

TEST(LGFF, test1) {
  s21::Graph graph;
  ASSERT_EQ(graph.LoadGraphFromFile("Test_files/test1.txt"), false);
}

TEST(EGTD, test1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("Test_files/test1.txt");
  graph.ExportGraphToDot("Test_dot");
  std::string file1_path = "Test_files/test1.dot";
  std::string file2_path = "Test_dot.dot";
  std::ifstream file1(file1_path, std::ios::binary);
  ASSERT_TRUE(file1.is_open()) << "Could not open file1";
  std::ifstream file2(file2_path, std::ios::binary);
  ASSERT_TRUE(file2.is_open()) << "Could not open file2";
  file1.seekg(0, std::ios::beg);
  file2.seekg(0, std::ios::beg);

  while (!file1.eof() && !file2.eof()) {
    char byte1;
    file1.get(byte1);
    char byte2;
    file2.get(byte2);
    ASSERT_EQ(byte1, byte2) << "Files are not identical";
  }

  ASSERT_TRUE(file1.eof() && file2.eof()) << "Files have different lengths";
  file1.close();
  file2.close();
}

TEST(BFS, test1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("Test_files/test1.txt");
  std::vector<unsigned> expectedData = {3, 1, 2, 4, 5};
  s21::GraphAlgorithms algoritm;
  std::vector<unsigned> temp = algoritm.BreadthFirstSearch(graph, 3);
  ASSERT_EQ(expectedData, temp);
}

TEST(BFS, test2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("Test_files/test2.txt");
  std::vector<unsigned> expectedData = {8, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11};
  s21::GraphAlgorithms algoritm;
  std::vector<unsigned> temp = algoritm.BreadthFirstSearch(graph, 8);
  ASSERT_EQ(expectedData, temp);
}

TEST(BFS, test3) {
  s21::Graph graph(10);
  graph.LoadGraphFromFile("Test_files/test2.txt");
  s21::GraphAlgorithms algoritm;
  ASSERT_THROW(algoritm.BreadthFirstSearch(graph, 12), std::invalid_argument);
}

TEST(BFS, test4) {
  s21::Graph graph(10);
  graph.LoadGraphFromFile("Test_files/test2.txt");
  s21::GraphAlgorithms algoritm;
  ASSERT_THROW(algoritm.BreadthFirstSearch(graph, 0), std::invalid_argument);
}

TEST(DFS, test1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("Test_files/test1.txt");
  std::vector<unsigned> expectedData = {3, 1, 2, 4, 5};
  s21::GraphAlgorithms algoritm;
  std::vector<unsigned> temp = algoritm.DepthFirstSearch(graph, 3);
  ASSERT_EQ(expectedData, temp);
}

TEST(DFS, test2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("Test_files/test2.txt");
  std::vector<unsigned> expectedData = {8, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11};
  s21::GraphAlgorithms algoritm;
  std::vector<unsigned> temp = algoritm.DepthFirstSearch(graph, 8);
  ASSERT_EQ(expectedData, temp);
}

TEST(DFS, test3) {
  s21::Graph graph(10);
  graph.LoadGraphFromFile("Test_files/test2.txt");
  s21::GraphAlgorithms algoritm;
  ASSERT_THROW(algoritm.DepthFirstSearch(graph, 12), std::invalid_argument);
}

TEST(DFS, test4) {
  s21::Graph graph(10);
  graph.LoadGraphFromFile("Test_files/test1.txt");
  s21::GraphAlgorithms algoritm;
  ASSERT_THROW(algoritm.DepthFirstSearch(graph, 0), std::invalid_argument);
}

TEST(GSPBV, test1) {
  s21::Graph graph(10);
  graph.LoadGraphFromFile("Test_files/test1.txt");
  s21::GraphAlgorithms algoritm;
  ASSERT_EQ(0U, algoritm.GetShortestPathBetweenVertices(graph, 3, 3));
}

TEST(GSPBV, test2) {
  s21::Graph graph(10);
  graph.LoadGraphFromFile("Test_files/test1.txt");
  s21::GraphAlgorithms algoritm;
  ASSERT_EQ(7U, algoritm.GetShortestPathBetweenVertices(graph, 1, 5));
}

TEST(GSPBV, test3) {
  s21::Graph graph(10);
  graph.LoadGraphFromFile("Test_files/test1.txt");
  s21::GraphAlgorithms algoritm;
  ASSERT_THROW(algoritm.GetShortestPathBetweenVertices(graph, 0, 3),
               std::invalid_argument);
}

TEST(GSPBV, test4) {
  s21::Graph graph(10);
  graph.LoadGraphFromFile("Test_files/test1.txt");
  s21::GraphAlgorithms algoritm;
  ASSERT_THROW(algoritm.GetShortestPathBetweenVertices(graph, 15, 12),
               std::invalid_argument);
}

TEST(prim, test1) {
  s21::Graph graph(10);
  graph.LoadGraphFromFile("Test_files/test2.txt");
  s21::GraphAlgorithms algoritm;
  std::vector<std::vector<unsigned>> result =
      algoritm.GetLeastSpanningTree(graph);
  int length{0};
  for (unsigned i{0}; i < graph.GetSize(); ++i) {
    for (unsigned j{0}; j < graph.GetSize(); ++j) {
      length += result[i][j];
    }
  }
  ASSERT_EQ(length, 150);
  ASSERT_EQ(result[0][7], 12U);
  ASSERT_EQ(result[0][8], 4U);
  ASSERT_EQ(result[1][6], 72U);
  ASSERT_EQ(result[2][10], 13U);
  ASSERT_EQ(result[3][5], 12U);
  ASSERT_EQ(result[4][3], 4U);
  ASSERT_EQ(result[5][9], 3U);
  ASSERT_EQ(result[7][2], 9U);
  ASSERT_EQ(result[7][4], 9U);
  ASSERT_EQ(result[10][1], 12U);
}

TEST(floyd, test1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("Test_files/test3.txt");
  std::vector<unsigned> expectedData = {0, 8, 1, 3, 8, 0, 7, 5,
                                        1, 7, 0, 2, 3, 5, 2, 0};
  s21::GraphAlgorithms algoritm;
  std::vector<std::vector<unsigned>> temp =
      algoritm.GetShortestPathsBetweenAllVertices(graph);

  int n = 0;
  for (size_t i{}; i < temp.size(); ++i) {
    for (size_t j{}; j < temp[i].size(); ++j) {
      ASSERT_EQ(temp[i][j], expectedData[n]);
      n++;
    }
  }
}

TEST(floyd, test2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("Test_files/test1.txt");
  std::vector<unsigned> expectedData = {0, 3,  9,  4,  8,  2, 0, 6, 6,
                                        5, 13, 16, 0,  13, 6, 7, 5, 6,
                                        0, 4,  7,  10, 13, 7, 0};
  s21::GraphAlgorithms algoritm;
  std::vector<std::vector<unsigned>> temp =
      algoritm.GetShortestPathsBetweenAllVertices(graph);

  int n = 0;
  for (size_t i{}; i < temp.size(); ++i) {
    for (size_t j{}; j < temp[i].size(); ++j) {
      ASSERT_EQ(temp[i][j], expectedData[n]);
      n++;
    }
  }
}

TEST(salesman, test1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("Test_files/test2.txt");
  s21::GraphAlgorithms algoritm;
  s21::TsmResult res = algoritm.SolveTravelingSalesmanProblem(graph);

  ASSERT_TRUE(res.distance < 300);
  ASSERT_FALSE(res.distance > 300);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
