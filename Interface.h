//<015>
#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include <string>

#include "CampoMinado.h"

class Interface
{
private:
    // Janela principal e fonte utilizadas pela interface.
    sf::RenderWindow janela;
    sf::Font fonte;

    // Objeto que executa a logica do Campo Minado.
    CampoMinado campo;

    // Controla a etapa atual do programa:
    // 0 = entrada das linhas
    // 1 = entrada das colunas
    // 2 = entrada do tabuleiro
    // 3 = exibicao do resultado
    int etapa;

    int linhas;
    int colunas;
    int linhaAtual;
    int colunaAtual;

    // Armazena temporariamente os valores digitados pelo usuario.
    std::string entrada;

    // Processa digitos no teclado, fechamento da janela e outros eventos.
    void processarEventos();

    void desenhar();

public:
    Interface();
    void executar();
};

#endif