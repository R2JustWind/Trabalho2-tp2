// Copyright 2025 Arthur Soares

#ifndef BACKUP_HPP_
#define BACKUP_HPP_

/**
 * @file backup.hpp
 * @brief Declarações do sistema de backup.
 */

#define bImpossible -1
#define bError -2
#define bDoNothing 0
#define bBackupToPendrive 1
#define bBackupToHD 2
#define bDelete 3

struct Config {
    bool faz_backup = false;
    std::vector<std::string> files;
};

std::string trim(const std::string& str);

Config ReadParam(std::ifstream& param_file);

/**
 * @brief Executa a lógica de backup a partir de um diretório fonte e um diretório de destino.
 * 
 * Esta função verifica a existência do arquivo de parâmetros "backup.parm" e a condição dos diretórios,
 * determninando a ação que será tomada.
 * 
 * @param source Caminho do diretório fonte (HD).
 * @param destination Caminho do diretório de destino (pendrive).
 * @return Um código inteiro representando o resultado da operação:
 *        - bImpossible (-1): Indica que qualquer ação é impossível (ex: arquivo de parâmetros não encontrado).
 *        - bError (-2): Indica que ocorreu um erro durante a operação.
 *        - bDoNothing (0): Indica que nenhuma ação é necessária.
 *        - bBackupToPendrive (1): Indica que o backup deve ser realizado para o pendrive.
 *        - bBackupToHD (2): Indica que o backup deve ser realizado para o HD.
 *        - bDelete (3): Indica que algum arquivo deve ser deletado.
 * 
 */
int FazBackup(const char* pendrive_path);


#endif  // BACKUP_HPP_
