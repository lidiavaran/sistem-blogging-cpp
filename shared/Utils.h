#pragma once
#include <iostream>
#include <string>

// Functie utila pentru afisarea unui mesaj cu eticheta (ex: eroare, info)
template <typename T>
void printLabeled(const std::string& label, const T& value) {
    std::cout << "[" << label << "]: " << value << std::endl;
}