#include "shared/BlogSystem.h"
#include "shared/Utils.h"
#include <iostream>
#include <vector>
#include <string>

// Afiseaza instructiuni pentru utilizarea aplicatiei 1 (pentru postari)
void showHelpApp1(const std::string& appName) {
    std::cout << "--- Student 1: Management Blog ---\n";
    std::cout << "  " << appName << " add_post <autor> \"<titlu>\" \"<continut>\"\n";
    std::cout << "  " << appName << " edit_post <id> \"<titlu_nou>\" \"<continut_nou>\"\n";
    std::cout << "  " << appName << " delete_post <id>\n";
    std::cout << "  " << appName << " list_posts\n";
    std::cout << "  " << appName << " view_post <id>\n";
    std::cout << "  " << appName << " view_interactions\n";
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv, argv + argc);
    if (argc < 2) { showHelpApp1(args[0]); return 1; }

    BlogSystem blog;
    const std::string& command = args[1];

    try {
        if (command == "add_post") {
            if (argc != 5) throw std::runtime_error("Sintaxa invalida!");
            blog.createPost(args[2], args[3], args[4]);
        } else if (command == "edit_post") {
            if (argc != 5) throw std::runtime_error("Sintaxa invalida!");
            blog.editPost(std::stoi(args[2]), args[3], args[4]);
        } else if (command == "delete_post") {
            if (argc != 3) throw std::runtime_error("Sintaxa invalida!");
            blog.deletePost(std::stoi(args[2]));
        } else if (command == "list_posts") {
            if (argc != 2) throw std::runtime_error("Sintaxa invalida!");
            blog.listAllPosts();
        } else if (command == "view_post") {
            if (argc != 3) throw std::runtime_error("Sintaxa invalida!");
            blog.viewPostDetails(std::stoi(args[2]));
        } else if (command == "view_interactions") {
            if (argc != 2) throw std::runtime_error("Sintaxa invalida!");
            blog.viewInteractions();
        } else {
            printLabeled<std::string>("EROARE", "Comanda necunoscuta: " + command);
            showHelpApp1(args[0]);
        }
    } catch (const std::exception& e) {
        printLabeled<const char*>("EROARE", e.what());
        return 1;
    }
    return 0;
}