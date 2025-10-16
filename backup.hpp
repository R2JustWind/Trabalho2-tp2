#ifndef BACKUP_HPP_
#define BACKUP_HPP_
// Copyright 2025 Arthur Soares

#define bImpossible -1
#define bError -2
#define bDoNothing 0
#define bBackupToPendrive 1
#define bBackupToHD 2
#define bDelete 3

/**
 * @file backup.hpp
 * @brief Declarações do sistema de backup.
 */

int FazBackup(const char* source, const char* destination);

#endif  // BACKUP_HPP_  