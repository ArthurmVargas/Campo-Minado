//<015>
#include "Interface.h"

#include <iostream>

Interface::Interface()
    : janela(sf::VideoMode(800, 600), "Campo Minado"),
      campo(1, 1)
{
    etapa = 0;

    linhas = 0;
    colunas = 0;

    linhaAtual = 0;
    colunaAtual = 0;

    if (!fonte.loadFromFile("assets/arial.ttf"))
    {
        std::cout << "Erro ao carregar fonte.\n";
    }

    janela.setFramerateLimit(60);
}

void Interface::executar()
{
    while (janela.isOpen())
    {
        processarEventos();
        desenhar();
    }
}

void Interface::processarEventos()
{
    sf::Event evento;

    while (janela.pollEvent(evento))
    {
        if (evento.type == sf::Event::Closed)
        {
            janela.close();
        }

        if (evento.type == sf::Event::TextEntered)
        {
            char caractere =
                static_cast<char>(evento.text.unicode);

            if (etapa == 0 || etapa == 1)
            {
                if (caractere >= '0' && caractere <= '9')
                {
                    entrada += caractere;
                }
            }

            else if (etapa == 2)
            {
                if (caractere == '*' || caractere == '.')
                {
                    campo.definirCelula(
                        linhaAtual,
                        colunaAtual,
                        caractere
                    );

                    colunaAtual++;

                    if (colunaAtual == colunas)
                    {
                        colunaAtual = 0;
                        linhaAtual++;
                    }

                    if (linhaAtual == linhas)
                    {
                        campo.resolver();

                        etapa = 3;
                    }
                }
            }
        }

        if (evento.type == sf::Event::KeyPressed)
        {
            if (evento.key.code == sf::Keyboard::BackSpace)
            {
                if ((etapa == 0 || etapa == 1) &&
                    !entrada.empty())
                {
                    entrada.pop_back();
                }
            }

            if (evento.key.code == sf::Keyboard::Enter)
            {
                if (entrada.empty())
                {
                    continue;
                }

                if (etapa == 0)
                {
                    linhas = std::stoi(entrada);

                    entrada.clear();

                    etapa = 1;
                }

                else if (etapa == 1)
                {
                    colunas = std::stoi(entrada);

                    campo = CampoMinado(
                        linhas,
                        colunas
                    );

                    entrada.clear();

                    linhaAtual = 0;
                    colunaAtual = 0;

                    etapa = 2;
                }
            }
        }
    }
}

void Interface::desenhar()
{
    janela.clear(sf::Color::Black);

    sf::Text texto(
        "",
        fonte,
        26
    );

    texto.setFillColor(
        sf::Color::White
    );

    if (etapa == 0)
    {
        texto.setString(
            "Digite o numero de linhas:\n\n" +
            entrada
        );

        texto.setPosition(
            100,
            100
        );

        janela.draw(texto);
    }

    else if (etapa == 1)
    {
        texto.setString(
            "Digite o numero de colunas:\n\n" +
            entrada
        );

        texto.setPosition(
            100,
            100
        );

        janela.draw(texto);
    }

    else if (etapa == 2)
    {
        texto.setString(
            "Digite * para mina ou . para vazio:"
        );

        texto.setPosition(
            100,
            50
        );

        janela.draw(texto);

        float inicioX = 100;
        float inicioY = 120;
        float espaco = 35;

        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                char valor =
                    campo.getCelula(i, j);

                std::string caractere;

                if (valor == ' ')
                {
                    caractere = "_";
                }
                else
                {
                    caractere =
                        std::string(1, valor);
                }

                texto.setString(caractere);

                texto.setPosition(
                    inicioX + j * espaco,
                    inicioY + i * espaco
                );

                janela.draw(texto);
            }
        }
    }

    else if (etapa == 3)
    {
        texto.setString(
            "Resultado:"
        );

        texto.setPosition(
            100,
            50
        );

        janela.draw(texto);

        float inicioX = 100;
        float inicioY = 120;
        float espaco = 35;

        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                std::string valor;

                if (campo.getCelula(i, j) == '*')
                {
                    valor = "*";
                }
                else
                {
                    valor =
                        std::to_string(
                            campo.getResultado(i, j)
                        );
                }

                texto.setString(valor);

                texto.setPosition(
                    inicioX + j * espaco,
                    inicioY + i * espaco
                );

                janela.draw(texto);
            }
        }
    }

    janela.display();
}