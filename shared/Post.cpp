#include "Post.h"
#include <utility>

// Constructor care initializeaza o postare
Post::Post(int id, std::string author, std::string title, std::string content)
    : id(id), author(std::move(author)), title(std::move(title)), content(std::move(content)) {}

// Returneaza ID-ul postarii    
int Post::getId() const { return id; }
const std::string& Post::getTitle() const { return title; }

// Seteaza titlul sau continutul
void Post::setTitle(const std::string& newTitle) { title = newTitle; }
void Post::setContent(const std::string& newContent) { content = newContent; }

// Adauga un comentariu in lista
void Post::addComment(const std::string& text) { comments.push_back({text}); }

// Adauga un comentariu in lista
void Post::addReaction(int reactionIndex) {
    if (reactionIndex >= 0 && reactionIndex < 3) {
        reactions[reactionIndex]++;
    }
}

// Adauga un comentariu in lista
std::ostream& operator<<(std::ostream& os, const Post& post) {
    os << "--- Postare (ID: " << post.id << ") ---\n";
    os << "Titlu: " << post.title << "\n";
    os << "Autor: " << post.author << "\n";
    os << "------------------------------------\n";
    os << post.content << "\n";
    os << "------------------------------------\n";
    os << "Reactii: " << post.reactions[0] << " Loves, " 
       << post.reactions[1] << " Likes, " 
       << post.reactions[2] << " Dislikes\n";
    os << "Comentarii (" << post.comments.size() << "):\n";
    if (post.comments.empty()) {
        os << "Niciun comentariu.\n";
    } else {
        for (const auto& comment : post.comments) {
            os << "- " << comment.text << "\n";
        }
    }
    os << "------------------------------------\n";
    return os;
}