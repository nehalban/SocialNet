#pragma once
#include <avl.hpp>
#include <unordered_map>
#include <set>
#include <queue>
struct User{
    std::string username;
    std::string hashedpassword;
    std::string email;
    std::string bio;
    AVL* posts;
    int post_count;
    struct UserPtrLess{
        bool operator()(const User* a, const User* b) const {
            return a->username < b->username;
        }
    };
    std::set<User*, UserPtrLess> friends;
    User(std::string username) : username(username), posts(new AVL()), post_count(0) {}
    void AddPost(std::string post){
        posts->insert(post);
        post_count++;
    }
    void OutputPosts(int n){
        if(n==-1) n = post_count;
        posts->reverseInOrder(posts->root, n);
    }
    void ListFriends(){
        for (User* friendUser : friends) {
            std::cout << friendUser->username << std::endl;
        }
    }
    void AddFriend(User* user) {
        friends.insert(user);
    }
    void Unfriend(User* user) {
        friends.erase(user);
    }
    void SuggestFriends(int N){
        if(N <= 0) return;

        std::unordered_map<User*, int> mutualFriendsCount;
        for (User* friendUser : friends) {
            for (User* friendOfFriend : friendUser->friends) {
                mutualFriendsCount[friendOfFriend]++;
            }
        }
        for(const auto& friendUser: friends) {
            mutualFriendsCount.erase(friendUser);
        }
        // Create a heap of pairs ordered as (mutual friend count, username)
        using Pair = std::pair<int, std::string>;
        std::vector<Pair> pairs_vector;
        pairs_vector.reserve(mutualFriendsCount.size()); // pre-allocate memory to avoid repeated reallocations in vector
        for (const auto& pair : mutualFriendsCount) {
            pairs_vector.push_back(std::make_pair(pair.second, pair.first->username));
        }

        struct comp{
            bool operator()(const Pair& a, const Pair& b) const {
                if (a.first != b.first) return a.first < b.first;
                return a.second > b.second;
            }
        };
        std::priority_queue<Pair, std::vector<Pair>, comp> pq(pairs_vector.begin(), pairs_vector.end());

        // Pop N elements from the priority queue
        while (N > 0 && !pq.empty()) {
            const auto& suggestion = pq.top();
            std::cout << suggestion.second << " (Mutual Friends: " << suggestion.first << ")\n";
            pq.pop();
            N--;
        }
    }

    void DegreesOfSeparation(User* targetUser){
        if(this == targetUser) {
            std::cout << "Degrees of Separation: 0" << std::endl;
            return;
        }
        std::queue<User*> q;
        std::set<User*> visited;
        q.push(this);
        q.push(nullptr);
        visited.insert(this);
        int degree = 1;
        while(!q.empty()){
            auto currentUser = q.front();
            q.pop();
            if(!currentUser){
                degree++;
                if(!q.empty()) q.push(nullptr);
                continue;
            }
            for(auto friendUser : currentUser->friends){
                if(visited.find(friendUser) == visited.end()){
                    if(friendUser == targetUser){
                        std::cout << "Degrees of Separation: " << degree + 1 << std::endl;
                        return;
                    }
                    visited.insert(friendUser);
                    q.push(friendUser);
                }
            }
        }
        std::cout << "The two users are not connected." << std::endl;
    }
    ~User(){
        delete posts;
        for (User* friendUser : friends) {
            friendUser->Unfriend(this);
        }
    }
};

std::unordered_map<std::string, User*> userMap;
User* getUser(const std::string& username) {
    auto it = userMap.find(username);
    if (it != userMap.end()) {
        return it->second;
    }
    return nullptr; // User not found
}
void deleteAllUsers() {
    for (auto& pair : userMap) {
        delete pair.second;
    }
    userMap.clear();
}
