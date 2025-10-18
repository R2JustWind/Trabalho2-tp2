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

/**
 * Função: Trim
 * 
 * @brief Corta uma string em caracteres significativos
 *
 * @details A função recebe uma string e retorna uma nova string derivada da
 * original, mas que se inicia após o primeiro caracter espaço ou de função e
 * termina logo antes do último caracter espaço ou de função.
 *
 * @param[in]  str  String original a ser cortada.
 *
 * @return Retorna uma string processada de acordo com a função.
 *
 * @pre As seguintes assertivas de entrada devem ser verdadeiras:
 * - !str.empty()
 * 
 * @post As seguintes assertivas de saída devem ser verdadeiras:
 * - last >= first
 *
**/
std::string trim(const std::string& str);

/**
 * Função: ReadParam
 * 
 * @brief Lê o arquivo de parâmetros e retorna uma estrutura Config.
 *
 * @details A função recebe uma ifstream aberta do arquivo de parâmetros,
 * lê seu conteúdo e retorna uma estrutura Config preenchida com os dados 
 * obtidos, tanto sobre a flag de backup quanto sobre os arquivos listados.
 *
 * @param[in]  param_file  Ifstream aberta do arquivo de parâmetros.
 *
 * @return Retorna uma estrutura Config atualizada com os dados do arquivo.
 *
 * @pre As seguintes assertivas de entrada devem ser verdadeiras:
 * - param_file.is_open()
 * 
 * @post As seguintes assertivas de saída devem ser verdadeiras:
 * - !config.files.empty()
 *
**/
Config ReadParam(std::ifstream& param_file);

/**
 * Função: FazBackup
 * 
 * @brief Realiza a tentativa de backup/restauração de acordo com o arquivo de
 * parâmetros fornecido.
 *
 * @details A função recebe uma string com o endereço do diretório para onde 
 * será feito o backup ou de onde será feita a restauração, tomando então as
 * ações necessárias comandadas pelo arquivo de parâmetros.
 *
 * @param[in]  pdPath  String com o diretório que será usado nas operações 
 * (no caso desses testes, com o diretório do PenDrive).
 * 
 * @return Inteiro que indica qual a situação da operação que foi
 * tentada pelo código, podendo variar entre: \n
 * bError = -2 \n
 * bImpossible = -1 \n
 * bDoNothing = 0 \n
 * bBackupToPendrive = 1 \n
 * bBackupToHD = 2 \n
 * bDelete = 3 \n
 *
 * @pre As seguintes assertivas de entrada devem ser verdadeiras:
 * - pdPath != nullptr
 * 
 * @post As seguintes assertivas de saída devem ser verdadeiras:
 * - result >= bError && result <= bDelete
 *
**/
int FazBackup(const char* pdPath);


#endif  // BACKUP_HPP_
