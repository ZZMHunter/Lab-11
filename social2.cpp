/*
    Author: Zhao Zhang
    Course: CSCI-135
    Instructor: Tong Yi
    Assignment: Lab-11 B

    Class Network: Adds new users, following, posting messages

    Array of user "profiles"
    Integer "numUsers" stores number of users
    Size of "profiles" array defined as MAX_USERS=20
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
        }
        bool addUser(std::string usrn, std::string dspn){
            profiles[numUsers] = Profile(usrn, dspn);
            numUsers++;
        }
};

int main(){
    Network nw;
    std::cout << nw.addUser("mario", "Mario") << std::endl;
    std::cout << nw.addUser("luigi", "Luigi") << std::endl;

    std::cout << nw.addUser("mario", "Mario2") << std::endl;
    std::cout << nw.addUser("mario 2", "Mario2") << std::endl;
    std::cout << nw.addUser("mario-2", "Mario2") << std::endl;

    for(int i = 2; i < 20; i ++){
        std::cout << nw.addUser("mario"+std::to_string(i), "Mario"+std::to_string(i)) << std::endl;
    }
    std::cout << nw.addUser("yoshi", "Yoshi") << std::endl;
}