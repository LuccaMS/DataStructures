#include "GrafoAbstrato.h"
// GrafoAbstrato

GrafoAbstrato::GrafoAbstrato(MatrizAdjacencia const& matrizAdjacencia):
    _matrizAdjacencia{matrizAdjacencia}
{}

GrafoAbstrato::~GrafoAbstrato() = default;
