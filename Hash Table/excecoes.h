#ifndef DEC0006_TABELA_ESPALHAMENTO_EXCECOES_H
#define DEC0006_TABELA_ESPALHAMENTO_EXCECOES_H

#include <stdexcept>
// std::invalid_argument
// std::runtime_error
#include <string>
// std::string

class ExcecaoDadoInexistente: public std::invalid_argument
{
public:
	ExcecaoDadoInexistente();
};

class [[maybe_unused]] ExcecaoNaoImplementado: public std::runtime_error
{
public:
	explicit ExcecaoNaoImplementado(std::string const& nome);
};

ExcecaoDadoInexistente::ExcecaoDadoInexistente():
	std::invalid_argument{"o dado nao esta contido na tabela"}
{}

ExcecaoNaoImplementado::ExcecaoNaoImplementado(std::string const& nome):
	std::runtime_error
	{
		std::string{"\""} + nome + "\" nao foi implementado ainda"
	}
{}

#endif
