#include "Logger.h"
#include <iostream>
#include <fstream>

void Logger::update(const std::string& query) {
    // Afisam in consola log-ul
    std::cout << "\n[LOGGER] A fost efectuata o cautare pentru: '" << query << "'\n";

    // Scriem si intr-un fisier de log
    std::ofstream logFile("search_history.log", std::ios::app);
    if (logFile.is_open()) {
        logFile << "Cautare inregistrata: " << query << "\n";
        logFile.close();
    }
}