# SocialNet Simulator

Name : Nehal Bansal
Entry No. : 2024MT10788

A command-line social network simulator that implements core backend functionalities for managing users, friendships, and content using AVL Trees and Graphs.

## Overview

SocialNet simulates a network of users where:
- Each user is represented as a vertex in an undirected graph
- Friendships are represented as edges between vertices
- User posts are stored in an AVL Tree, sorted by timestamp

## Data Structures

- **Graph**: Simulates the social network with users as vertices and friendships as edges
- **AVL Tree**: Efficiently stores posts sorted by creation time
- **HashMap**: Maps username strings to corresponding user vertices

## Project Structure

```
├── main.cpp          # Main program and command parser
├── user.hpp          # User class and graph operations
├── avl.hpp           # AVL Tree implementation for posts
├── compile.sh        # Compilation script
└── README.md         # This file
```

## Compilation

Use the provided shell script to compile the project:

```bash
chmod +x compile.sh
./compile.sh
```

Or compile manually:

```bash
g++ -std=c++11 -I. main.cpp -o socialnet
```

## Running the Program

```bash
./socialnet
```

The program will start and wait for commands from stdin.

## Available Commands

### Social Network Operations

#### ADD_USER
```
ADD_USER <username>
```
Adds a new user to the network with no friends and no posts initially.

**Example:**
```
ADD_USER alice
ADD_USER bob
```

#### ADD_FRIEND
```
ADD_FRIEND <username1> <username2>
```
Establishes a bidirectional friendship between two existing users.

**Example:**
```
ADD_FRIEND alice bob
```

#### REMOVE_FRIEND
```
REMOVE_FRIEND <username1> <username2>
```
Removes the friendship between two users if it exists.

**Example:**
```
REMOVE_FRIEND alice bob
```

#### LIST_FRIENDS
```
LIST_FRIENDS <username>
```
Prints an alphabetically sorted list of the specified user's friends.

**Example:**
```
LIST_FRIENDS alice
```

#### SUGGEST_FRIENDS
```
SUGGEST_FRIENDS <username> <N>
```
Recommends up to N new friends who are "friends of a friend" but not already friends.

**Ranking Criteria:**
- Ranked by number of mutual friends (descending)
- Ties broken by alphabetical order of usernames

**Edge Cases:**
- If N is 0, outputs nothing
- If fewer than N candidates exist, lists all available

**Example:**
```
SUGGEST_FRIENDS alice 5
```

#### DEGREES_OF_SEPARATION
```
DEGREES_OF_SEPARATION <username1> <username2>
```
Calculates the shortest path length between two users. Returns -1 if no path exists.

**Example:**
```
DEGREES_OF_SEPARATION alice charlie
```

### User Content Operations

#### ADD_POST
```
ADD_POST <username> <post content>
```
Adds a post to the specified user's timeline.

**Example:**
```
ADD_POST alice Hello, this is my first post!
```

#### OUTPUT_POSTS
```
OUTPUT_POSTS <username> <N>
```
Outputs the most recent N posts of the user in reverse chronological order.

**Special Cases:**
- If N is -1, outputs all posts
- If fewer than N posts exist, lists all available posts

**Example:**
```
OUTPUT_POSTS alice 10
OUTPUT_POSTS alice -1
```

### Additional Commands

#### HELP
```
HELP
```
Displays a list of all available commands with descriptions.

#### EXIT
```
EXIT
```
Exits the program.

## Important Notes

1. **Case Insensitivity**: Usernames and post contents are not case-sensitive. For example, `Lakshay COL106` and `lakshay col106` are treated as identical.

2. **Error Handling**: The program handles various error cases:
   - Attempting to add an existing user
   - Operations on non-existent users
   - Invalid commands

3. **Memory Management**: All dynamically allocated memory is properly deallocated when the program exits.

## Implementation Details

### AVL Tree
- Posts are inserted with timestamps
- Maintains balance through rotations
- Supports reverse in-order traversal for chronological output

### Graph Operations
- BFS for shortest path calculation (degrees of separation)
- Friend suggestions using mutual friend counting
- Efficient friend list management using ordered sets

### Time Complexity
- Add User: O(1)
- Add Friend: O(log n) where n is the number of friends
- List Friends: O(k) where k is the number of friends
- Suggest Friends: O(f × m + k log k) where f is friends count, m is average friends of friends, k is candidates
- Degrees of Separation: O(V + E) using BFS
- Add Post: O(log p) where p is the number of posts
- Output Posts: O(n) where n is the requested number of posts

## Example Session

```
SocialNet
Enter commands:
ADD_USER alice
User 'alice' added.
ADD_USER bob
User 'bob' added.
ADD_USER charlie
User 'charlie' added.
ADD_FRIEND alice bob
ADD_FRIEND bob charlie
LIST_FRIENDS alice
bob
DEGREES_OF_SEPARATION alice charlie
Degrees of Separation: 2
ADD_POST alice My first post!
OUTPUT_POSTS alice -1
Timestamp: Wed Oct 29 12:00:00 2025
   Post: My first post!
EXIT
```

