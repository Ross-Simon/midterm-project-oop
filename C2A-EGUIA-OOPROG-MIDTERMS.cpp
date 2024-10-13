// Eguia, Ross Simon S. (Midterm Examination - Object Oriented Programming)

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cctype> 

using namespace std;

// For Case Insensitivity
string toUpper(const string& str) {
    string upperStr;
    for (char ch : str) {
        upperStr += toupper(ch);
    }
    return upperStr;
}

// Abstract Class for displaying
class InventoryItem {
public:
    virtual void display() const = 0; // Virtual Function for displaying
    virtual ~InventoryItem() {} // Virtual Destructor after displaying
};

// Encapsulated Item Class
class Item : public InventoryItem {
private:
    string id, name, category;
    int quantity;
    double price;

public:
    Item(string id, string name, int quantity, double price, string category) 
        : id(id), name(name), quantity(quantity), price(price), category(category) {} // Initialization List

    // Getters
    string getId() const {
        return id; 
    }
    
    string getName() const {
        return name; 
    }
    
    string getCategory() const {
        return category; 
    }
    
    int getQuantity() const {
        return quantity; 
    }
    
    double getPrice() const {
        return price; 
    }

    // Setters
    void setQuantity(int qty) {
        quantity = qty; 
    }
    
    void setPrice(double prc) { 
        price = prc; 
    }

    void setCategory(const string& cat) {
        category = cat;
    }

    void display() const override {
        cout << left << setw(10) << id << setw(20) << name
             << setw(10) << quantity << setw(10) << fixed << setprecision(2) << price
             << setw(15) << category << endl;
    }
};

// Inventory Class
class Inventory {
private:
    vector<Item> items;
    const vector<string> validCategories = {"CLOTHING", "ELECTRONICS", "ENTERTAINMENT"}; // Valid categories

public:
    Inventory() : items{
        Item("01C", "Type A Shirt", 5, 250.00, "CLOTHING"),
        Item("02C", "Type A Pants", 50, 300.00, "CLOTHING"),
        Item("03C", "Type A Dress", 50, 350.00, "CLOTHING"),
        Item("01E", "Type A Phone", 20, 14999.00, "ELECTRONICS"),
        Item("02E", "Type A Laptop", 20, 39999.00, "ELECTRONICS"),
        Item("03E", "Type A Tablet", 20, 23999.00, "ELECTRONICS"),
        Item("01EN", "Type A Toy", 100, 200.00, "ENTERTAINMENT"),
        Item("02EN", "Type A Game Console", 20, 45000.00, "ENTERTAINMENT"),
        Item("03EN", "Type A Game CD", 100, 500.00, "ENTERTAINMENT")
    } {}

    void addItem(const Item& item) {
        items.push_back(item);
    }
    
    bool removeItem(const string& id, string& itemName) {
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].getId() == id) {
                itemName = items[i].getName(); // Get the name of the item
                items.erase(items.begin() + i);
                return true; // If item removed successfully
            }
        }
        itemName = ""; // Set itemName to empty if not found
        return false; // If item not found
    }
    
    void displayItemsByCategory(const string& category) const {
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
        for (const auto& item : items) {
            if (toUpper(item.getCategory()) == toUpper(category)) {
                item.display();
            }
        }
    }
    
    void displayAllItems() const {
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;
        for (const auto& item : items) {
            item.display();
        }
    }

    Item* findItemById(const string& id) {
        for (auto& item : items) {
            if (item.getId() == id) return &item;
        }
        return nullptr;
    }

    // sorting items through bubble sort
	void sortItems(int sortChoiceQP, int sortChoiceAD) { 
	        bool swapped;
	        for (size_t i = 0; i < items.size(); ++i) {
	            swapped = false;
	            for (size_t j = 0; j < items.size() - 1 - i; ++j) {
	                bool condition = (sortChoiceQP == 1) ? 
	                    (sortChoiceAD == 1 ? items[j].getQuantity() > items[j + 1].getQuantity() :
	                                         items[j].getQuantity() < items[j + 1].getQuantity()) :
	                    (sortChoiceAD == 1 ? items[j].getPrice() > items[j + 1].getPrice() :
	                                         items[j].getPrice() < items[j + 1].getPrice());
	
	                if (condition) {
	                    swap(items[j], items[j + 1]);
	                    swapped = true;
	                }
	            }
	            if (!swapped) 
				break; // stop if no swaps occurred
	        }
	}
    
    void displayLowStockItems() const {
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(10) << "Category" << endl;
        for (const auto& item : items) {
            if (item.getQuantity() <= 5) {
                item.display();
            }
        }
    }

    bool isValidCategory(const string& category) const {
        for (const auto& valid : validCategories) {
            if (toUpper(valid) == toUpper(category)) {
                return true;
            }
        }
        return false;
    }
    
    vector<Item>& getItems() {
        return items;
    }
};

// Add Item Class
class AddItem {
private:
	Inventory& inventory;

public:
	AddItem(Inventory& inv) : inventory(inv) {}
	
	void execute() {
	    string id, name, category;
	    int quantity;
	    double price;
		 
		system("cls"); 
		cout << "\n[ADD ITEM]\n\n"; 
		cout << "\nCategories:\n"; 
		cout << "\n1. Clothing"; 
		cout << "\n2. Electronics"; 
		cout << "\n3. Entertainment";   
	    cout << "\n\nEnter category: ";
	    cin >> category;
	    cout << "Enter ID: ";
	    cin >> id;
	
	    id = toUpper(id);
	    category = toUpper(category);
	
	    if (inventory.findItemById(id)) {
	        cout << "\nItem ID already exists. Please use a unique ID.\n";
	        return;
	    }
	
	    cout << "Enter Name: ";
	    cin >> name;
	
	    cout << "Enter Quantity: ";
	    while (true) {
	        cin >> quantity;
	        if (cin.fail() || quantity < 0) {
	            cin.clear();
	            cin.ignore(10000, '\n');
	            cout << "\nInvalid input. Please enter a non-negative integer for Quantity: ";
	        } else {
	            cin.ignore(10000, '\n');
	            break;
	        }
	    }
	
	    cout << "Enter Price: ";
	    while (true) {
	        cin >> price;
	        if (cin.fail() || price < 0) {
	            cin.clear();
	            cin.ignore(10000, '\n');
	            cout << "\nInvalid input. Please enter a non-negative number for Price: ";
	        } else {
	            cin.ignore(10000, '\n');
	            break;
	        }
	    }
	
	    inventory.addItem(Item(id, name, quantity, price, category));
	    cout << "\nItem added successfully!\n";
	    system("pause"); 
		system("cls");     
	}
};

// Update Item Class
class UpdateItem {
private:
	Inventory& inventory;

public:
	UpdateItem(Inventory& inv) : inventory(inv) {}

	void execute() {
	    string id;

        system("cls");
        cout << "\n[REMOVE ITEM]\n\n";
        inventory.displayAllItems();  
        
	    cout << "\nEnter ID: ";
	    cin >> id;
	    id = toUpper(id); 
	    Item* item = inventory.findItemById(id);
	    if (item) {
	    	string newCategory; 
	        int newQuantity;
	        double newPrice;
	        
	        cout << "Enter new Category: ";
            cin >> newCategory;
            newCategory = toUpper(newCategory);
			if (!inventory.isValidCategory(newCategory)) {
                cout << "Invalid category! Please enter a valid category (CLOTHING, ELECTRONICS, ENTERTAINMENT).\n";
                system("pause"); 
				system("cls"); 
                return execute();
            }

	        cout << "Enter new Quantity: ";
	        while (true) {
	            cin >> newQuantity;
	            if (cin.fail() || newQuantity < 0) {
	                cin.clear();
	                cin.ignore(10000, '\n');
	                cout << "\nInvalid input. Please enter a non-negative integer for Quantity: ";
	            } else {
	                cin.ignore(10000, '\n');
	                break;
	            }
	        }
	
	        cout << "Enter new Price: ";
	        while (true) {
	            cin >> newPrice;
	            if (cin.fail() || newPrice < 0) {
	                cin.clear();
	                cin.ignore(10000, '\n');
	                cout << "\nInvalid input. Please enter a non-negative number for Price: ";
	            } else {
	                cin.ignore(10000, '\n');
	                break;
	            }
	        }
	
	        item->setQuantity(newQuantity);
	        item->setPrice(newPrice);
	        cout << "\nItem updated successfully!\n";
	    	system("pause"); 
			system("cls"); 
	    } else {
	        cout << "\nItem not found! Please try again.\n";
	        system("pause"); 
			system("cls"); 
	        return execute(); 
	    }
	}
};

// Remove Item Class
class RemoveItem {
private:
    Inventory& inventory;

public:
    RemoveItem(Inventory& inv) : inventory(inv) {}

    void execute() {
        string id, itemName;
        
        system("cls");
        cout << "\n[REMOVE ITEM]\n\n";
        inventory.displayAllItems();  
        cout << "\nEnter ID: ";
        cin >> id;
        id = toUpper(id); 
        if (inventory.removeItem(id, itemName)) { // to check if item was removed
            cout << "\nItem " << itemName << " has been removed from the inventory.\n";
            system("pause"); 
			system("cls"); 
			
        } else {
            cout << "\nItem not found! Please try again.\n";
            system("pause"); 
			system("cls"); 
	        return execute(); 
        }
    }
};

// Display Items by Category Class
class DisplayItemsByCategory {
private:
    Inventory& inventory;

public:
    DisplayItemsByCategory(Inventory& inv) : inventory(inv) {}

    void execute() {
        string category;

        system("cls");
        cout << "\n[DISPLAY ITEMS BY CATEGORY]\n\n";  
        cout << "Categories:\n"; 
        cout << "1. Clothing\n"; 
        cout << "2. Electronics\n"; 
        cout << "3. Entertainment\n";  
        cout << "\nEnter category: ";
        cin >> category;
        category = toUpper(category); 

        if (!inventory.isValidCategory(category)) {
            cout << "\nInvalid category! Please enter a valid category (CLOTHING, ELECTRONICS, ENTERTAINMENT).\n";
            system("pause"); 
			system("cls"); 
	        return execute();
        }
        cout << endl; 
        inventory.displayItemsByCategory(category);
        cout << endl; 
        system("pause"); 
		system("cls"); 
    }
};

// Search Item Class
class SearchItem {
private:
    Inventory& inventory;

public:
    SearchItem(Inventory& inv) : inventory(inv) {}

    void execute() {
        string id;
        system("cls");
        cout << "\n[SEARCH ITEM]\n\n";  
        cout << "Enter ID: ";
        cin >> id;
        id = toUpper(id); 
        Item* item = inventory.findItemById(id);
        if (item) {
            cout << "\nID: " << item->getId() << " | Name: " << item->getName()
                 << " | Quantity: " << item->getQuantity() << " | Price: " << fixed << setprecision(2) << item->getPrice()
                 << " | Category: " << item->getCategory() << endl;
            cout << endl;  
            system("pause"); 
			system("cls");   
        } else {
            cout << "\nItem not found! Please try again.\n";
            system("pause"); 
			system("cls"); 
	        return execute();
        }     
    }
};

// Display Low Stock Items Class
class DisplayLowStockItems {
private:
    Inventory& inventory;

public:
    DisplayLowStockItems(Inventory& inv) : inventory(inv) {}

    void execute() {
    	system("cls");
        cout << "\n[DISPLAY LOW STOCK ITEMS]\n\n";  
        inventory.displayLowStockItems();
        cout << endl; 
        system("pause"); 
		system("cls"); 
    }
};

// Sort Items Class
class SortItems {
private:
    Inventory& inventory;

public:
    SortItems(Inventory& inv) : inventory(inv) {}

    void execute() {
        int sortChoiceQP; // Sort Choice (Quantity or Price)
        int sortChoiceAD; // Sort Choice (Ascending or Descending)

        system("cls");
        cout << "\n[Sort Items]\n\n";
        cout << "Sort by:\n";
        cout << "1. Quantity\n";
        cout << "2. Price\n";
        cout << "\nEnter option (1 or 2): ";
        cin >> sortChoiceQP;

        // Validate sort choice
        while (sortChoiceQP != 1 && sortChoiceQP != 2) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid option! Please enter 1 for Quantity or 2 for Price: ";
            cin >> sortChoiceQP;
        }

        cout << "\nSort order:\n";
        cout << "1. Ascending\n";
        cout << "2. Descending\n";
        cout << "\nEnter option (1 or 2): ";
        cin >> sortChoiceAD;

        while (sortChoiceAD != 1 && sortChoiceAD != 2) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid option! Please enter 1 for Ascending or 2 for Descending: ";
            cin >> sortChoiceAD;
        }

        inventory.sortItems(sortChoiceQP, sortChoiceAD);

        cout << endl; 
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
        inventory.displayAllItems();
        cout << endl; 
        system("pause");
        system("cls");
    }
};

int main() {
    Inventory inv; 

    AddItem addItem(inv);
    UpdateItem updateItem(inv);
    RemoveItem removeItem(inv);
    DisplayItemsByCategory displayItemsByCategory(inv);
    DisplayLowStockItems displayLowStockItems(inv);
    SearchItem searchItem(inv);
    SortItems sortItems(inv);

    int menuChoice;

    do {
        cout << "\n-----------------------------------\n";
        cout << "    Inventory Management System\n";
        cout << "-----------------------------------\n";
        cout << "\nMenu:";
        cout << "\n[1] Add Item\n";
        cout << "[2] Update Item\n";
        cout << "[3] Remove Item\n";
        cout << "[4] Display Items by Category\n";
        cout << "[5] Display All Items\n";
        cout << "[6] Search Item\n";
        cout << "[7] Display Low Stock Items\n";
        cout << "[8] Sort Items\n";
        cout << "[9] Exit\n";
        cout << "\nChoose an option [1-9]: ";
        cin >> menuChoice;
        cout << endl;

        switch (menuChoice) {
            case 1: 
                addItem.execute(); 
                break;
                
            case 2: 
                updateItem.execute(); 
                break;
                
            case 3: 
                removeItem.execute(); 
                break;
                
            case 4: 
                displayItemsByCategory.execute();
                break;
                
            case 5: 
            	system("cls");
				cout << "\n[DISPLAY ALL ITEMS]\n\n"; 
                inv.displayAllItems(); 
                cout <<endl; 
                system("pause"); 
				system("cls"); 
                break;
                
            case 6: 
                searchItem.execute(); 
                break;
                
            case 7: 
                displayLowStockItems.execute(); 
                break;
                
            case 8: 
                sortItems.execute(); 
                break;
                
            case 9: 
                cout << "\nExiting...\n"; 
                break;
                
            default: 
                cout << "\nInvalid Input. Please try again.\n"; 
            	cin.clear();
            	cin.ignore(1000, '\n');
            	system("pause"); 
				system("cls"); 
                break;
                
        }
    } while (menuChoice != 9);

    return 0;
}