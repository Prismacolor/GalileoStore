#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
using namespace std;

// put the item classes here, let's try some polymorphism and inheritance 
// each item should have a name, a cost, a quantity, and an item number
class StoreItem {
public:
	int Item_number;
	string Name;
	int Quantity;
	float Price;

public:
	StoreItem() = default;
	StoreItem(int item_number, string name, int quantity, float price) {
		Name = name;
		Quantity = quantity;
		Price = price;
		Item_number = item_number;
	}

	float getTotal(int quantity, float item_price) {
		float total_cost = quantity * item_price;
		return total_cost;
	}

	virtual void getInfo() {
		cout << "Adding item to the list" << endl;
	}
};


class Weapon :public StoreItem {
public: 
	Weapon( int item_number, string name, int quantity, float price):StoreItem(item_number, name, quantity, price){
	
	}

	void getInfo() {
		cout << "Oh, you're looking for weapons? Expecting trouble, are you?" << endl;
	}
};

class Clothing :public StoreItem {
public:
	Clothing(int item_number, string name, int quantity, float price) :StoreItem(item_number, name, quantity, price) {

	}

	void getInfo() {
		cout << "Go out in style, I always say!" << endl;
	}
};

class Potion :public StoreItem {
public:
	Potion(int item_number, string name, int quantity, float price) :StoreItem(item_number, name, quantity, price) {

	}

	void getInfo() {
		cout << "If you're messing around with potions, you better know what you're doing!" << endl;
	}
};


void showMenu();
string getItemQuantity(int cust_quantity, StoreItem selection);
float getCustomerTotal(list<float> customer_amounts);
bool canCustomerPay(float purse, float total);


int main()
{
	// first create the store items for the inventory
	Weapon claymore(1, "Claymore", 13, 799.95);
	Weapon thunderHammer(2, "ThunderHammer", 7, 895.00);
	Weapon elvenArrows(3, "Elvin Arrows", 21, 375.50);
	Clothing leatherJerkin(4, "Leather Jerkin", 13, 450.25);
	Clothing wizardHat(5, "Wizard's Hat", 3, 25.50);
	Clothing shadowyCloak(6, "Shadowy Cloak", 1, 1050.75);
	Potion lovePotion(7, "Love Potion No. 9", 0, 45.50);
	Potion liquidDarkness(8, "Liquid Darkness", 3,  375.00);
	Potion restorativePotion(9, "Restorative potion", 25, 20.50);
	
	unordered_map<int, StoreItem> inventory;
	inventory.insert(make_pair(1, claymore));
	inventory.insert(make_pair(2, thunderHammer));
	inventory.insert(make_pair(3, elvenArrows));
	inventory.insert(make_pair(4, leatherJerkin));
	inventory.insert(make_pair(5, wizardHat));
	inventory.insert(make_pair(6, shadowyCloak));
	inventory.insert(make_pair(7, lovePotion));
	inventory.insert(make_pair(8, liquidDarkness));
	inventory.insert(make_pair(9, restorativePotion));

	
	// establish the variables for shopping
	float customer_purse = 575;
	string go_shopping;
	string continue_shopping;
	bool is_shopping = false;
	string customer_item;
	StoreItem current_selection;
	StoreItem* bptr;
	bool invalidItem = true;
	list<float> customer_invoice;
	string customer_q_string;
	int customer_quantity;
	float item_total;
	string quantity_check;
	float customer_total;
	string customer_response;
	bool paying = true;
	bool can_pay;

	cout << "Looks like you've arrived at Galileo's Apothecary. Do you want to go in and shop? Y or N?" << endl;
	cin >> go_shopping;
 
	if (go_shopping == "Y" || go_shopping == "y") {
		is_shopping = true;

		// start a loop for the shopping experience
		while (is_shopping) {
			cout << "Welcome to my shop. I am the renowned wizard Galileo!" << endl;
			cout << "What are you looking for, pray tell?" << endl;
			showMenu();
			cin >> customer_item;

			// we need to loop through our inventory and match the customer selection to an item.
			for (pair<int, StoreItem> element : inventory) {
				if (element.first == stoi(customer_item)) {
					invalidItem = false;
					break;
				}
				else
					continue;
			}

			if (invalidItem)
				continue;
			else {
				int item_no = stoi(customer_item);
				cout << item_no;

				if (item_no == 1) 
				{
					Weapon current_selection = claymore;
				}
				else if (item_no == 2) 
				{
					Weapon current_selection = thunderHammer;
				}
				else if (item_no == 3)
				{
					Weapon current_selection = elvenArrows; 
				}
				else if (item_no == 4)
				{
					Clothing current_selection = leatherJerkin;
				}
				else if (item_no == 5)
				{
					Clothing current_selection = wizardHat; 
				}
				else if (item_no == 6)
				{
					Clothing current_selection = shadowyCloak;
				}
				else if (item_no == 7)
				{
					Potion current_selection = lovePotion; 
				}
				else if (item_no == 8)
				{
					Potion current_selection = liquidDarkness; 
				}
				else if (item_no == 9)
				{
					Potion current_selection = restorativePotion; 
				}
				else if (item_no == 10)
				{
					cout << "Thanks for stopping by, do come back soon!" << endl;
					exit(3);
				}
				else
				{
					cout << "Invalid response. Let's try this again!" << endl;
					continue;
				}
			}

			bptr = &current_selection;
			bptr->getInfo();
			//ERR this prints nothing and doesn't show up in the description of the item in the debugger

			cout << "How many of those do you want, please?" << endl;
			cin >> customer_q_string;
			try
			{
				customer_quantity = stoi(customer_q_string);
			}
			catch (exception& e)
			{
				cout << "You've entered an invalid response. Whole numbers only, please!" << endl;
				continue;
			}

			// compare customer request to available inventory
			quantity_check = getItemQuantity(customer_quantity, current_selection);

			if (quantity_check == "out") {
				continue;
			}
			else if (quantity_check == "ok") {
				item_total = current_selection.getTotal(customer_quantity, current_selection.Price);
				// ERR 799.950012 x 1 is yielding -107374176
			}
			else {
				item_total = current_selection.getTotal(current_selection.Quantity, current_selection.Price);
			}
			customer_invoice.push_back(item_total);

			cout << "Will there be anything else? Yea or nay?" << endl;
			cin >> continue_shopping;

			if (continue_shopping == "Yea" || continue_shopping == "yea") {
				continue;
			}

			customer_total = getCustomerTotal(customer_invoice);

			while (paying) {
				cout << "Ah, that will be " << customer_total << " florins." << endl;

				cout << "What do you do next? Choose the number that corresponds with your answer." << endl;
				cout << "1. That's ridiculous. I had no idea it'd be that much. I won't pay it." << endl;
				cout << "2. Okay, that sounds good. Let me get my purse." << endl;
				cin >> customer_response;

				if (customer_response == "1") {
					cout << "Oh, a cheapskate, aye? I'll show you!" << endl;
					cout << "POOF!" << endl;
					cout << "You are now a pigeon. Coo coo..." << endl;
					exit(1);
				}
				else if (customer_response == "2") {
					can_pay = canCustomerPay(customer_purse, customer_total);
					if (can_pay) {
						cout << "Well there you go. Pleasure doing business! Do come back soon!" << endl;
						cout << "Oh, and here are some tea bags for you, on the house. Tea's good for the nerves, you know!" << endl;
						exit(1);
					}
					else {
						cout << "Not enough in your purse? SCOUNDREL! I'll teach you to short change me!" << endl;
						cout << "POOF!" << endl;
						cout << "You are now a toad...an ugly warty toad. :(" << endl;
						exit(1);
					}
				}
				else {
					cout << "Yikes, you entered an invalid response!" << endl;
					cout << "Sadly, Galileo is not a patient wizard..." << endl;
					cout << "You'd better try again before he turns you into something unpleasant!" << endl;
					continue;
				}
			}
		}	
	}
	else {
		cout << "Well maybe next time. Better keep going, it'll be dark soon!";
	}

	system("pause>0");
	return 0;
}

// functions needed for project
void showMenu() {
	cout << "********* Shop Menu *********" << endl;
	cout << "1: Claymore" << endl;
	cout << "2: ThunderHammer" << endl;
	cout << "3: Elven Arrows" << endl;
	cout << "4: Leather Jerkin" << endl;
	cout << "5: Wizard's Hat" << endl;
	cout << "6: Shadowy Cloak" << endl;
	cout << "7: Love Potion No. 9" << endl;
	cout << "8: Liquid Darkness" << endl;
	cout << "9: Restorative potion" << endl;
	cout << "10: Exit" << endl;
	cout << "********* ********* *********" << endl;
}

string getItemQuantity(int cust_quantity, StoreItem selection) {
	string gal_response;
	int leftover = 0;

	leftover = selection.Quantity - cust_quantity;
	
	if (selection.Quantity == 0) {
		cout << "Sorry, I'm all out of those!" << endl;
		gal_response == "out";
	}
	else if (leftover >= 0) {
		cout << "Very well, I'll add that to your bill!" << endl;
		gal_response = "ok";
	}
	else {
		cout << "I'm sorry, I only have " << selection.Quantity << " of those." << endl;
		cout << "I'll just sell you what I have!" << endl;
		gal_response = "not enough";
	}

	return gal_response;
}
 
float getCustomerTotal(list<float> customer_amounts) {
	float customer_total = 0;

	for (int i = 0; i < customer_amounts.size(); i++) {
		customer_total += i;
	};

	return customer_total;
}

bool canCustomerPay(float purse, float total) {
	float final_amount = purse - total;
	if (final_amount >= 0)
		return true;
	else
		return false;

}
