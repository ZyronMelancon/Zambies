#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

/*The original program was very disbalanced and seemingly incomplete.

-There was no splashscreen, menu, or text at startup to explain the situation
or functions the user can control. There is no awareness of what to do.
-Only Zambies are able to attack Ninjas, there are no functions for Ninjas
to attack Zambies, creating a huge disbalance and no sense of challenge.
-There is no sense of what the user is controlling. Is he controlling the 
Ninja? The Zambie? The only option is to watch the Zambie attack the Ninja.
-There are no variations in attack damage. This means that there is a 
guaranteed win for the character with the highest health.
-There is no way to boost or replinish stats.
-Zambie does not stop attacking even if its Spirit is below 1.
-The text feedback is often gramatically incorrect. This is unprofessional
unless it the goal is a comedic effect.
-Giving a multiple-character input will make the game automate each character.
-There are multiple Zambies and Ninjas, two of which are not used.

I will add/fix the missing functions and refine the interface between the user and
game. I will add multi-character functions to the game, and I will also be adding 
randomization for a sense of luck. 
*/

struct Chara
{
	int health;
	bool alive;
	int mana;
	string name;
	int type;
};

/* The functions of Spirit and Chi are equivalent. A Ninja needs chi for various moves,
and a Zambie needs spirit to attack. If the value drops below 1, they cannot perform attacks. 
The battle will stop if both characters' chi and spirit drop below 1. */


/* Zambie attack sequence */

void Attack(Chara z[])
{
	int y;
	int randomAttack; 

	for (int x = 0; x < 2; x++)
	{
		if (z[x].alive)
		{
			if (z[x].mana > 0 && z[x].alive == true)
			{
				y = rand() % 2 + 2;
				randomAttack = rand() % 30 + 1;

				cout << z[x].name << " is attacking " << z[y].name << "!" << endl;
				z[y].health -= randomAttack;
				cout << z[y].name << " took " << randomAttack << " damage. His health is now " << z[y].health << "." << endl;
				z[x].mana -= 1;
				cout << z[x].name << "'s spirit is now " << z[y].mana << "." << endl;
			}
			else if (!z[y].alive)
				cout << z[y].name << " is dead!" << endl;
			else
				cout << z[x].name << " has no more spirit! He cannot attack!" << endl;
		}
	}
}


/* Ninja attack sequence */

int Attack(Chara z[], int x, int y)
{
	x--;

	int random = rand() % 30 + 1;

	if (z[y].mana > 0)
	{
		cout << z[y].name << " is attacking " << z[x].name << "!" << endl;
		z[x].health -= random;
		cout << z[x].name << " took " << random << " damage. His health is now " << z[x].health << "." << endl;
		z[y].mana -= 1;
		cout << z[y].name << "'s chi is now " << z[y].mana << "." << endl;
	}
	else
		cout << z[y].name << " has no more chi! He cannot attack!" << endl;

	return 1;
}


/* This move allows a Ninja to steal a Zambie's spirit in exchange for a bit of health. */

int Steal(Chara z[], int x, int y)
{
	x--;

	int random = rand() % 3;
	int random2 = rand() % 10 + 1;

	if (z[x].mana > 0)
	{
		cout << z[y].name << " tests his luck and attempts to steal " << z[x].name << "'s spirit." << endl;

		z[x].mana -= random;
		z[y].mana += random;
		z[y].health -= random2;
		cout << z[y].name << "'s chi is now " << z[y].mana << " and " << z[x].name << "'s spirit is now " << z[x].mana << "." << endl;
		cout << z[x].name << " attacked " << z[y].name << " during his vulnerability, bringing his health down to " << z[y].health << "." << endl;
	}
	else
		cout << "Zambie does not have any spirit to steal!" << endl;

	return 1;
}


/* This move allows a Ninja to heal by a random amount (up to 25) in exchange for 1 chi. */

int Heal(Chara n[], int y)
{
	int random = rand() % 21 + 5;

	if (n[y].mana > 0)
	{
		cout << n[y].name << " used his chi to heal by " << random << "." << endl;
		n[y].health += random;
		n[y].mana -= 1;
		cout << "His health is now " << n[y].health << " and he has " << n[y].mana << " chi." << endl;
	}
	else
		cout << n[y].name << " has no more chi! He cannot heal!" << endl;

	return 1;
}


/* Here, we check if the characters' health is below 1. If so, their "alive" state is set to false. */

int checkAlive(Chara z[])
{
	for (int i = 0; i < 4; i++)
	{
		if (z[i].health < 1)
			z[i].alive = false;
	}
	return 1;
}


/* Full game sequence. This is a turn-based RPG-style battle sequence between Zambies and Ninjas.
The user is in control of the Ninjas, and has a set of moves to choose from. Both Ninja and Zambie 
have matching amounts of health and chi/spirit, but the values of each move is randomized, making 
the chances of winning a bit tricky. The user must play their moves wisely in order to win. */

int main()
{
	Chara chara[4]; 

	chara[0] = { 100, true, 10, "Chris", 1 }; //Initializing Zambies
	chara[1] = { 100, true, 10, "Matthew", 1 };

	chara[2] = { 100, true, 10, "Regi", 2 }; //Initializing Ninjas
	chara[3] = { 100, true, 10, "Wilson", 2 };

	string input;
	int turn = 1;
	bool end = false;

	cout << "Zambies vs Ninjas!" << endl;


	//START


	while (!end) //GAME LOOP
	{
		cout << "Round " << turn << "!" << endl; //Show round number

		printf("\n");

		for (int x = 0; x < 4; x++) 
		{
			if (chara[x].alive)
			{
				cout << chara[x].name << "'s health: " << chara[x].health << endl;
				cout << chara[x].name << "'s chi: " << chara[x].mana << endl;
			}
			else
				cout << chara[x].name << " is dead!" << endl;
		}

		printf("\n");

		for (int y = 2; y < 4; y++) //Cycles through options for both Ninjas
		{
			if (chara[y].alive)
			{
				cout << "What will " << chara[y].name << " do?" << endl;
				cout << "a. Fight   b. Heal   c. Steal   q. Quit" << endl;

				while (true)
				{
					getline(cin, input);
					int x;

					if (input[0] == 'a')
					{
						while (true) //This loop makes sure you select only 1 or 2, and the defending Zambie is alive.
						{
							cout << "Which Zambie will you attack?" << endl;
							cout << "1. Chris   2. Matthew" << endl;
							cin >> x;

							if (x == 1 || x == 2)
							{
								if (chara[x-1].alive)
								{
									Attack(chara, x, y);
									break;
								}
								else
									cout << chara[x].name << " is dead! You cannot attack him." << endl;
							}
							else
								cout << "Invalid number!" << endl;
						}
						break;
					}
					else if (input[0] == 'b')
					{
						Heal(chara, y);
						break;
					}
					else if (input[0] == 'c')
					{
						while (true) //This loop makes sure you select only 1 or 2, and the defending Zambie is alive.
						{
							cout << "Which Zambie will you steal from?" << endl;
							cout << "1. Chris   2. Matthew" << endl;
							cin >> x;

							if (x == 1 || x == 2)
							{
								if (chara[x-1].alive)
								{
									Steal(chara, x, y);
									break;
								}
								else
									cout << chara[x].name << " is dead! You cannot attack him." << endl;
							}
							else
								cout << "Invalid number!" << endl;
						}
						break;
					}
					else if (input[0] == 'q')
					{
						end = true;
						break;
					}
				}
			}
		}

		if (!end)
		{
			printf("\n");

			checkAlive(chara); //After all turns end, we check health stats and set "alive" to false if any are under 1.

			//After, we check who is alive. If a team is dead, the other team wins!

			if (!chara[0].alive && !chara[1].alive) 
			{
				cout << "All Zambies are dead! Ninjas win!" << endl;
				break;
			}

			if (!chara[2].alive && !chara[3].alive)
			{
				cout << "All Ninjas are dead! Game over." << endl;
			}

			if (chara[0].mana < 1 && chara[0].mana < 1 && chara[2].mana < 1 && chara[3].mana < 1)
			{
				cout << "No one has chi or spirit! The battle cannot continue." << endl;
				break;
			}

			//Zombies attack

			Attack(chara);
			printf("\n");

			system("pause");
			system("cls");

			turn++;
		}
		else
			break;
	}

	system("pause");
	return 0;
}