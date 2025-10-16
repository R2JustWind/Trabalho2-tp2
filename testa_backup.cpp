// Copyright 2025 Arthur Soares

/**
 * \file testa_backup.cpp
 */

#include "backup.hpp"
#include <string>

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_NO_POSIX_SIGNALS
#include "catch.hpp"

TEST_CASE("Arquivo .parm não existe", "[FazBackup]") {
    std::string source = "backup.parm";
    std::string destination = "destino";

    REQUIRE(FazBackup(source.c_str(), destination.c_str()) == bImpossible);
}