// Copyright 2025 Arthur Soares

/**
 * \file testa_backup.cpp
 */

#include <string>
#include <cstdio>
#include <fstream>
#include <filesystem>
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_NO_POSIX_SIGNALS
#include "catch.hpp"
#include "backup.hpp"

namespace fs = std::filesystem;

/**
 * @brief Testa o cenário da coluna 1 da tabela, em que o arquivo de parâmetros não existe.
 * 
 * Condição: O arquivo "backup.parm" não está presente no diretório de execução.
 * Resultado esperado: A função FazBackup deve retornar bImpossible (-1).
 */

TEST_CASE("Arquivo .parm não existe", "[FazBackup]") {
    std::remove("backup.parm");  // Garante que o arquivo não existe

    std::string source = "HD/origem";
    std::string destination = "PenDrive/destino";

    REQUIRE(FazBackup(source.c_str(), destination.c_str()) == bImpossible);
}

TEST_CASE("Backup para o pendrive", "[FazBackup]") {
    std::remove("backup.parm");  // Garante que o arquivo não existe
    fs::remove_all("HD");
    fs::remove_all("PenDrive");

    fs::create_directories("HD");
    fs::create_directories("PenDrive");
    std::ofstream param_file("backup.parm");
    param_file << "FAZ_BACKUP=TRUE\nhd/arquivo1.txt\n";
    std::ofstream("HD/arquivo1.txt") << "conteudo";

    REQUIRE(FazBackup("HD", "PenDrive") == bBackupToPendrive);
}