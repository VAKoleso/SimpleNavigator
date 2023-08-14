#include "console_interface.h"

namespace s21 {
void ConsoleInterface::Start() {
  while (true) {
    DisplayMenu();
    switch (PerformChoice()) {
      case 1:
        LoadGraphFromFile();
        break;
      case 2:
        BreadthFirstSearch();
        break;
      case 3:
        DepthFirstSearch();
        break;
      case 4:
        GetShortestPathBetweenVertices();
        break;
      case 5:
        GetShortestPathsBetweenAllVertices();
        break;
      case 6:
        GetLeastSpanningTree();
        break;
      case 7:
        SolveTravelingSalesmanProblem();
        break;
      case 0:
        exit(0);
      default:
        std::cout << "Нет такой цифры!";
        continue;
    }
    std::cin.get();
    std::cin.get();
    system("clear");
  }
}

void ConsoleInterface::LoadGraphFromFile() {
  std::cout << "Введите путь до файла, относительно данной директории: ";
  std::string filename;
  std::cin >> filename;
  if (graph_.LoadGraphFromFile(filename)) {
    std::cout << "Некоррекктный файл!" << std::endl;
  } else {
    std::cout << "Файл загружен!" << std::endl;
  }
}

void ConsoleInterface::SolveTravelingSalesmanProblem() {
  TsmResult res_struct;
  res_struct = graph_algorithms_.SolveTravelingSalesmanProblem(graph_);

  std::cout << "Длина маршрута: " << res_struct.distance << std::endl;
  std::cout << "Массив с искомым маршрутом: ";

  for (unsigned i{}; i < res_struct.vertices.size(); ++i) {
    std::cout << res_struct.vertices[i];
    if (res_struct.vertices.size() - 1 != i) {
      std::cout << "->";
    }
  }
  std::cout << std::endl;
}

void ConsoleInterface::PrintMatrix(std::vector<std::vector<unsigned>> vec) {
  for (unsigned i{}; i < vec.size(); ++i) {
    for (unsigned j{}; j < vec[i].size(); ++j) std::cout << vec[i][j] << " ";
    std::cout << std::endl;
  }
}

void ConsoleInterface::GetLeastSpanningTree() {
  std::vector<std::vector<unsigned>> vec;
  vec = graph_algorithms_.GetLeastSpanningTree(graph_);
  PrintMatrix(vec);
}

void ConsoleInterface::GetShortestPathsBetweenAllVertices() {
  std::vector<std::vector<unsigned>> vec;
  vec = graph_algorithms_.GetShortestPathsBetweenAllVertices(graph_);
  PrintMatrix(vec);
}

void ConsoleInterface::GetShortestPathBetweenVertices() {
  int vertex1, vertex2;
  std::cout << "Введите 2 вершины через пробел между которыми нужен поиск "
               "пути: ";

  std::cin >> vertex1 >> vertex2;
  std::cout << graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex1,
                                                                vertex2);
}

void ConsoleInterface::DepthFirstSearch() {
  std::vector<unsigned> st;
  int start_vertex = StartVertex();
  st = graph_algorithms_.DepthFirstSearch(graph_, start_vertex);

  for (auto iter : st) {
    std::cout << iter << " ";
  }
}

void ConsoleInterface::BreadthFirstSearch() {
  std::vector<unsigned> qu;
  int start_vertex = StartVertex();
  qu = graph_algorithms_.BreadthFirstSearch(graph_, start_vertex);

  for (auto iter : qu) {
    std::cout << iter << " ";
  }
}

int ConsoleInterface::StartVertex() {
  std::cout << "Введите номер начальной точки: ";
  int start_vertex;
  std::cin >> start_vertex;
  return start_vertex;
}

int ConsoleInterface::PerformChoice() {
  std::cout << "Введите цифру пункта меню: ";
  int choice;
  std::cin >> choice;
  return choice;
}

void ConsoleInterface::DisplayMenu() {
  std::cout << "=========" << std::endl;
  std::cout << " М Е Н Ю " << std::endl;
  std::cout << "=========" << std::endl;
  std::cout << "1. Загрузка исходного графа из файла." << std::endl;
  std::cout << "2. Обход графа в ширину с выводом результата обхода в консоль."
            << std::endl;
  std::cout << "3. Обход графа в глубину с выводом результата обхода в консоль."
            << std::endl;
  std::cout << "4. Поиск кратчайшего пути между произвольными двумя "
               "вершинами с выводом результата в консоль."
            << std::endl;
  std::cout << "5. Поиск кратчайших путей между всеми парами вершин в графе "
               "с выводом результирующей матрицы в консоль."
            << std::endl;
  std::cout << "6. Поиск минимального остовного дерева в графе с выводом "
               "результирующей матрицы смежности в консоль."
            << std::endl;
  std::cout << "7. Решение задачи комивояжера с выводом результирующего "
               "маршрута и его длины в консоль."
            << std::endl;
  std::cout << "0. Выход." << std::endl << std::endl;
}
}  // namespace s21
