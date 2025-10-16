// Copyright 2025 Arthur Soares

/**
 * \file testa_backup.cpp
 */

#include <filesystem>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include "backup.hpp"

namespace fs = std::filesystem;

int FazBackup(const char* source, const char* destination) {
    // Assertivas de entrada
    assert(source != nullptr && "Diretório source não pode ser nulo");
    assert(destination != nullptr && "Diretório destination não pode ser nulo");

    std::ifstream param_file("backup.parm");
    int result;

    if (!param_file.is_open()) {
        result = bImpossible;  
        // Retorna bImpossible se o arquivo de parâmetros não existir
    } else {
        result = bDoNothing;   
        // Retorna bDoNothing se o arquivo de parâmetros existir
    }
    //Assertiva de saída;
    assert(result >= bImpossible && result <= bDelete);
    return result;
}
