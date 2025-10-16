// Copyright 2025 Arthur Soares

/**
 * \file testa_backup.cpp
 */

#include <cstdio>
#include <cstring>
#include <cassert>
#include "backup.hpp"

int FazBackup(const char* source, const char* destination){
    FILE* file = fopen(source, "r");
    
    if (file == nullptr) {
        return bImpossible;
    }
    return bDoNothing;
}
