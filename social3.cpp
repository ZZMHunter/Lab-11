/*
    Author: Zhao Zhang
    Course: CSCI-135
    Instructor: Tong Yi
    Assignment: Lab-11 C

    Improved version of previous Lab-11 B Network class
    Add private variable following[][]
    Constructor sets everthing to false in following
    Add 2 functions follow and printDot
*/

#include <iostream>
#include <string>

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

class Network{
    private:
        static const int MAX_USERS = 20;
        int numUsers;
        bool following[MAX_USERS][MAX_USERS];
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
};

int main(){
    Network nw;
    nw.addUser("mario", "Mario");
    nw.addUser("luigi", "Luigi");
    nw.addUser("yoshi", "Yoshi");

    nw.follow("mario","luigi");
    nw.follow("mario","yoshi");
    nw.follow("luigi", "mario");
    nw.follow("luigi", "yoshi");
    nw.follow("yoshi", "mario");
    nw.follow("yoshi", "luigi");

    nw.addUser("wario", "Wario");

    for(int i = 2; i < 6; i++){
        std::string usrn = "mario" + std::to_string(i);
        std::string dspn = "Mario" + std::to_string(i);
        nw.addUser(usrn, dspn);
        nw.follow(usrn, "mario");
    }

    nw.follow("mario2", "luigi");
    nw.printDot();
}
