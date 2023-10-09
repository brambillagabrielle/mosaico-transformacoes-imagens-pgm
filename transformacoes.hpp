#include <Eigen/Dense>
using namespace Eigen;

#define _PI 3.14159265358979323846

void transformacao2D(PGM *pgmEntrada, PGM *pgmSaida, Matrix3f M)
{
    for (size_t y = 0; y < pgmEntrada->altura; y++)
    {
        for (size_t x = 0; x < pgmEntrada->largura; x++)
        {
            Vector3f coordenadaEntrada(x, y, 1);
            Vector3f coordenadaSaida = M * coordenadaEntrada;

            coordenadaSaida(0) = round(coordenadaSaida(0));
            coordenadaSaida(1) = round(coordenadaSaida(1));

            if (coordValida(pgmSaida, coordenadaSaida.x(), coordenadaSaida.y()))
            {
                unsigned char cor = getPixel(pgmEntrada, coordenadaEntrada.x(), coordenadaEntrada.y());
                setPixel(pgmSaida, coordenadaSaida.x(), coordenadaSaida.y(), cor);
            }
        }
    }
}

void transformacao2D(PPM *ppmEntrada, PPM *ppmSaida, Matrix3f M)
{
    for (size_t y = 0; y < ppmEntrada->altura; y++)
    {
        for (size_t x = 0; x < ppmEntrada->largura; x++)
        {
            Vector3f coordenadaEntrada(x, y, 1);
            Vector3f coordenadaSaida = M * coordenadaEntrada;

            coordenadaSaida(0) = round(coordenadaSaida(0));
            coordenadaSaida(1) = round(coordenadaSaida(1));

            if (coordValida(ppmSaida, coordenadaSaida.x(), coordenadaSaida.y()))
            {
                RGB cor = getPixel(ppmEntrada, coordenadaEntrada.x(), coordenadaEntrada.y());
                setPixel(ppmSaida, coordenadaSaida.x(), coordenadaSaida.y(), cor);
            }
        }
    }
}

void transformacao2DInversa(PGM *pgmEntrada, PGM *pgmSaida, Matrix3f M)
{
    for (size_t y = 0; y < pgmSaida->altura; y++)
    {
        for (size_t x = 0; x < pgmSaida->largura; x++)
        {
            Vector3f coordenadaSaida(x, y, 1);
            Vector3f coordenadaEntrada = M * coordenadaSaida;

            coordenadaEntrada(0) = round(coordenadaEntrada(0));
            coordenadaEntrada(1) = round(coordenadaEntrada(1));

            if (coordValida(pgmSaida, coordenadaEntrada.x(), coordenadaEntrada.y()))
            {
                unsigned char cor = getPixel(pgmEntrada, coordenadaEntrada.x(), coordenadaEntrada.y());
                setPixel(pgmSaida, coordenadaSaida.x(), coordenadaSaida.y(), cor);
            }
        }
    }
}

void transformacao2DInversa(PPM *ppmEntrada, PPM *ppmSaida, Matrix3f M)
{
    for (size_t y = 0; y < ppmSaida->altura; y++)
    {
        for (size_t x = 0; x < ppmSaida->largura; x++)
        {
            Vector3f coordenadaSaida(x, y, 1);
            Vector3f coordenadaEntrada = M * coordenadaSaida;

            coordenadaEntrada(0) = round(coordenadaEntrada(0));
            coordenadaEntrada(1) = round(coordenadaEntrada(1));

            if (coordValida(ppmSaida, coordenadaEntrada.x(), coordenadaEntrada.y()))
            {
                RGB cor = getPixel(ppmEntrada, coordenadaEntrada.x(), coordenadaEntrada.y());
                setPixel(ppmSaida, coordenadaSaida.x(), coordenadaSaida.y(), cor);
            }
        }
    }
}

void gravarSegmento(PGM *pgmAux, PGM *pgmS, int segmento)
{
    for (size_t y = 0; y < pgmAux->altura; y++)
    {
        for (size_t x = 0; x < pgmAux->largura; x++)
        {
            Vector2f coordenadaSaida(x + segmento * pgmAux->largura, y);
            Vector2f coordenadaEntrada(x, y);

            unsigned char cor = getPixel(pgmAux, coordenadaEntrada.x(), coordenadaEntrada.y());
            setPixel(pgmS, coordenadaSaida.x(), coordenadaSaida.y(), cor);
        }
    }
}

void gravarSegmento(PPM *ppmAux, PPM *ppmSaida, int segmento)
{
    for (size_t y = 0; y < ppmAux->altura; y++)
    {
        for (size_t x = 0; x < ppmAux->largura; x++)
        {
            Vector2f coordenadaSaida(x + segmento * ppmAux->largura, y);
            Vector2f coordenadaEntrada(x, y);

            RGB cor = getPixel(ppmAux, coordenadaEntrada.x(), coordenadaEntrada.y());
            setPixel(ppmSaida, coordenadaSaida.x(), coordenadaSaida.y(), cor);
        }
    }
}

float degree2rad(float ang)
{
    return ang * (float)(_PI / 180.0);
}

Matrix3f getTranslacao(float tx, float ty)
{
    Matrix3f M = Matrix3f::Identity();

    M(0, 2) = tx;
    M(1, 2) = ty;

    return M;
}

Matrix3f getCisalhamentoHorizontal(float a)
{
    Matrix3f M = Matrix3f::Identity();

    M(0, 1) = a;

    return M;
}

Matrix3f getReflexaoEixoY()
{
    Matrix3f M = Matrix3f::Identity();

    M(0, 0) = -1;

    return M;
}

Matrix3f getReflexaoEixoX()
{
    Matrix3f M = Matrix3f::Identity();

    M(1, 1) = -1;

    return M;
}

Matrix3f getRotacao(float graus)
{
    Matrix3f M = Matrix3f::Identity();
    float cosO = cos(degree2rad(graus));
    float sinO = sin(degree2rad(graus));

    M(0, 0) = cosO;
    M(0, 1) = -sinO;
    M(1, 0) = sinO;
    M(1, 1) = cosO;

    return M;
}

Matrix3f getEscala(float sx, float sy)
{
    Matrix3f M = Matrix3f::Identity();

    M(0, 0) = sx;
    M(1, 1) = sy;

    return M;
}

Matrix3f getCisalhamentoVertical(float b)
{
    Matrix3f M = Matrix3f::Identity();

    M(1, 0) = b;

    return M;
}