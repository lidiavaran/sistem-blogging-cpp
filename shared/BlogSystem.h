#pragma once
#include "Post.h"
#include <vector>
#include <string>
#include <memory>

// Clasa pentru gestionarea blogului
class BlogSystem {
private:
    std::vector<std::unique_ptr<Post>> posts;
    const std::string dataFile = "blog_data.txt";

    void saveToFile();
    void loadFromFile();
    Post* findPostById(int id);
    int findNextAvailableId();

public:
    BlogSystem();
    ~BlogSystem();

    // Student 1
    void createPost(const std::string& author, const std::string& title, const std::string& content);
    void editPost(int id, const std::string& newTitle, const std::string& newContent);
    void deletePost(int id);
    void viewInteractions();

    // Student 2
    void addCommentToPost(int postId, const std::string& commentText);
    void addReactionToPost(int postId, const std::string& reactionType);

    // Comun
    void listAllPosts();
    void viewPostDetails(int id);
};