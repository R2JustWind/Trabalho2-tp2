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

int FazBackup(const char* pdPath) {
    // Assertiva de entrada
    assert(pdPath != nullptr);

    std::ifstream param_file("backup.parm");
    int result = bDoNothing;   // Iniciar com um padrão seguro
    bool modified = false;

    if (!param_file.is_open()) {
        result = bImpossible;
    } else {
        Config config = ReadParam(param_file);

        for (const auto& file : config.files) {
            fs::path dest_path = fs::path(pdPath) / fs::path(file).filename();

            if (fs::exists(file) && !fs::exists(dest_path)) {
                if(config.faz_backup == true) {
                    std::error_code ec;
                    fs::copy_file(file, dest_path, ec);

                    if (!ec) {
                        result = bBackupToPendrive;
                        modified = true;
                    }
                } else {
                    result = bError;
                }
            } else if (fs::exists(file) && fs::exists(dest_path)) {
                auto hd_time = fs::last_write_time(file);
                auto pendrive_time = fs::last_write_time(dest_path);

                if (hd_time > pendrive_time) {
                    if(config.faz_backup == false) {
                        result = bError;
                    } else {
                        std::error_code ec;
                        fs::copy_file(file, dest_path,
                        fs::copy_options::overwrite_existing, ec);
                        if (!ec) {
                            result = bBackupToPendrive;
                            modified = true;
                        }
                    }
                } else if (pendrive_time == hd_time) {
                    result = bDoNothing;
                    modified = true;
                }
            } else if (!fs::exists(file) && fs::exists(dest_path)) {
                result = bDoNothing;
                modified = true;
            }
            if (!modified) {
                result = bError;
            }
        }
    }


    // Assertiva de saída;
    assert(result >= bError && result <= bDelete);
    return result;
}
