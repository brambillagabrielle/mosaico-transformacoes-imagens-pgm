#ifndef PGM_H_INCLUDED
#define PGM_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Dados da PGM
struct PGM
{
    string tipo;
    int largura;
    int altura;
    int vmax;
    unsigned char *pixels;

    PGM()
    {
        pixels = nullptr;
        largura = 0;
        altura = 0;
        vmax = 255;
        tipo = "";
    }
};

// Descarta os dados alocados de uma PGM
void destruir(PGM *pgm)
{
    if (pgm->pixels)
        delete pgm->pixels;

    pgm->pixels = nullptr;
    pgm->largura = 0;
    pgm->altura = 0;
    pgm->tipo = "";
    pgm->vmax = 255;
}

// Imprime os dados de uma PGM
void imprimir(PGM *pgm)
{
    cout << "\n * PGM * \n";
    cout << "Tipo: " << pgm->tipo << endl;
    cout << "Dimensao: " << pgm->largura << "x" << pgm->altura << endl;
    cout << "vMax: " << pgm->vmax << endl;

    if (pgm->pixels)
        cout << "Vetor de pixels: " << &(pgm->pixels) << endl;
    else
        cout << "Vetor de pixels: NULL\n";
}

// Cria uma nova PGM com todos os pixels na cor preto (0), caso a PGM não exista
void criar(PGM *pgm, int largura, int altura)
{
    if (pgm->pixels)
        delete pgm->pixels;

    int tamanho = largura * altura;

    pgm->tipo = "P2";
    pgm->largura = largura;
    pgm->altura = altura;
    pgm->vmax = 255;
    pgm->pixels = new unsigned char[tamanho];

    for (int i = 0; i < tamanho; i++)
        pgm->pixels[i] = 0;
}

// Reseta todos os pixels para a cor preta em uma PGM
void resetarPixels(PGM *pgm)
{
    for (int i = 0; i < pgm->altura * pgm->largura; i++)
        pgm->pixels[i] = 0;
}

// Grava na memória uma PGM de acordo com o caminho recebido
bool gravar(PGM *pgm, string caminho)
{
    if (!pgm->pixels)
        return false;

    ofstream arq;

    arq.open(caminho);
    if (!arq.is_open())
    {
        cout << "PGM: caminho do arquivo invalido\n";
        return false;
    }

    arq << pgm->tipo << endl;
    arq << pgm->largura << " " << pgm->altura << endl;
    arq << 255 << endl;

    int tam = pgm->largura * pgm->altura;
    for (int i = 0; i < tam; i++)
    {
        arq << (int)pgm->pixels[i] << endl;
        arq.flush();
    }

    arq.close();
    return true;
}

// Lê a linha de um arquivo que contém a PGM, ignorando espaços em branco e comentários
string lerLinha(std::ifstream &arq)
{
    string linha = "", dadoLido = "";
    while (!arq.eof())
    {
        linha = "";
        std::getline(arq, linha);
        if (linha.size() > 0 && linha[0] != '#')
            return linha;
    }

    return linha;
}

// Lê um arquivo contendo uma PGM, utilizando a função lerLinha como auxiliar
bool ler(PGM *pgm, string caminho)
{
    ifstream arq;
    string dado;
    stringstream str;

    arq.open(caminho);
    if (!arq.is_open())
    {
        cout << "PGM: endereco do arquivo invalido!\n";
        return false;
    }

    dado = lerLinha(arq);
    if (dado == "P2")
        pgm->tipo = dado;
    else
    {
        cout << "PGM: Erro ao ler o tipo da imagem\n";
        return false;
    }

    dado = lerLinha(arq);
    str = stringstream(dado);
    if (!(str >> pgm->largura))
    {
        cout << "PGM: Erro ao ler a largura\n";
        return false;
    }

    if (!(str >> pgm->altura))
    {
        cout << "PGM: Erro ao ler a largura\n";
        return false;
    }

    dado = lerLinha(arq);
    str = stringstream(dado);
    if (!(str >> pgm->vmax))
    {
        cout << "PGM: Erro ao ler vMax\n";
        return false;
    }

    if (pgm->pixels)
        delete pgm->pixels;

    int tam = pgm->largura * pgm->altura;

    pgm->pixels = new unsigned char[tam];

    int i = 0, p;
    while (!arq.eof())
    {
        if (arq >> p)
        {
            if (i < tam)
                pgm->pixels[i] = (unsigned char)p;
            i++;
        }
        else
            break;
    }

    if (i != tam)
    {
        cout << "PGM: Erro ao ler os pixels!\n";
        return false;
    }

    arq.close();

    return true;
}

// Retorna a cor de um pixel encontrado com a coordenada (x,y) recebida
unsigned char getPixel(PGM *pgm, int x, int y)
{
    if (!pgm->pixels)
        return 0;

    return pgm->pixels[y * pgm->largura + x];
}

// Altera a cor de um pixel encontrado com a coordenada (x,y) recebida
void setPixel(PGM *pgm, int x, int y, unsigned char cor)
{
    if (!pgm->pixels)
        return;

    pgm->pixels[y * pgm->largura + x] = cor;
}

// Verifica se uma determinada coordenada é válida na imagem PGM
bool coordValida(PGM *pgm, int x, int y)
{
    if (!pgm->pixels)
        return false;

    if (x >= 0 && y >= 0 && x < pgm->largura && y < pgm->altura)
        return true;

    return false;
}

#endif