#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

double costo(const vector<double>& datos, int i, int j) {
    double promedio = 0.0;
    for (int k = i; k <= j; k++) promedio += datos[k];
    promedio /= (j - i + 1);
    double suma = 0.0;
    for (int k = i; k <= j; k++)
        suma += pow(datos[k] - promedio, 2);

    return suma;
}

pair<double, vector<vector<int>>> agrupamientoDinamico(const vector<double>& datos, int grupos) {
    int n = datos.size();
    vector<vector<double>> dp(grupos + 1, vector<double>(n + 1, numeric_limits<double>::infinity()));
    vector<vector<int>> division(grupos + 1, vector<int>(n + 1, -1));

    for (int i = 1; i <= n; i++)
        dp[1][i] = costo(datos, 0, i - 1);

    for (int g = 2; g <= grupos; g++) {
        for (int j = g; j <= n; j++) {
            for (int k = g - 1; k < j; k++) {
                double valor = dp[g - 1][k] + costo(datos, k, j - 1);
                if (valor < dp[g][j]) {
                    dp[g][j] = valor;
                    division[g][j] = k;
                }
            }
        }
    }

    return {dp[grupos][n], division};
}

void imprimirGrupos(const vector<double>& datos, const vector<vector<int>>& division, int grupos, int n) {
    if (grupos == 1) {
        cout << "Grupo " << grupos << ": ";
        for (int i = 0; i < n; i++) cout << datos[i] << " ";
        cout << endl;
        return;
    }
    int k = division[grupos][n];
    imprimirGrupos(datos, division, grupos - 1, k);
    cout << "Grupo " << grupos << ": ";
    for (int i = k; i < n; i++) cout << datos[i] << " ";
    cout << endl;
}

int main() {
    vector<double> valores = {1, 2, 3, 4, 5, 6, 7, 10, 12, 13, 15, 16, 17};
    int cantidadGrupos = 3;

    auto [costoMinimo, divisiones] = agrupamientoDinamico(valores, cantidadGrupos);

    cout << "Costo total mínimo: " << costoMinimo << endl;
    imprimirGrupos(valores, divisiones, cantidadGrupos, valores.size());
}
