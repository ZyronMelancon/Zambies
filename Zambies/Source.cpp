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

I will add/fix the missing functions and refine the interface between the user and
game. I will be cleaning up unused variables. I will also be adding randomization 
for a sense of luck. 
*/

struct Zambie
{
	int health;
	bool alive;
	int spirit;
	string name;
};

struct Ninja
{
	int health;
	bool alive;
	int chi;
	string name;
};

/* The functions of Spirit and Chi are equivalent. A Ninja needs chi for various moves,
and a Zambie needs spirit to attack. If the value drops below 1, they cannot perform attacks. 
The battle will stop if both characters' chi and spirit drop below 1. */


/* Zambie attack sequence */

int zAttack(Zambie z[], Ninja n[])
{
	int y;

	int randomAttack = rand() % 30 + 1; 

	for (int x = 0; x < 2; x++)
	{
		if (z[x].spirit > 0)
		{
			y = rand() % 2;

			cout << z[x].name << " is attacking " << n[y].name << "!" << endl;
			n[y].health -= randomAttack;
			cout << n[y].name << " took " << randomAttack << " damage. His health is now " << n[y].health << "." << endl;
			z[x].spirit -= 1;
			cout << z[x].name << "'s spirit is now " << z[y].spirit << "." << endl;
		}
		else
			cout << z[x].name << " has no more spirit! He cannot attack!" << endl;
	}

	return 1;
}


/* Ninja attack sequence */

int nAttack(Zambie z[], Ninja n[], int x, int y)
{
	x--;

	int random = rand() % 30 + 1;

	if (n[y].chi > 0)
	{
		cout << n[y].name << " is attacking " << z[x].name << "!" << endl;
		z[x].health -= random;
		cout << z[x].name << " took " << random << " damage. His health is now " << z[x].health << "." << endl;
		n[y].chi -= 1;
		cout << n[y].name << "'s chi is now " << n[y].chi << "." << endl;
	}
	else
		cout << n[y].name << " has no more chi! He cannot attack!" << endl;

	return 1;
}


/* This move allows a Ninja to steal a Zambie's spirit in exchange for a bit of health. */

int nSteal(Zambie z[], Ninja n[], int x, int y)
{
	x--;

	int random = rand() % 3;
	int random2 = rand() % 10 + 1;

	if (z[x].spirit > 0)
	{
		cout << n[y].name << " tests his luck and attempts to steal " << z[x].name << "'s spirit." << endl;

		z[x].spirit -= random;
		n[y].chi += random;
		n[y].health -= random2;
		cout << n[y].name << "'s chi is now " << n[y].chi << " and " << z[x].name << "'s spirit is now " << z[x].spirit << "." << endl;
		cout << z[x].name << " attacked " << n[y].name << " during his vulnerability, bringing his health down to " << n[y].health << "." << endl;
	}
	else
		cout << "Zambie does not have any spirit to steal!" << endl;

	return 1;
}


/* This move allows a Ninja to heal by a random amount (up to 25) in exchange for 1 chi. */

int nHeal(Ninja n[], int y)
{
	int random = rand() % 21 + 5;

	if (n[y].chi > 0)
	{
		cout << n[y].name << " used his chi to heal by " << random << "." << endl;
		n[y].health += random;
		n[y].chi -= 1;
		cout << "His health is now " << n[y].health << " and he has " << n[y].chi << " chi." << endl;
	}
	else
		cout << n[y].name << " has no more chi! He cannot heal!" << endl;

	return 1;
}


/* Here, we check if the characters' health is below 1. If so, their "alive" state is set to false. */

int checkAlive(Zambie z[], Ninja n[])
{
	for (int i = 0; i < 2; i++)
	{
		if (z[i].health < 1)
			z[i].alive = false;
		else
			z[i].alive = true;

		if (n[i].health < 1)
			n[i].alive = false;
		else
			n[i].alive = true;
	}
	return 1;
}


/* Full game sequence. This is a turn-based RPG-style battle sequence between Zambies and Ninjas.
The user is in control of the Ninjas, and has a set of moves to choose from. Both Ninja and Zambie 
have matching amounts of health and chi/spirit, but the values of each move is randomized, making 
the chances of winning a bit tricky. The user must play their moves wisely in order to win. */

int main()
{
	Zambie zamb[2];

	zamb[0] = { 100, true, 10, "Chris" };
	zamb[1] = { 100, true, 10, "Matthew" };

	Ninja ninj[2];

	ninj[0] = { 100, true, 10, "Regi" };
	ninj[1] = { 100, true, 10, "Wilson" };

	string input;
	int turn = 1;
	bool end = false;

	cout << "Zambies vs Ninjas!" << endl;


	while (!end)
	{
		cout << "Round " << turn << "!" << endl;

		printf("\n");

		for (int x = 0; x < 2; x++)
		{
			cout << ninj[x].name << "'s health: " << ninj[x].health << endl;
			cout << ninj[x].name << "'s chi: " << ninj[x].chi << endl;

		}

		printf("\n");

		for (int x = 0; x < 2; x++)
		{
			cout << zamb[x].name << "'s health: " << zamb[x].health << endl;
			cout << zamb[x].name << "'s spirit: " << zamb[x].spirit << endl;

		}

		printf("\n");

		for (int y = 0; y < 2; y++)
		{
			cout << "What will " << ninj[y].name << " do?" << endl;
			cout << "a. Fight   b. Heal   c. Steal   q. Quit" << endl;

			while (true)
			{
				getline(cin, input);
				int x;

				if (input[0] == 'a')
				{
					cout << "Which Zambie will you attack?" << endl;
					cout << "1. Chris   2. Matthew" << endl;
					cin >> x;

					while (true)
					{
						if (x == 1 || x == 2)
						{
							nAttack(zamb, ninj, x, y);
							break;
						}
						else
							cout << "Invalid number!" << endl;
					}
					break;
				}
				else if (input[0] == 'b')
				{
					nHeal(ninj, y);
					break;
				}
				else if (input[0] == 'c')
				{
					cout << "Which Zambie will you steal from?" << endl;
					cout << "1. Chris   2. Matthew" << endl;
					cin >> x;

					while (true)
					{
						if (x == 1 || x == 2)
						{
							nSteal(zamb, ninj, x, y);
							break;
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

		if (!end)
		{
			printf("\n");
			checkAlive(zamb, ninj);

			for (int i = 0; i < 2; i++)
			{
				if (!ninj[i].alive)
				{
					cout << ninj[i].name << " is dead!" << endl;
					break;
				}
				else if (!zamb[i].alive)
				{
					cout << zamb[i].name << " is dead!" << endl;
					break;
				}
			}

			if (ninj[0].chi < 1 && zamb[0].spirit < 1 && ninj[1].chi < 1 && zamb[1].spirit < 1)
			{
				cout << "No one has chi or spirit! The battle cannot continue." << endl;
				break;
			}

			zAttack(zamb, ninj);
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