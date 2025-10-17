// Copyright 2025 Arthur Soares

/**
 * \file testa_backup.cpp
 */

#include <filesystem>
#include <fstream>
#include <cassert>
#include <string>
#include <iostream>
#include <vector>
#include "backup.hpp"

namespace fs = std::filesystem;

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

Config ReadParam(std::ifstream& param_file) {
    Config config;
    std::string line;
    while (std::getline(param_file, line)) {
        std::string trimmed_line = trim(line);

        if (trimmed_line.empty()) {
            continue;
        }
        if (trimmed_line == "FAZ_BACKUP=TRUE") {
            config.faz_backup = true;
        } else {
            config.files.push_back(trimmed_line);
        }
    }
    return config;
}

int FazBackup(const char* pendrive_path) {
    // Assertiva de entrada
    assert(pendrive_path != nullptr && "Diretório destination não pode ser nulo");

    std::ifstream param_file("backup.parm");
    int result = bDoNothing; // Iniciar com um padrão seguro

    if (!param_file.is_open()) {
        result = bImpossible;  
    } else { 
        Config config = ReadParam(param_file);

        for (const auto& file : config.files) {
            fs::path dest_path = fs::path(pendrive_path) / fs::path(file).filename();

            if (fs::exists(file) && !fs::exists(dest_path)) {
                std::error_code ec;
                fs::copy_file(file, dest_path, ec); // Usar copy_file é mais explícito
                
                // CORREÇÃO: O 'return -1;' foi removido.
                if (!ec) { // Se não houve erro
                    result = bBackupToPendrive;
                } else {
                    result = bError; // Se a cópia falhar, marque como erro
                }
            } else if (fs::exists(file) && fs::exists(dest_path)) {
                uintmax_t hd_size = fs::file_size(file);
                uintmax_t pendrive_size = fs::file_size(dest_path);

                if (hd_size > pendrive_size) {
                    std::error_code ec;
                    fs::copy_file(file, dest_path, fs::copy_options::overwrite_existing, ec);
                    if (!ec) {
                        result = bBackupToPendrive;
                    } else {
                        result = bError;
                    }
                }
            }
        }
    }


    //Assertiva de saída;
    assert(result >= bError && result <= bDelete);
    return result;
}