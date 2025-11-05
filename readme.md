# SocialNet Simulator

## COL106 Long Assignment 2

Name: Nehal Bansal  
Entry No.: 2024MT10788

A command-line social network simulator that implements core backend functionalities for managing users, friendships, and content using AVL Trees and Graphs.

## Overview

SocialNet simulates a network of users where:
- Each user is represented as a vertex in an undirected graph
- Friendships are represented as edges between vertices
- User posts are stored in an AVL Tree, sorted by timestamp for efficient chronological retrieval

## Data Structures

- **Graph**: Simulates the social network with users as vertices and friendships as edges (implemented using adjacency lists via `std::set`)
- **AVL Tree**: Efficiently stores posts sorted by creation time with self-balancing properties
- **HashMap** (`std::unordered_map`): Maps username strings to corresponding user vertices for O(1) average lookup
- **Priority Queue**: Used for ranking friend suggestions by mutual friend count

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

The program will display:
```
SocialNet
Enter commands:
```

Then wait for commands from stdin. Enter commands one per line.

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

**Output:**
```
User 'alice' added.
User 'bob' added.
```

**Error Handling:**
- If user already exists: `User '<username>' already exists.`

---

#### ADD_FRIEND
```
ADD_FRIEND <username1> <username2>
```
Establishes a bidirectional friendship between two existing users.

**Example:**
```
ADD_FRIEND alice bob
```

**Error Handling:**
- If either user doesn't exist: `Error: User '<username>' not found`
- Duplicate friendships are handled silently (set prevents duplicates)

---

#### REMOVE_FRIEND
```
REMOVE_FRIEND <username1> <username2>
```
Removes the friendship between two users if it exists.

**Example:**
```
REMOVE_FRIEND alice bob
```

**Error Handling:**
- If either user doesn't exist: `Error: User '<username>' not found`
- Non-existent friendships are handled silently

---

#### LIST_FRIENDS
```
LIST_FRIENDS <username>
```
Prints an alphabetically sorted list of the specified user's friends (one per line).

**Example:**
```
LIST_FRIENDS alice
```

**Output:**
```
bob
charlie
david
```

**Error Handling:**
- If user doesn't exist: `Error: User '<username>' not found`
- If user has no friends: No output (empty list)

---

#### SUGGEST_FRIENDS
```
SUGGEST_FRIENDS <username> <N>
```
Recommends up to N new friends who are "friends of a friend" but not already friends.

**Ranking Criteria:**
1. Ranked by number of mutual friends (descending)
2. Ties broken by alphabetical order of usernames

**Edge Cases:**
- If N is 0, outputs nothing
- If fewer than N candidates exist, lists all available
- Excludes the user themselves and existing friends

**Example:**
```
SUGGEST_FRIENDS alice 3
```

**Output:**
```
eve (Mutual Friends: 5)
frank (Mutual Friends: 3)
grace (Mutual Friends: 3)
```

**Error Handling:**
- If user doesn't exist: `Error: User '<username>' not found`

---

#### DEGREES_OF_SEPARATION
```
DEGREES_OF_SEPARATION <username1> <username2>
```
Calculates the shortest path length between two users using BFS. Returns the degree of separation.

**Example:**
```
DEGREES_OF_SEPARATION alice charlie
```

**Output:**
```
Degrees of Separation: 2
```

**Special Cases:**
- If both users are the same: `Degrees of Separation: 0`
- If no path exists: `The two users are not connected.`

**Error Handling:**
- If either user doesn't exist: `Error: User '<username>' not found`

---

### User Content Operations

#### ADD_POST
```
ADD_POST <username> <post content>
```
Adds a post with the given content to the specified user's timeline. Timestamp is automatically generated.

**Example:**
```
ADD_POST alice Hello, this is my first post!
```

**Note:** The post content is everything after the username on the same line.

**Error Handling:**
- If user doesn't exist: `Error: User '<username>' not found`

---

#### OUTPUT_POSTS
```
OUTPUT_POSTS <username> <N>
```
Outputs the most recent N posts of the user in reverse chronological order (newest first).

**Special Cases:**
- If N is -1, outputs all posts
- If fewer than N posts exist, lists all available posts

**Example:**
```
OUTPUT_POSTS alice 10
OUTPUT_POSTS alice -1
```

**Output Format:**
```
Timestamp: Wed Nov 05 14:30:45 2025
   Post: My latest post
Timestamp: Wed Nov 05 12:15:30 2025
   Post: My earlier post
```

**Error Handling:**
- If user doesn't exist: `Error: User '<username>' not found`
- If user has no posts: No output

---

### Additional Commands

#### HELP
```
HELP
```
Displays a list of all available commands with brief descriptions.

#### EXIT
```
EXIT
```
Exits the program and performs cleanup (deallocates all dynamic memory).

---

## Important Notes

1. **Case Insensitivity**: Usernames are not case-sensitive. `Alice`, `ALICE`, and `alice` are all treated as the same user. All usernames are converted to lowercase internally.

2. **Post Content**: Post content preserves its original case and whitespace.

3. **Error Handling**: The program handles various error cases gracefully:
   - Attempting to add an existing user
   - Operations on non-existent users
   - Invalid commands
   - Null node operations in AVL tree
   - Empty inputs

4. **Memory Management**: All dynamically allocated memory is properly deallocated when the program exits:
   - AVL trees are recursively deleted
   - User objects delete their posts
   - Friendships are properly cleaned up
   - Global user map is cleared

5. **Input Format**: Commands and usernames are space-separated. For `ADD_POST`, everything after `<username>` is treated as post content.

---

## Implementation Details

### AVL Tree
- **Structure**: Binary search tree with balance factor tracking
- **Insertion**: Always inserts at the rightmost position (most recent timestamp)
- **Balancing**: Performs left rotations when balance factor < -1
- **Traversal**: Reverse in-order (right → root → left) for chronological output
- **Height Update**: Maintains height information during insertions

### Graph Operations
- **Representation**: Adjacency list using `std::set<User*>` for automatic alphabetical ordering
- **BFS Implementation**: Uses level-by-level traversal with null markers for degree counting
- **Friend Suggestions**: 
  - Counts mutual friends using hash map
  - Uses max-heap (priority queue) for ranking
  - Filters out self and existing friends

### User Management
- **Username Lookup**: O(1) average time using `std::unordered_map`
- **Friendship Storage**: `std::set` with custom comparator for alphabetical order
- **Post Storage**: AVL tree sorted by timestamp

---

## Time Complexity Analysis

| Operation | Time Complexity | Explanation |
|-----------|----------------|-------------|
| **ADD_USER** | O(1) | HashMap insertion |
| **ADD_FRIEND** | O(log F) | Set insertion where F = number of friends |
| **REMOVE_FRIEND** | O(log F) | Set deletion where F = number of friends |
| **LIST_FRIENDS** | O(F) | Iterate through F friends (already sorted) |
| **SUGGEST_FRIENDS** | O(F × M + C log C) | F friends, M = avg friends per friend, C = candidates for heap operations |
| **DEGREES_OF_SEPARATION** | O(V + E) | BFS traversal where V = users, E = friendships |
| **ADD_POST** | O(log P) | AVL insertion where P = number of posts (unbalanced due to sequential insertion) |
| **OUTPUT_POSTS** | O(min(N, P)) | Traverse N posts or P total posts |



### Space Complexity
- **Graph**: O(V + E) where V = number of users, E = number of friendships
- **AVL Trees**: O(P) per user where P = number of posts
- **Username Map**: O(V)

---

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
ADD_USER david
User 'david' added.
ADD_FRIEND alice bob
ADD_FRIEND bob charlie
ADD_FRIEND alice david
LIST_FRIENDS alice
bob
david
SUGGEST_FRIENDS charlie 2
alice (Mutual Friends: 1)
DEGREES_OF_SEPARATION alice charlie
Degrees of Separation: 2
ADD_POST alice Hello everyone!
ADD_POST alice This is my second post
OUTPUT_POSTS alice -1
Timestamp: Wed Nov 05 14:32:10 2025
   Post: This is my second post
Timestamp: Wed Nov 05 14:32:05 2025
   Post: Hello everyone!
EXIT
```
