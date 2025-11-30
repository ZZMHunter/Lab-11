/*
    Author: Zhao Zhang
    Course: CSCI-135
    Instructor: Tong Yi
    Assignment: Lab-11 A

    Implement class Profile that can store the info about a user of the network.
    Two priate properties type string: displayName and username.
    Public Interface consists of two constructors and three functions:
    -getUsername
    -getFullName
    -setDisplayname.
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

int main() {
    Profile p1("marco","Marco");
    std::cout << p1.getUsername() << std::endl;
    std::cout << p1.getFullName() << std::endl;
    p1.setDisplayName("Marco Rossi");
    std::cout << p1.getUsername() << std::endl;
    std::cout << p1.getFullName() << std::endl;
    Profile p2("tarma1", "Tarma Roving");
    std::cout << p2.getUsername() << std::endl;
    std::cout << p2.getFullName() << std::endl;
}