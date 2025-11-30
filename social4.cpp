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

struct Post{
    std::string username;
    std::string message;
};
//A
class Profile{
    private:
        std::string username;
        std::string displayName;
    public:
        Profile(std::string usrn, std::string dspn){
            username = usrn;
            displayName = dspn;
        }
        Profile(){
            username = "";
            displayName = "";
        }
        std::string getUsername(){
            return username;
        }
        std::string getFullName(){
            std::string result = displayName;
            result += " (@)";
            result += username;
            result += ")";
            return result;
        }
        void setDisplayName(std::string dspn){
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
        int findID(std::string usrn){
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
        bool addUser(std::string usrn, std::string dspn){
            profiles[numUsers] = Profile(usrn, dspn);
            numUsers++;
        }
        //C
        bool follow(std::string usrn1, std::string usrn2){
            int follower = -1;
            int followed = -1;
            for(int i = 0; i < numUsers; i++){
                if(usrn1 == profiles[i].getUsername()){
                    follower = i;
                }
                if(usrn2 == profiles[i].getUsername()){
                    followed = i;
                }
            }
            if(follower != -1 || followed != -1){
                return false;
            }
            following[follower][followed] = true;
            return true;
        }
        void printDot(){
            for(int i = 0; i < numUsers; i++){
                std::cout << "\"@" << profiles[i].getUsername() << "\"" << std::endl;
            }
            for(int i = 0; i < numUsers; i++){
                for(int j = 0; j < numUsers; j++){
                    if (following[i][j] == true){
                        std::cout << "\"@" << profiles[i].getUsername() << "\"" <<
                                 "-> \"@" << profiles[j].getUsername() <<"\"" << std::endl;
                    }
                }
            }
        }
        //D
        bool writePost(std::string usrn, std::string msg){
            if(numPosts>=100){
                return false;
            }
            struct Post newPost = {usrn, msg};
            posts[numPosts] =  newPost;
            numPosts++;
            return true;
        }
        bool printTimeline(std::string usrn){
            int userNum = -1;
            for(int i = 0; i < numUsers; i++){
                if (profiles[i].getUsername() == usrn){
                    userNum = i;
                }
            }
            if(userNum == -1){
                return false;
            }
            for(int i = 0; i < numPosts; i++){
                for(int j = 0; j < numUsers; j++){
                    if(following[userNum][j] == true && profiles[j].getUsername() == posts[i].username){
                        std::cout << profiles[j].getFullName() << ": " << posts[i].message << std::endl;
                    }
                }
                if(profiles[userNum].getUsername() == posts[i].username){
                    std::cout << profiles[userNum].getFullName() << ": " << posts[i].message << std::endl;
                }
            }
            return true;
        }
};

int main(){
    Network nw;
    nw.addUser("mario", "Mario");
    nw.addUser("luigi", "Luigi");
    nw.addUser("yoshi", "Yoshi");

    nw.follow("mario","luigi");
    nw.follow("luigi", "mario");
    nw.follow("luigi", "yoshi");
    nw.follow("yoshi", "mario");

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

    std::cout << std::endl;
    std::cout << "======= Mario's timeline =======" << std::endl;
    nw.printTimeline("mario");
    std::cout << std::endl;

    std::cout << "======= Yoshi's timeline =======" << std::endl;
    nw.printTimeline("yoshi");
    std::cout << std::endl;
}
