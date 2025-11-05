#include <iostream>
#include <vector>

using namespace std;

void printMatrix(vector<vector<int>>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        cout << "[";
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << " " << matrix[i][j];
        }
        cout << " ]\n";
    }
    cout << '\n';
}

void printMatrix(vector<vector<pair<int, int>>>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        cout << "[";
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << " (" << matrix[i][j].first << ", " << matrix[i][j].second << ")";
        }
        cout << " ]\n";
    }
    cout << '\n';
}

vector<pair<int, int>> getPath(vector<vector<pair<int, int>>> pathMatrix) {
    int n = pathMatrix.size();

    vector<pair<int, int>> path;
    path.push_back(make_pair(n - 1, n - 1));

    pair<int, int> prev = make_pair(n - 1, n - 1);

    while (prev.first != 0 || prev.second != 0) {
        prev = pathMatrix[prev.first][prev.second];
        path.insert(path.begin(), prev);
    }

    return path;
}

pair<int, vector<pair<int, int>>> getMostValuableWay(vector<vector<int>> casilleros) {
    if (casilleros.size() != casilleros[0].size()) {
        cout << "No se matriz de casilleros no cuadrada";
        return {};
    }

    int n = casilleros.size();

    vector<vector<int>> maxGanancia(n, vector<int>(n, 0));
    vector<vector<pair<int, int>>> maxPasos(n, vector<pair<int,int>>(n, make_pair(0, 0)));

    maxGanancia[0][0] = casilleros[0][0];
    maxPasos[0][0] = pair(0, 0);

    for (int i = 1; i < n; i++) {
        int left = maxGanancia[0][i - 1];
        maxGanancia[0][i] = left + casilleros[0][i];
        maxPasos[0][i] = make_pair(0, i - 1);
    }

    for (int j = 1; j < n; j++) {
        int up = maxGanancia[j - 1][0];
        maxGanancia[j][0] = up + casilleros[j][0];
        maxPasos[j][0] = make_pair(j - 1, 0);
    }

    if (n == 1)
        return {maxGanancia[0][0], {make_pair(0,0)}};

    for (int k = 1; k < n; k++) {
        int up = maxGanancia[k - 1][k];
        int left = maxGanancia[k][k -1]; 
        maxGanancia[k][k] = max(up, left) + casilleros[k][k];
        maxPasos[k][k] = up >= left ? make_pair(k - 1, k) : make_pair(k, k - 1);


        for (int i = k + 1; i < n; i++) {
            int up = maxGanancia[k - 1][i];
            int left = maxGanancia[k][i - 1];
            maxGanancia[k][i] = max(up, left) + casilleros[k][i];
            maxPasos[k][i] = up >= left ? make_pair(k - 1, i) : make_pair(k, i - 1);
        }

        for (int j = k + 1; j < n; j++) {
            int up = maxGanancia[j - 1][k];
            int left = maxGanancia[j][k - 1];
            maxGanancia[j][k] = max(up, left) + casilleros[j][k];
            maxPasos[j][k] = up >= left ? make_pair(j - 1, k) : make_pair(j, k - 1);
        }
    }

    auto path = getPath(maxPasos);
    int mejorGanancia = maxGanancia[n - 1][n - 1];

    return {mejorGanancia, path};
}

int main() {
    // vector<vector<int>> casilleros = {
    //     {0, 2, 3, 1, 3},
    //     {4, 3, 2, 1, 2},
    //     {1, 3, 1, 1, 4},
    //     {2, 2, 3, 3, 3},
    //     {3, 1, 2, 4, 1},
    // };
    vector<vector<int>> casilleros = {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0},
        {12, 0, 0, 0, 0},
    };

    printMatrix(casilleros);

    auto [ganancia, path] = getMostValuableWay(casilleros);
    cout << "Ganancia máxima = " << ganancia << "\n";
    
    cout << "Camino para obtener mejor ganancia\n";
    for (auto casilleroPos : path) {
        cout << "(" << casilleroPos.first << ", " << casilleroPos.second << ")  ";
    }
    cout << "\n";
}