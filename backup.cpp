// Copyright 2025 Arthur Soares

/**
 * \file testa_backup.cpp
 */

#include <cstdio>
#include <cstring>
#include <cassert>
#include "backup.hpp"

int FazBackup(const char* source, const char* destination){
    //Assertivas de entrada
    assert(source != nullptr && "Diretório source não pode ser nulo");
    assert(destination != nullptr && "Diretório destination não pode ser nulo");
    assert(strlen(source) > 0 && "Diretório source não pode ser vazio");
    assert(strlen(destination) > 0 && "Diretório destination não pode ser vazio");

    FILE* file = fopen("backup.parm", "r");
    int result;

    if (file == nullptr) {
        result = bImpossible;  //Retorna bImpossible se o arquivo de parâmetros não existir
    }else{
        result = bDoNothing;   //Retorna bDoNothing se o arquivo de parâmetros existir
    }
    //Assertiva de saída;
    assert(result >= bImpossible && result <= bDelete && "Código de retorno inválido");
    return result;
}
