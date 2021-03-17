/*
 * gameplay.h
 *
 *  Created on: Mar. 16, 2021
 *      Author: samuel
 */

#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_
#include <iostream>
#include <vector>
#include <iomanip>
#include "Visual/initGraph.h"
#include "Visual/initLevels.h"
#include "Visual/Room.h"
#include "Visual/Levels.h"
#include "item/Item.h"


char inTown(Merchandise& townMerchandise, Character& mainPlayer){
//Will probably need to receive the player to access his inventory
	char option;
	char buyOption;
	size_t itemToBuy;
	int quantityToBuy;
	int totalPrice;
	Item* itemToBuyObject;
	int qteObject;
	map<Item *, int>::iterator it;
	int i = 0;
	map<Item*, int> townSalesList = townMerchandise.getSaleList();
	Inventory playerInventory = mainPlayer.getMyInventory();
	int qteRemaining;


	cout << "\tWhat would you like to do ?" << endl << endl;
	cout << "\th - Heal yourself" << endl;
	cout << "\tb - See what the merchands have to offer" << endl;
	cout << "\ti - See your inventory" << endl;
	cout << "\tn - Go to the next level" << endl;

	cin >> option;

	switch(option){
	case('h'):

			//Put the player's health to max health
			mainPlayer.setHealth(mainPlayer.getMaxHp());
			cout << "\tYour player's health is now at the max ! " << endl;
			break;

	case('b'):
		cout << "\tHere is what is in store for this town !" << endl << endl;
		townMerchandise.printInfo();
		cout << endl;
		cout << "\tWould you like to buy something ? (y/n)" << endl;
		cin >> buyOption;

		while(buyOption != 'y' && buyOption != 'n'){
			cout << "\tNot a valid option, choose between y and n" << endl;
			cin >> buyOption;
		}

		if(buyOption == 'y'){
			//IMPLEMENT MECHANICS TO BUY AN ITEM WHICH SHOULD BE :
			//Ask for the number of the item
			cout << "Enter the index number of the item you would like to buy" << endl;
			cin >> itemToBuy;

			//Check that number is valid
			while(itemToBuy > townMerchandise.getSaleList().size()){
				cout << "\tNot a valid option, choose a number smaller than" << townMerchandise.getSaleList().size() << endl;
				cin >> itemToBuy;
			}

			for (it = townSalesList.begin(); it != townSalesList.end(); it++){
				if(it->second>0)
					i++;
				if(i == itemToBuy){
					qteObject = it->second;
					itemToBuyObject = it->first;
					break;
				}
			}

			//Ask for the quantity
			cout << "How many of these would you like to buy ?" << endl;
			cin >> quantityToBuy;

			//Check that the quantity is valid
			while(quantityToBuy > qteObject){
				cout << "\tNot a valid option, choose a number smaller than" << townMerchandise.getSaleList().size() << endl;
				cin >> quantityToBuy;
			}

			qteRemaining = qteObject - quantityToBuy;

			totalPrice = itemToBuyObject->getBuyPrice() * quantityToBuy;

			//Check if player has enough money
			if(mainPlayer.getMoney() > totalPrice){
				//if yes, buy. (remove from shop, put in his inventory, remove the money from his inventory)
				mainPlayer.removeMoney(totalPrice);
				for(int j = 0; j < quantityToBuy; j++)
					mainPlayer.pickUpItem(itemToBuyObject);

				//BUG WITH THE MERCHAND
				for (it = townSalesList.begin(); it != townSalesList.end(); it++){
					if(it->second>0)
						i++;
					if(i == itemToBuy){
						if(qteRemaining == 0)
							townSalesList.erase(itemToBuyObject);
						else
							it->second = qteRemaining;
					}
				}
				townMerchandise.setSaleList(townSalesList);

			} else{
				cout << "\tYou don't have enough money to buy item # " << itemToBuy << " " << quantityToBuy << " times" << endl;
			}

			//if not, say that he doesn't have enough money and ask if he wants to buy something else
		} else {
			cout << "\tOk, no problem, good luck on your adventure !" << endl;
		}
		break;

	case('i'):
		//Show the player's inventory
		cout << "\tHere are your potions: " << endl << endl;
		playerInventory.showPotions();
		cout << endl;
		cout << "\tHere are your weapons: " << endl << endl;
		playerInventory.showWeapons();
		cout << endl;
		cout << "\tHere is your gold: " << endl << endl;
		playerInventory.showMyMoney();
		cout << endl;
		cout << "\tAnd you have this amount of money: " << endl << endl;
		cout << "\t" << mainPlayer.getMoney() << "$";
		cout << endl << endl;

		break;

	case('n'):
		break;

	default:

		cout << "\tNot a valid option" << endl;
		break;

	}
	return option;
}

char inFight(Character& enemy, Character& player, bool isBoss, Room currRoom, Graphics currDisplay){

	char option;

	//Prompt the player
	// for drink a potion, fighting or running
	//if (Boss), you can't run

	cout << "\tWhat would you like to do ?" << endl << endl;
	cout << "\tf - Attack the monster" << endl;
	cout << "\th - Drink a potion from your inventory" << endl;
	//TO BE IMPLEMENTED
	cout << "\tr - Run away from the monster" << endl;

	cin >> option;

	system("clear");

	cout << endl << endl << "\t\t\t\t\tYou are in Room #" << currRoom.getRoomNumber() << endl;
	//Print the first screen
	currDisplay.PrintDisplay();



	//if fight
	//attack the enemy
	if(option == 'f'){
		player.basicAttack(&enemy);
		cout << endl;
	}
	//else if run

	else if(option == 'r'){
		//FOR NOW YOU CAN'T
		if(isBoss){
			cout << "\tThis is the boss, you can't run !" << endl;
		}
	}
	//else if you drink a potion

	else if(option == 'h'){
		//your health goes up
		player.drinkPotion();
	}
	//Not a valid option
	else{
		cout << "\tNot a valid option" << endl;
	}
	if(!enemy.isAlive())
		return option;

	//Then the enemy attacks you
	enemy.basicAttack(&player);
	cout << endl;

	return option;
}

void mainGameplay(){
	//Creating the game
	vector<Levels> wholeGame;
	Levels level1;
	Levels level2;
	Levels currLevel;
	Character currMonster;

	createLevelOne(level1);
	createLevelTwo(level2);

	wholeGame.push_back(level1);
	wholeGame.push_back(level2);


	//current Room and display of the level
	Room currRoom;
	Graphics currDisplay;

	//First chest encountered
	HP_Potion* hpPotionStart = new HP_Potion("small hp","level 1 hp potion",100,1,25);
	Weapon* myFirstSword = new Sword("wood sword","level 1 with 5% pierce through armor",100,1,100,0.55);
	Weapon* myFirstArmor = new Armor("cloth armor ","level 2 with 10% against the damage",500,2,180,0.1);

	//When the player encounters a chest
	vector<Item*> itemListTotal = getTotalListItem();
	Item* randomItemChest;
	Chest chestInRoom{"Random Chest", "A random chest in a room"};
	int randomGoldValue;

	//Variable for the game
	char directionUser;
	char useless;
	char optionChest;
	bool isFightingBoss;
	char townOutput;
	bool isPlayerAlive = true;
	bool first = true;

	//Everything to do with the town
	Graphics townDisplay = town();
	Merchandise townMerchandise("Town", "Town in between the levels");
	map<Item *, int> townSaleList;

	//Initializing the character
	string playersName;
	char charRole;


	system("clear");
	cout << "\tWelcome to the world of....." << endl;
	cout << "Please enter a name for your Character: ";
	cin >> playersName;
	cout << "Great, now what role would you like ? " << endl << endl;
	//Print the roles
	//cin >> charRole;
	//Create character with role
	Character mainPlayer(playersName, '1');


	cout << "Greetings ! ";

	mainPlayer.printCharacter();

	for(size_t i = 0; i < wholeGame.size(); i++){

			currLevel = wholeGame.at(i);
			currRoom = currLevel.getCurrRoom();
			currDisplay = currRoom.getDesign();

			system("clear");


			do{

				cout << endl << endl << "\t\t\t\t\tYou are in Room #" << currRoom.getRoomNumber() << endl;
				//Print the first screen
				currDisplay.PrintDisplay();

				//Check if there are monsters
				if(currDisplay.GetMonsters()){
					cout << "\tThere is a monster in this room !!" << endl << endl;
					//Get the monster in the room
					currMonster = currRoom.getEnemy();

					//check if the monster is the boss
					isFightingBoss = currDisplay.GetBoss();

					//If there are, fight them then continue

					//IMPLEMENT FIGHT MECHANICS

					cout << "\tThe monster in this room is:" << endl << endl;
					currMonster.printCharacter();

					//while(the enemy is alive)
					while(currMonster.isAlive()){
						//Prompt the player
						// for drink a potion, fighting or running
						//if (Boss), you can't run

						cout << "\tYou have : " << setw(15) << mainPlayer.getHp() << " health points" << endl;
						cout << "\tAnd the enemy has : " << setw(6) << currMonster.getHp() << " health points" << endl << endl;

						inFight(currMonster, mainPlayer, isFightingBoss, currRoom, currDisplay);

						//is the player alive

						isPlayerAlive = mainPlayer.isAlive();
						//if not cout dead balbalbla
						if(!isPlayerAlive){
							cout << "\tYou died !" << endl;
							break;
						}
						//if yes loop again
					}





					//we won and it was the boss, say boss is dead in the level
					if(isFightingBoss && isPlayerAlive){
						currLevel.setBossStatus(false);
						cout << "\tCongratulations ! The boss is dead ! Let's go to a town to celebrate ! (Press any key then enter to go to the town)" << endl;
						cin >> useless;
						break;
					}
					if(isPlayerAlive){
						cout << "\tCongratulations ! You won against the monster !" << endl;
					}
				}
				if(!isPlayerAlive)
					break;
				//Check if there is a chest
				if(currDisplay.GetChest()){
					//If there is a chest, ask the player if he wants to open it
					cout << "\t There is a chest in this room ! Would you like to open it ? (y/n)" << endl;
					cin >> optionChest;
					cout << endl << endl;

					if(optionChest == 'y' ||optionChest == 'Y'){

						if(first){
							first = false;

							cout << "\tIn the box, you found: " << endl;
							cout << "\t";
							myFirstSword->printInfo();
							cout << endl;
							cout << "\t";
							myFirstArmor->printInfo();
							cout << endl << "\tAnd 2 small health potions of 25 hp each !" << endl << endl;

							cout << "\tYour sword and cloth armor are now equipped !" << endl;

							mainPlayer.equipArmor(myFirstArmor);
							mainPlayer.equipMainWeapon(myFirstSword);
							mainPlayer.pickUpItem(hpPotionStart);
							mainPlayer.pickUpItem(hpPotionStart);
							cout << endl;


						} else {
							//Generate the random item
							cout << "\tIn the box, you found: " << endl;
							cout << "\t";
							randomItemChest = chestInRoom.openBox(itemListTotal);
							cout << endl;
							mainPlayer.pickUpItem(randomItemChest);

							//Generate the random amount of money
							randomGoldValue = rand() % 1000;
							cout << "\tAnd " << randomGoldValue << " gold !" << endl << endl;
							mainPlayer.addMoney(randomGoldValue);
							cout << endl;
						}

						//Add those to the player inventory
						//add randomItemChest
						//randomGold

						//Mark the chest as opened or something
						wholeGame.at(i).setChestState(false);

						//BUG TO FIX
						//MARK THE CHEST AS OPEN SO THE PLAYER CAN'T CONTINUOUSLY OPEN IT
						//BY GETTING IN AND OUT OF THE ROOM

					}
				}

				//DOES THE PLAYER WANTS TO ACCESS HIS INVENTORY(NOW IT'LL JUST BE DRINK POTIONS) OR GO TO ANOTHER ROOM

				//ask the user which direction he wants to go
				cout << "\tWhich direction would you like to go ? ('F' (Forward), 'R' (Right), 'L' (Left), 'B' (backward))" << endl;

				cin >> directionUser;
				//Verify that the input is ok
				while(directionUser != 'F' && directionUser != 'R' && directionUser != 'L' && directionUser != 'B' &&
						directionUser != 'f' && directionUser != 'r' && directionUser != 'l' && directionUser != 'b'){
					//If not, ask a good output
					cout << "Invalid output, please choose (F, R, L or B)" << endl;
					cin >> directionUser;
				}
				//If it is, verify that he can go to this room ( not *nullptr)
				//Done in the nextRoom of Levels
				//If he can, switch room
				currLevel.nextRoom(directionUser);


				//Reassign the current Room and Display to work with them
				currRoom = currLevel.getCurrRoom();
				currDisplay = currRoom.getDesign();

				//Clear the real terminal screen
				//For linux
				system("clear");
				//For windows
				//system("CLS");


			}while(1);
			//while(!currLevel.getBossStatus());

			if(!isPlayerAlive)
				break;

			//When boss is defeated, we should go to the town.
			system("clear");
			townDisplay.PrintDisplay();

			cout << "\tYou reached a town. You must be exhausted !" << endl;

			//Clear old sale list of the town
			townSaleList.clear();

			//Generate the inventory of the Town
			for (Item *item: itemListTotal) {
				townSaleList.emplace(item, Merchandise::getRandomNumByLevel(item));
			}

			townMerchandise.setSaleList(townSaleList);

			do{
				//Call to inTown while output is not n
				townOutput = inTown(townMerchandise, mainPlayer);
			}while(townOutput != 'n');
		}
}



#endif /* GAMEPLAY_H_ */
