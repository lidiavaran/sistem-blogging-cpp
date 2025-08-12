#include "shared/BlogSystem.h"
#include "shared/Utils.h"
#include <iostream>
#include <vector>
#include <string>

// Afiseaza instructiuni pentru utilizarea aplicatiei 1 (pentru postari)
void showHelpApp2(const std::string& appName) {
    std::cout << "--- Student 2: Interactiuni Cititor ---\n";
    std::cout << "  " << appName << " add_comment <id> \"<comentariu>\"\n";
    std::cout << "  " << appName << " react <id> <love|like|dislike>\n";
    std::cout << "  " << appName << " list_posts\n";
    std::cout << "  " << appName << " view_post <id>\n";
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv, argv + argc);
    if (argc < 2) { showHelpApp2(args[0]); return 1; }

    BlogSystem blog;
    const std::string& command = args[1];

    try {
        if (command == "add_comment") {
            if (argc != 4) throw std::runtime_error("Sintaxa invalida!");
            blog.addCommentToPost(std::stoi(args[2]), args[3]);
        } else if (command == "react") {
            if (argc != 4) throw std::runtime_error("Sintaxa invalida!");
            blog.addReactionToPost(std::stoi(args[2]), args[3]);
        } else if (command == "list_posts") {
            if (argc != 2) throw std::runtime_error("Sintaxa invalida!");
            blog.listAllPosts();
        } else if (command == "view_post") {
            if (argc != 3) throw std::runtime_error("Sintaxa invalida!");
            blog.viewPostDetails(std::stoi(args[2]));
        } else {
            printLabeled<std::string>("EROARE", "Comanda necunoscuta: " + command);
            showHelpApp2(args[0]);
        }
    } catch (const std::exception& e) {
        printLabeled<const char*>("EROARE", e.what());
        return 1;
    }
    return 0;
}