#pragma once

#include "functions.h"

class Players
{
    public:
    void setName(string plrname);
    string getName();
    void setScore(int num);
    int getScore();

    private:
    string name;
    int score;
};

class Menu
{
public:
	void displayMenu();
	void startMenu();
    void displayMenu(Players profileList[]);
    int findProfile(string name, Players profileList[]);
    Players* loadProfile(Players profileList[]);
    int getNums(vector<int> vec, int maxNum);
    void printRules();
    Players* playGame(Players profileList[], bool bypass, int plrNum);
    void addCmd();
    void removeCmd();
    void updatecmdCsv(ofstream& outfile);
    void updateprofCsv(ofstream& outfile, Players profileList[]);

private:

};