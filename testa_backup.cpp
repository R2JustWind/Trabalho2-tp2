// Copyright 2025 Arthur Soares

/**
 * \file testa_backup.cpp
 */

#include <string>
#include <cstdio>
#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_NO_POSIX_SIGNALS
#include "catch.hpp"
#include "backup.hpp"

namespace fs = std::filesystem;

void CleanUp() {
    std::remove("backup.parm");
    fs::remove_all("HD");
    fs::remove_all("PenDrive");
}

/**
 * @brief Testa o cenário da coluna 1 da tabela, em que o arquivo de parâmetros não existe.
 * 
 * Condição: O arquivo "backup.parm" não está presente no diretório de execução.
 * Resultado esperado: A função FazBackup deve retornar bImpossible (-1).
 */

TEST_CASE("Arquivo .parm não existe", "[FazBackup]") {
    CleanUp();

    REQUIRE(FazBackup("PenDrive") == bImpossible);
}

TEST_CASE("Backup para o pendrive", "[FazBackup]") {
    CleanUp();

    fs::create_directories("HD");
    fs::create_directories("PenDrive");
    
    std::ofstream("HD/arquivo1.txt") << "conteudo";
    std::string source = fs::absolute("HD/arquivo1.txt").string();

    std::ofstream param_file("backup.parm");
    param_file << "FAZ_BACKUP=TRUE\n" + source + "\n";
    param_file.close();

    REQUIRE(FazBackup("PenDrive/") == bBackupToPendrive);
    REQUIRE(fs::exists("PenDrive/arquivo1.txt") == true);

    CleanUp();
}

TEST_CASE("Ambos possuem o arquivo mas o HD é mais recente", "[FazBackup]") {
    CleanUp();

    fs::create_directories("HD");
    fs::create_directories("PenDrive");

    std::ofstream("PenDrive/arquivo1.txt") << "conteudo";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::ofstream("HD/arquivo1.txt") << "conteudo";
    std::string source_hd = fs::absolute("HD/arquivo1.txt").string();

    std::ofstream param_file("backup.parm");
    param_file << "FAZ_BACKUP=TRUE\n" + source_hd + "\n";
    param_file.close();

    REQUIRE(FazBackup("PenDrive/") == bBackupToPendrive);

    CleanUp();
}

TEST_CASE("Ambos possuem o arquivo de mesmo tamanho", "[FazBackup]") {
    CleanUp();

    fs::create_directories("HD");
    fs::create_directories("PenDrive");
    
    std::ofstream("HD/arquivo1.txt") << "teste";
    std::string source_hd = fs::absolute("HD/arquivo1.txt").string();

    std::ofstream("PenDrive/arquivo1.txt") << "teste";

    std::ofstream param_file("backup.parm");
    param_file << "FAZ_BACKUP=TRUE\n" + source_hd + "\n";
    param_file.close();

    REQUIRE(FazBackup("PenDrive/") == bDoNothing);

    CleanUp();
}

TEST_CASE("Ambos possuem o arquivo mas o de PenDrive é maior", "[FazBackup]") {
    CleanUp();

    fs::create_directories("HD");
    fs::create_directories("PenDrive");
    
    std::ofstream("HD/arquivo1.txt") << "dados menores";
    std::string source_hd = fs::absolute("HD/arquivo1.txt").string();

    std::ofstream("PenDrive/arquivo1.txt") << "dados um pouco maiores";

    std::ofstream param_file("backup.parm");
    param_file << "FAZ_BACKUP=TRUE\n" + source_hd + "\n";
    param_file.close();

    REQUIRE(FazBackup("PenDrive/") == bError);

    CleanUp();
}