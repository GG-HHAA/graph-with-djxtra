#include <vector> 
#include <iostream> 
#include <cmath> 
#include <queue> 

struct Edge
{
    int start, end;
    int weight;
};

struct Node
{
    uint64_t metka = -1;
    bool f = false;
};

class Graph
{
    int k = 0;
    int n;
    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<int>> list; //в какие вершины мы можем прийти из i-той вершиный 
    std::vector<Edge> edges; //вектор ребер 
public:
    Graph(int n_) : n(n_)
    {
        matrix = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
        list.resize(n);
    }
    void set_matrix()
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j) std::cin >> matrix[i][j];
        }
    }
    void dfs(int, std::vector<bool>&);
    void bfs(int);
    void djxtra();
    void matrix_to_edges_list();
    void matrix_to_list();
    void show_list();
    void show_edges_list();
    int find_node(int, int);
};

int Graph::find_node(int start, int end)
{
    for (int i = 0; i < k; ++i)
    {
        if (edges[i].start == start and edges[i].end == end) return edges[i].weight;
    }
}

void Graph::dfs(int start, std::vector<bool>& visited)
{
    std::cout << start << " ";
    visited[start] = true;
    for (int i = 0; i < matrix[start].size(); i++)
    {
        if (matrix[start][i] != 0 && (!visited[i])) dfs(i, visited);
    }
}

void Graph::bfs(int start)
{
    std::cout << "\nbfs: " << std::endl;
    std::vector<bool> visited(n, false);
    std::vector<int> q;
    q.push_back(start);
    visited[start] = true;
    int vis;
    while (!q.empty())
    {
        vis = q[0];
        std::cout << vis << " ";
        q.erase(q.begin());
        for (int i = 0; i < matrix[vis].size(); i++)
        {
            if (matrix[vis][i] != 0 && (!visited[i]))
            {
                q.push_back(i);
                visited[i] = true;
            }
        }
    }
}

typedef std::pair<uint64_t, size_t> pair;
void Graph::djxtra()
{
    std::vector<Node> node(n);
    std::priority_queue<pair, std::vector<pair>, std::greater<pair>> q;
    int start = 0;
    node[start].metka = 0;
    q.push(std::make_pair(node[start].metka, start));
    while (!q.empty())
    {
        size_t ind = q.top().second;
        q.pop();
        node[ind].f = true;
        for (int i = 0; i < list[ind].size(); ++i)
        {
            if (!node[list[ind][i]].f and (node[ind].metka + find_node(ind, list[ind][i]) < node[list[ind][i]].metka))
            {
                node[list[ind][i]].metka = node[ind].metka + find_node(ind, list[ind][i]);
                q.push(std::make_pair(node[list[ind][i]].metka, i));
            }
        }
    }
    std::cout << std::endl;
    int k = 0;
    for (auto i : node)
    {
        std::cout << k << ": " << i.metka << std::endl;
        ++k;
    }
}

void Graph::matrix_to_list()
{
    for (auto i : list) i.resize(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (matrix[i][j])
            {
                list[i].push_back(j);
            }
        }
    }
}
void Graph::matrix_to_edges_list()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j) if (matrix[i][j] != 0) ++k;
    }
    edges.resize(k);
    k = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (matrix[i][j] != 0)
            {
                edges[k].start = i;
                edges[k].end = j;
                edges[k].weight = matrix[i][j];
                ++k;
            }
        }
    }
}

void Graph::show_list()
{
    std::cout << std::endl;
    for (int i = 0; i < list.size(); ++i)
    {
        std::cout << i << ": ";
        for (int j = 0; j < list[i].size(); ++j) std::cout << list[i][j] << " ";
        std::cout << std::endl;
    }
}

void Graph::show_edges_list()
{
    std::cout << std::endl;
    for (auto i : edges) std::cout << i.start << " -> " << i.end << "  " << i.weight << std::endl;
}

//для дейкстры лучше использовать взыешенный граф, просто скопируй и вставь:
//7
//0 5 8 0 0 0 0
//5 0 0 12 0 9 0
//8 0 0 0 8 4 2
//0 12 0 0 3 6 0
//0 0 8 3 0 0 7
//0 9 4 6 0 0 0
//0 0 2 0 7 0 0


int main()
{
    int n;
    std::cin >> n;
    Graph g(n);
    g.set_matrix();
    g.matrix_to_list();
    //g.show_list();
    g.matrix_to_edges_list();
    //g.show_edges_list();
    g.djxtra();
    /*int start = 0;
    std::vector<bool> visited(n, false);
    g.bfs(start);
    g.dfs(start, visited);*/

}