#include <sstream>
#include <user.hpp>

int main() {
    std::string line;
    std::cout << "SocialNet" << std::endl;
    std::cout << "Enter commands:" << std::endl;
    
    while (std::getline(std::cin, line)) {
        // Skip empty lines
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if(command=="EXIT") break;
        else if (command == "HELP") {
            std::cout << "Available commands:\n"
                    << "ADD_USER <username>: Adds a new user to the network, initially with no friends and no posts.\n"
                    << "ADD_FRIEND <username1> <username2>: Establishes a bidirectional friendship between two existing usernames.\n"
                    << "REMOVE_FRIEND <username1> <username2>: Removes the friendship between two usernames if it exists.\n"
                    << "LIST FRIENDS <username>: Prints an alphabetically sorted list of the specified username's friends.\n"
                    << "SUGGEST FRIENDS <username> <N>: Recommends up to N new friends who are ”friends of a friend” but not already friends. Recommendations are ranked by the number of mutual friends (descending). Ties are broken by alphabetical order of usernames. If N is 0, output nothing. If fewer than N candidates exist, list all available.\n"
                    << "DEGREES OF SEPARATION <username1> <username2>: Calculates the length of the shortest path of friendships between two usernames. If no path exists, reports -1.\n"
                    << "ADD POST <username> <post content>: Add a post whose content is the post content string, to the posts created by the specified user.\n"
                    << "OUTPUT POSTS <username> <N>: Output the most recent N posts of the user, in reverse chronological order. If N is -1, you should output all the posts by the user. If there are fewer than N posts by the user, then list all available posts.\n";
            continue;
        }
        std::string username;
        ss >> username;
        User* active_user = getUser(username);
        if (command == "ADD_USER"){
            if (active_user){
                std::cout << "User '" << username << "' already exists." << std::endl;
            }
            else {
                userMap[username] = new User(username);
                std::cout << "User '" << username << "' added." << std::endl;
            }
        }
        else if (!active_user) {
            std::cout << "Error: User '" << username << "' not found" << std::endl;
            // continue;
        }

        else if (command == "ADD_POST") {
            std::string post_content;
            std::getline(ss, post_content);
            active_user->AddPost(post_content);
        }

        else if (command == "OUTPUT_POSTS") {
            int num_posts = -1;
            ss >> num_posts;
            active_user->OutputPosts(num_posts);
        }

        else if(command == "LIST_FRIENDS") {
            active_user->ListFriends();
        }

        else if(command == "SUGGEST_FRIENDS") {
            int N;
            ss >> N;
            active_user->SuggestFriends(N);
        }

        else{
            std::string friend_username;
            ss >> friend_username;
            User* friend_user = getUser(friend_username);
            if(!friend_user) {
                std::cout << "Error: User '" << friend_username << "' not found" << std::endl;
                continue;
            }
            if(command=="ADD_FRIEND"){
                active_user->AddFriend(friend_user);
                friend_user->AddFriend(active_user);
            }
            else if(command=="REMOVE_FRIEND"){
                active_user->Unfriend(friend_user);
                friend_user->Unfriend(active_user);
            }
            else if(command=="DEGREES_OF_SEPARATION"){
                active_user->DegreesOfSeparation(friend_user);
            }
            else {
                std::cout << "Error: Unknown command '" << command << "'" << std::endl;
                continue;
            }
        }

    }

    // Deallocate memory
    deleteAllUsers();
    
    return 0;
}

