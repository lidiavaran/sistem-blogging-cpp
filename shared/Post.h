#pragma once
#include <string>
#include <vector>
#include <iostream>

// Clasa pentru un comentariu
class Comment {
public:
    std::string text;
};

// Clasa pentru un comentariu
class Post {
private:
    int id;
    std::string author;
    std::string title;
    std::string content;
    std::vector<Comment> comments;
    int reactions[3] = {0, 0, 0}; // 0:love, 1:like, 2:dislike

public:
    Post(int id, std::string author, std::string title, std::string content);

    int getId() const;
    const std::string& getTitle() const;
    void setTitle(const std::string& newTitle);
    void setContent(const std::string& newContent);
    void addComment(const std::string& text);
    void addReaction(int reactionIndex);

    friend std::ostream& operator<<(std::ostream& os, const Post& post);
    friend class BlogSystem;
};