//<015>
#include "CampoMinado.h"

CampoMinado::CampoMinado(int linhas, int colunas)
{
    this->linhas = linhas;
    this->colunas = colunas;

    tabuleiro.assign(
        linhas,
        std::vector<char>(colunas, ' ')
    );

    resultado.assign(
        linhas,
        std::vector<int>(colunas, 0)
    );
}

int CampoMinado::getLinhas() const
{
    return linhas;
}

int CampoMinado::getColunas() const
{
    return colunas;
}

bool CampoMinado::posicaoValida(int linha, int coluna) const
{
    return linha >= 0 &&
           linha < linhas &&
           coluna >= 0 &&
           coluna < colunas;
}

void CampoMinado::definirCelula(
    int linha,
    int coluna,
    char valor)
{
    if (posicaoValida(linha, coluna))
    {
        tabuleiro[linha][coluna] = valor;
    }
}

char CampoMinado::getCelula(
    int linha,
    int coluna) const
{
    return tabuleiro[linha][coluna];
}

int CampoMinado::contarMinasVizinhas(
    int linha,
    int coluna) const
{
    int quantidade = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;

            int novaLinha = linha + i;
            int novaColuna = coluna + j;

            if (posicaoValida(novaLinha, novaColuna))
            {
                if (tabuleiro[novaLinha][novaColuna] == '*')
                {
                    quantidade++;
                }
            }
        }
    }

    return quantidade;
}

void CampoMinado::resolver()
{
    for (int linha = 0; linha < linhas; linha++)
    {
        for (int coluna = 0; coluna < colunas; coluna++)
        {
            if (tabuleiro[linha][coluna] != '*')
            {
                resultado[linha][coluna] =
                    contarMinasVizinhas(linha, coluna);
            }
        }
    }
}

int CampoMinado::getResultado(
    int linha,
    int coluna) const
{
    return resultado[linha][coluna];
}