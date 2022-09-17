#include "menu.h"

using std::cout;
using std::endl;

/*
ADVANTAGES/DISADVANTAGES LINKED LIST:

One advantage for using a linked list to store the command information in this assignment is the ability to easily and efficiently add
and remove items from it. Since a core feature of the program revolves around users being able to customize the commands via the menu
and have them easily accessed from the file, this helps greatly.

One disadvantage is having to iterate through the list to search or access specific things inside of it. This is particularly an issue
with this program as you have to do so in order to look for randomized commands as well as randomized descriptions consistently.



ADVANTAGES/DISADVANTAGES ARRAY:
One advantage to using an array to store the profile information in this assignment is the ability to access any profile at any point.
This is specifically useful when adding new profiles as well as being able to easily load previous ones that were added to the
array from the .csv file.

One disadvantage is having to go through the effort to create it as a dynamically allocating array whenever a new profile is added.
This creates overly complicated and less efficient code that is prone to errors and have better alternatives available.

*/

int main()
{
    srand(time(NULL));

    Menu a;
	a.startMenu();
    return 0;
};

