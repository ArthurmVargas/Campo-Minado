//<015>
#ifndef CAMPOMINADO_H
#define CAMPOMINADO_H

#include <vector>

class CampoMinado
{
private:
    int linhas;
    int colunas;

    // Matriz com as minas e espacos vazios.
    std::vector<std::vector<char>> tabuleiro;

    // Matriz que guarda a quantidade de minas em volta.
    std::vector<std::vector<int>> resultado;

    bool posicaoValida(int linha, int coluna) const;

    // Conta quantas minas existem nas posicoes vizinhas.
    int contarMinasVizinhas(int linha, int coluna) const;

public:
    
    CampoMinado(int linhas, int colunas);

    int getLinhas() const;
    int getColunas() const;
    char getCelula(int linha, int coluna) const;

    // Define uma celula como mina ou espaco vazio.
    void definirCelula(int linha, int coluna, char valor);

    // Retorna a quantidade de minas vizinhas calculada para uma celula.
    int getResultado(int linha, int coluna) const;

    // Percorre o tabuleiro e calcula o resultado de todas as celulas vazias.
    void resolver();
};

#endif