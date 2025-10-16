// Copyright 2025 Arthur Soares

/**
 * \file testa_backup.cpp
 */

#include "backup.hpp"
#include <string>

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_NO_POSIX_SIGNALS
#include "catch.hpp"

/**
 * @brief Testa o cenário da coluna 1 da tabela, em que o arquivo de parâmetros não existe.
 * 
 * Condição: O arquivo "backup.parm" não está presente no diretório de execução.
 * Resultado esperado: A função FazBackup deve retornar bImpossible (-1).
 */

TEST_CASE("Arquivo .parm não existe", "[FazBackup]") {
    std::remove("backup.parm");  //Garante que o arquivo não existe

    std::string source = "HD/origem";
    std::string destination = "PenDrive/destino";

    REQUIRE(FazBackup(source.c_str(), destination.c_str()) == bImpossible);
}