#include "menu.h"
#include "linkedlist.h"

List<string, string> cmdsList;
int profileSize = 0;

void Players::setName(string plrname)
{
    name = plrname;
};

void Players::setScore(int num)
{
    score = num;
};

string Players::getName()
{
    return name;
};

int Players::getScore()
{
    return score;
};

void Menu::displayMenu()
{
	cout << "-- Please select an option listed below: --" << endl;
	cout << "1. Game Rules" << endl;
	cout << "2. Play Game" << endl;
	cout << "3. Load Previous Game" << endl;
	cout << "4. Add Command" << endl;
	cout << "5. Remove Command" << endl;
	cout << "6. Exit" << endl;
};

int Menu::getNums(vector<int> vec, int maxNum)
{
    int num = 0;
    bool newNum = false;
    do
    {
        num = rand() % maxNum + 1;
        if (find(vec.begin(), vec.end(), num) != vec.end())
        {
            newNum = false;
        }
        else
        {
            newNum = true;
        }
    } while (newNum == false);
    return num;
};

void Menu::printRules()
{
    cout << "==:==RULES==:==" << endl;
    cout << "You are given the ability to select between 5-30 questions to run through at once." << endl;
    cout << "Each question will a randomized Linux command that you are given 3 possible definitions to." << endl;
    cout << "For each question you get right, a single point will be added to your score." << endl;
    cout << "For each question you get wrong, a single point will be removed from your score." << endl;
    cout << "Your score will save after you exit the game!" << endl;
};

Players* Menu::playGame(Players profileList[], bool bypass, int plrNum)
{
    string name = "";
    string qname = "";
    string qdesc = "";
    int qamt = 0;
    int qnum = 0;
    int qrandom = 0;

    vector<int> useddNums;
    vector<int> usedqNums;
    bool validNum = false;

    if (bypass == false)
    {
        cout << "Please enter your name: " << endl;
        cin >> name;

        Players* temp = new Players[profileSize + 1];
        for (int i = 0; i < profileSize; i++)
        {
            temp[i] = profileList[i];
        }
        //delete[] temp;
        profileList = temp;
        profileSize += 1;

        Players tempclass;
        tempclass.setName(name);
        tempclass.setScore(0);

        profileList[profileSize - 1] = tempclass;
        plrNum = profileSize - 1;
    }
    do {
        cout << "Please enter how many questions to generate (5-30): " << endl;
        cin >> qamt;
        if (qamt >= 5 && qamt <= 30)
        {
            validNum = true;
        }
    } while (validNum == false);

    for (int i = 0; i < qamt; i++)
    {
        useddNums.clear();

        qnum = getNums(usedqNums, 30);
        usedqNums.push_back(qnum);
        useddNums.push_back(qnum);
        qname = cmdsList.getnumName(qnum);
        
        cout << qname << endl;   
        qrandom = rand() % 3 + 1;
        for (int i = 1; i <= 3; i++)
        {
            if (i == qrandom) 
            {
                string name = cmdsList.getdescName(qnum);
                cout << i << ". " << name << endl;
            }
            else
            {   
                int newNum = getNums(useddNums, 30);
                useddNums.push_back(newNum);
                string name = cmdsList.getdescName(newNum);
                cout << i << ". " << name << endl;
            }
        }
        int answer = 0;
        cin >> answer;
        if (answer == qrandom)
        {
            int score = profileList[plrNum].getScore();
            score += 1;
            profileList[plrNum].setScore(score);
            cout << "Correct! " << qname << " - " << cmdsList.getdescName(qnum) << "You have been awarded 1 point. Your point total is " << profileList[plrNum].getScore() << "." << endl;
        }
        else
        {
             int score = profileList[plrNum].getScore();
            score -= 1;
            profileList[plrNum].setScore(score);
            cout << "Incorrect! " << qname << " - " << cmdsList.getdescName(qnum) << "You have lost 1 point. Your point total is " << profileList[plrNum].getScore() << "." << endl;
        }

        cout << endl;
        cout << "Press enter to continue..." << endl;
        cin.ignore();
        cin.get();
    }

    usedqNums.clear();
    useddNums.clear();
    return profileList;
};

void Menu::addCmd()
{
    string cmdname = "";
    string cmddesc = "";
    cout << "Please enter the command's name: " << endl;
    cin >> cmdname;
    cout << "Please enter the command's description: " << endl;
    cin.ignore();
    getline(cin, cmddesc);

    string newline = cmdname + ", " + "\"" + cmddesc + "\"";
    ListNode<string, string>* pNew = new ListNode<string, string>(newline);
    cmdsList.insertAtFront(pNew);

    cout << "Command added to the list!" << endl;
};

void Menu::removeCmd()
{
    string cmdname = "";
    bool validcmd = false;
    do
    {
        cout << "Please enter the command's name you'd like to remove: " << endl;
        cout << "Enter 'exitmenu' if you'd like to quit at any time." << endl;
        cin >> cmdname;
        if (cmdname == "exitmenu") 
        {
            validcmd = true;
        }
        else
        {
            validcmd = cmdsList.searchList(cmdname);
        }
    } while (validcmd == false);
    
    if (cmdname != "exitmenu") 
    {
        cout << "Command succesfully removed from the list!" << endl;
    }
};

void Menu::updatecmdCsv(ofstream& outfile)
{
    ListNode<string, string>* pTemp = cmdsList.getHeadPtr();

	while (pTemp != nullptr) // loop thru list to print to file
	{
		stringstream line;
		line << pTemp->getName() << "," << pTemp->getDesc();
        if (pTemp->getNextPtr() == nullptr)
        {
		    outfile << line.str();
        }
        else
        {
            outfile << line.str() << endl;
        }

		pTemp = pTemp->getNextPtr();
	}
};

void Menu::updateprofCsv(ofstream &outfile, Players profileList[])
{
    for (int i = 0; i < profileSize; i++)
    {
        stringstream line;
        line << profileList[i].getName() << "," << profileList[i].getScore();
        if (i + 1 == profileSize)
        {
            outfile << line.str();
        }
        else
        {
            outfile << line.str() << endl;
        }
    }
};

int Menu::findProfile(string name, Players profileList[])
{
    for (int i = 0; i < profileSize; i++)
    {
        if (profileList[i].getName() == name)
        {
            return i;
        }
    }
    return -1;
};

Players* Menu::loadProfile(Players profileList[])
{
    string name = "";
    int search = -1;

    do
    {
        cout << "Please enter your profile name: " << endl;
        cin >> name;   
        search = findProfile(name, profileList);
    } while (search == -1);
    
    cout << "Points: " << profileList[search].getScore() << endl;
    cout << "Press enter to continue..." << endl;
    cin.ignore();
    cin.get();

    profileList = playGame(profileList, true, search);

    return profileList;
};

void Menu::displayMenu(Players profileList[])
{
    int choice = 0, menu_loop = 0;

	ofstream outfileC;
	ofstream outfileP;

    while (menu_loop == 0)
	{
        cout << "\033[2J\033[1;1H"; // clear the terminal
		displayMenu();
		cin >> choice;

		switch (choice)
		{
		case 1: // game rules
			
            printRules();

			cout << "Press enter to continue..." << endl;
            cin.ignore();
            cin.get();
			break;
		case 2: // play game
			profileList = playGame(profileList, false, -1);
            
			break;
		case 3: // load prev game
			profileList = loadProfile(profileList);
            
			break;
		case 4: // add command
			addCmd();

            cout << "Press enter to continue..." << endl;
            cin.get();			
            break;
		case 5: // remove command
			removeCmd();

            cout << "Press enter to continue..." << endl;
            cin.ignore();
            cin.get();			
            break;
		case 6: // exit

            outfileC.open("/home/josh_abbott/PA1/commands.csv"); // had to direct reference the csv file
            if (outfileC.good()) // checking if it actually exists & is an option
            {
                updatecmdCsv(outfileC);
            }

            outfileC.close();

            outfileP.open("/home/josh_abbott/PA1/profiles.csv"); // had to direct reference the csv file
            if (outfileP.good()) // checking if it actually exists & is an option
            {
                updateprofCsv(outfileP, profileList); 
               
            }
            outfileP.close();

			menu_loop = 1;
			cout << "Thank you for using this program!" << endl;
			break;
		}
	}
}

void Menu::startMenu()
{
	ifstream infileC;
	ifstream infileP;

    infileC.open("/home/josh_abbott/PA1/commands.csv"); // had to direct reference the csv file
    infileP.open("/home/josh_abbott/PA1/profiles.csv"); // had to direct reference the csv file

    if (infileP.good() && infileC.good())
    {
        cmdsList.loadList(infileC); // load in list from commands.csv

        string line, input, loop;
        int i = 0;

        while (!infileP.eof())
        {
            profileSize += 1;
            cout << profileSize << endl;
            getline(infileP, line);
            stringstream newLine(line);
        }

        infileP.clear();
        infileP.seekg(0);

        Players profileList[profileSize];
        while (!infileP.eof())
	    {
		    getline(infileP, line);
		    stringstream newLine(line);

            getline(newLine, input, ',');

            if (input != "")
            {
                cout << input << endl;
                profileList[i].setName(input);
                getline(newLine, input, ',');
                profileList[i].setScore(stoi(input));
                cout << input << endl;
                i += 1;
            }
	    }

        displayMenu(profileList);
    }
    infileC.close();
    infileP.close();
};