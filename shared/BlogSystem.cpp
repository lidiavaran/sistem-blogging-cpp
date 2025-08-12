#include "BlogSystem.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>

BlogSystem::BlogSystem() { loadFromFile(); }
BlogSystem::~BlogSystem() { saveToFile(); }

// Incarca toate postarile din fisier
void BlogSystem::loadFromFile() {
    std::ifstream file(dataFile);
    if (!file.is_open()) return;
    posts.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line == "POST_START") {
            int id; std::string author, title, content;
            std::getline(file, line); id = std::stoi(line);
            std::getline(file, author);
            std::getline(file, title);
            std::getline(file, content);
            auto newPost = std::make_unique<Post>(id, author, title, content);
            std::getline(file, line);
            std::stringstream ss(line);
            ss >> newPost->reactions[0] >> newPost->reactions[1] >> newPost->reactions[2];
            while(std::getline(file, line) && line != "POST_END") {
                if (line.rfind("COMMENT:", 0) == 0) {
                    newPost->comments.push_back({line.substr(8)});
                }
            }
            posts.push_back(std::move(newPost));
        }
    }
}

// Salveaza toate postarile in fisier
void BlogSystem::saveToFile() {
    std::ofstream file(dataFile);
    if (!file.is_open()) {
        std::cerr << "EROARE: Nu s-a putut salva fisierul de date.\n"; return;
    }
    for (const auto& postPtr : posts) {
        file << "POST_START" << std::endl;
        file << postPtr->id << std::endl;
        file << postPtr->author << std::endl;
        file << postPtr->title << std::endl;
        file << postPtr->content << std::endl;
        file << postPtr->reactions[0] << " " << postPtr->reactions[1] << " " << postPtr->reactions[2] << std::endl;
        for (const auto& comment : postPtr->comments) {
            file << "COMMENT:" << comment.text << std::endl;
        }
        file << "POST_END" << std::endl;
    }
}

// Cauta urmatorul ID liber
int BlogSystem::findNextAvailableId() {
    if (posts.empty()) return 1;
    std::vector<int> existingIds;
    for (const auto& postPtr : posts) { existingIds.push_back(postPtr->getId()); }
    std::sort(existingIds.begin(), existingIds.end());
    int expectedId = 1;
    for (int currentId : existingIds) {
        if (currentId != expectedId) return expectedId;
        expectedId++;
    }
    return existingIds.back() + 1;
}

// Cauta o postare dupa ID
Post* BlogSystem::findPostById(int id) {
    auto it = std::find_if(posts.begin(), posts.end(), [id](const auto& post) { return post->getId() == id; });
    return (it != posts.end()) ? it->get() : nullptr;
}

// Cauta o postare dupa ID
void BlogSystem::createPost(const std::string& author, const std::string& title, const std::string& content) {
    int newId = findNextAvailableId();
    posts.push_back(std::make_unique<Post>(newId, author, title, content));
    std::cout << "Postare creata cu succes! ID: " << newId << std::endl;
}

// Editeaza o postare
void BlogSystem::editPost(int id, const std::string& newTitle, const std::string& newContent) {
    Post* post = findPostById(id);
    if (post) {
        post->setTitle(newTitle);
        post->setContent(newContent);
        std::cout << "Postarea cu ID " << id << " a fost editata.\n";
    } else {
        std::cout << "Eroare: Postarea cu ID " << id << " nu a fost gasita.\n";
    }
}

// Sterge o postare dupa ID
void BlogSystem::deletePost(int id) {
    auto it = std::remove_if(posts.begin(), posts.end(), [id](const auto& postPtr){ return postPtr->getId() == id; });
    if (it != posts.end()) {
        posts.erase(it, posts.end());
        std::cout << "Postarea cu ID " << id << " a fost stearsa.\n";
    } else {
        std::cout << "Eroare: Postarea cu ID " << id << " nu a fost gasita.\n";
    }
}

// Afiseaza toate reactiile si comentariile de pe blog
void BlogSystem::viewInteractions() {
    std::cout << "--- Istoric Complet Interactiuni ---\n";
    bool foundInteractions = false;
    for (const auto& postPtr : posts) {
        if (!postPtr->comments.empty() || postPtr->reactions[0] > 0 || postPtr->reactions[1] > 0 || postPtr->reactions[2] > 0) {
            foundInteractions = true;
            std::cout << "\n> Postare ID: " << postPtr->getId() << " | Titlu: " << postPtr->getTitle() << std::endl;
            std::cout << "  Reactii: " << postPtr->reactions[0] << " Loves, " << postPtr->reactions[1] << " Likes, " << postPtr->reactions[2] << " Dislikes\n";
            if (!postPtr->comments.empty()) {
                std::cout << "  Comentarii:" << std::endl;
                for (const auto& comment : postPtr->comments) {
                    std::cout << "    - " << comment.text << std::endl;
                }
            }
        }
    }
    if (!foundInteractions) std::cout << "Nicio interactiune gasita pe blog.\n";
    std::cout << "------------------------------------\n";
}

// Adauga un comentariu la o postare
void BlogSystem::addCommentToPost(int postId, const std::string& commentText) {
    Post* post = findPostById(postId);
    if (post) {
        post->addComment(commentText);
        std::cout << "Comentariu adaugat la postarea cu ID " << postId << ".\n";
    } else {
        std::cout << "Eroare: Postarea cu ID " << postId << " nu a fost gasita.\n";
    }
}

// Adauga o reactie la o postare
void BlogSystem::addReactionToPost(int postId, const std::string& reactionType) {
    Post* post = findPostById(postId);
    if (!post) {
        std::cout << "Eroare: Postarea cu ID " << postId << " nu a fost gasita.\n"; return;
    }
    if (reactionType == "love") post->addReaction(0);
    else if (reactionType == "like") post->addReaction(1);
    else if (reactionType == "dislike") post->addReaction(2);
    else {
        std::cout << "Eroare: Tip de reactie invalid.\n"; return;
    }
    std::cout << "Reactie adaugata la postarea cu ID " << postId << ".\n";
}

// Afiseaza lista de postari
void BlogSystem::listAllPosts() {
    std::cout << "--- Lista Postari ---\n";
    if (posts.empty()) {
        std::cout << "Nicio postare gasita.\n";
    } else {
        for (const auto& postPtr : posts) {
            std::cout << "ID: " << postPtr->getId() << " | Titlu: " << postPtr->getTitle() << std::endl;
        }
    }
    std::cout << "---------------------\n";
}

// Afiseaza toate detaliile despre o postare
void BlogSystem::viewPostDetails(int id) {
    Post* post = findPostById(id);
    if (post) {
        std::cout << *post;
    } else {
        std::cout << "Eroare: Postarea cu ID-ul " << id << " nu a fost gasita.\n";
    }
}