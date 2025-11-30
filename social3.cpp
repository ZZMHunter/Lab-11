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

using namespace std;
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
        int numUsers;
        bool following[MAX_USERS][MAX_USERS];
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
};

int main() {
    Network nw;
    // add three users
    nw.addUser("mario", "Mario");
    nw.addUser("luigi", "Luigi");
    nw.addUser("yoshi", "Yoshi");

    // make them follow each other
    nw.follow("mario", "luigi");
    nw.follow("mario", "yoshi");
    nw.follow("luigi", "mario");
    nw.follow("luigi", "yoshi");
    nw.follow("yoshi", "mario");
    nw.follow("yoshi", "luigi");

    // add a user who does not follow others
    nw.addUser("wario", "Wario");
    
    // add clone users who follow @mario
    for(int i = 2; i < 6; i++) {
        string usrn = "mario" + to_string(i);
        string dspn = "Mario " + to_string(i);
        nw.addUser(usrn, dspn);
        nw.follow(usrn, "mario");
    }
    // additionally, make @mario2 follow @luigi
    nw.follow("mario2", "luigi");

    nw.printDot();
}
