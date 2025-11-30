/*
    Author: Zhao Zhang
    Course: CSCI-135
    Instructor: Tong Yi
    Assignment: Lab-11 D

    Improved version of Lab-11 C
    Allow users to post messages and remember them.
*/

#include <iostream>
#include <string>

using namespace std;
//struct Post
struct Post{
    string username;
    string message;
};
//A
class Profile{
    private:
        string username;
        string displayName;
    public:
        Profile(string usrn, string dspn){
            username = usrn;
            displayName = dspn;
        }
        Profile(){
            username = "";
            displayName = "";
        }
        string getUsername(){
            return username;
        }
        string getFullName(){
            string result = displayName;
            result += " (@)";
            result += username;
            result += ")";
            return result;
        }
        void setDisplayName(string dspn){
            displayName = dspn;
        }
};
//B
class Network{
    private:
        static const int MAX_USERS = 20;
        static const int MAX_POSTS = 100;
        int numPosts;
        int numUsers;
        bool following[MAX_USERS][MAX_USERS];
        Post posts[MAX_POSTS];
        Profile profiles[MAX_USERS];
        int findID(string usrn){
            for(int i = 0; i < MAX_USERS; i++){
                if (profiles[i].getUsername()==usrn){
                    return i;
                }
            }
            return 0;
        }
    public:
        Network(){
            numUsers = 0;
            numPosts = 0;
            for(int i = 0; i < MAX_USERS; i++){
                for(int j = 0; j < MAX_USERS; j++){
                    following[i][j] = false;
                }
            }
        }
        bool addUser(string usrn, string dspn){
            if (numUsers >= MAX_USERS) {
                return false;
            }
            if (usrn == "") {
                return false;
            }
            for (char c : usrn) {
                if (!isalnum(c)) {
                    return false;
                }
            }
            for (int i = 0; i < numUsers; i++) {
                if (profiles[i].getUsername() == usrn) {
                    return false;
                }
            }
            profiles[numUsers] = Profile(usrn, dspn);
            numUsers++;
            return true;
        }
        //C
        bool follow(string usrn1, string usrn2){
            int follower = findID(usrn1);
            int followed = findID(usrn2);

            if (follower == -1 || followed == -1) {
                return false;
            }

            following[follower][followed] = true;
            return true;
        }
        void printDot() {
            cout << "digraph {" << endl;
            for (int i = 0; i < numUsers; i++) {
                cout << "    \"@" << profiles[i].getUsername() << "\"" << endl;
            }
            for (int i = 0; i < numUsers; i++) {
                for (int j = 0; j < numUsers; j++) {
                    if (following[i][j]) {
                        cout << "    \"@" << profiles[i].getUsername()
                            << "\" -> \"@" << profiles[j].getUsername() << "\"" << endl;
                    }
                }
            }
            cout << "}" << endl;
        }
        //D
        bool writePost(string usrn, string msg){
            //has too be less than 100 posts
            if(numPosts>=100){
                return false;
            }
            //create new Post
            struct Post newPost = {usrn, msg};
            //add Post to posts[] array
            posts[numPosts] =  newPost;
            numPosts++;
            return true;
        }
        bool printTimeline(string usrn){
            int userNum = -1;
            //find ID of user
            for(int i = 0; i < numUsers; i++){
                if (profiles[i].getUsername() == usrn){
                    userNum = i;
                }
            }
            //user has to exist, otherwise return false
            if(userNum == -1){
                return false;
            }
            //reverse chronological
            for(int i = numPosts - 1; i >= 0; i--){
                for(int j = 0; j < numUsers; j++){
                    //for other users following the inputted user
                    if(following[userNum][j] == true && profiles[j].getUsername() == posts[i].username){
                        cout << profiles[j].getFullName() << ": " << posts[i].message << endl;
                    }
                }
                //posts from the user
                if(profiles[userNum].getUsername() == posts[i].username){
                    cout << profiles[userNum].getFullName() << ": " << posts[i].message << endl;
                }
            }
            return true;
        }
};

int main() {
    Network nw;
    // add three users
    nw.addUser("mario", "Mario");
    nw.addUser("luigi", "Luigi");
    nw.addUser("yoshi", "Yoshi");
    
    nw.follow("mario", "luigi");
    nw.follow("luigi", "mario");
    nw.follow("luigi", "yoshi");
    nw.follow("yoshi", "mario");

    // write some posts
    nw.writePost("mario", "It's a-me, Mario!");
    nw.writePost("luigi", "Hey hey!");
    nw.writePost("mario", "Hi Luigi!");
    nw.writePost("yoshi", "Test 1");
    nw.writePost("yoshi", "Test 2");
    nw.writePost("luigi", "I just hope this crazy plan of yours works!");
    nw.writePost("mario", "My crazy plans always work!");
    nw.writePost("yoshi", "Test 3");
    nw.writePost("yoshi", "Test 4");
    nw.writePost("yoshi", "Test 5");

    cout << endl;
    cout << "======= Mario's timeline =======" << endl;
    nw.printTimeline("mario");
    cout << endl;

    cout << "======= Yoshi's timeline =======" << endl;
    nw.printTimeline("yoshi");
    cout << endl;
}
