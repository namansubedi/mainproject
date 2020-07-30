#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>


using namespace std;

void view_contact_info()
{
  cout<<"Designed by Students of Kathmandu Uniiversity, KUSOS"<<endl;
  cout<<"For the Partial Fulfilment of Second Semester"<<endl;
  cout<<"Ishwar K.c (24)"<<endl;
  cout<<"Subask Khatri(33)"<<endl;
  cout<<"Susil Raj Neupane(34)"<<endl;
  cout<<"Naman Subedi(53)"<<endl;
  cout<<"Nayan Magar(57)"<<endl;
}

void add_record()
{
  ofstream fout;//file pointer
  fout.open("inventory.csv", ios::out | ios::app);
  string item_name;
  float price;
  int amount, item_id;
  cout<<"Enter the Item Id: "<<endl;
  cin>>item_id;
  cout<<"Enter the Item Name: "<<endl;
  cin.ignore();
  getline(cin,item_name);
  cout<<"Enter the Item Price: "<<endl;
  cin>>price;
  cout<<"Enter the Item Amount: "<<endl;
  cin>>amount;
  fout<<item_id<<","<<item_name<<","<<price<<","<<amount<<"\n";
  fout.close();//closes the file after input
}

int view_all_records()
{
  fstream fin;
  fin.open("inventory.csv", ios::in);

  string line,word;
  vector<string> row;

  cout<<"ItemId"<<"--"<<"Name"<<"--"<<"Price"<<"--"<<"Amount"<<endl;

  while (!fin.eof())
  {
    row.clear();
    line.clear();
    word.clear();
    
    getline(fin, line,'\n'); 
    if(line == "")
    {
      cout<<"End of File"<<endl;
      return 0;
    }
		stringstream s(line);
    
    while (getline(s, word, ',')) { 
			row.push_back(word); 
		} 
    cout<<row[0]<<"--"<<row[1]<<"--"<<row[2]<<"--"<<row[3]<<endl;
    s.clear();
  }
  return 1;
}

int update_record()
{ 

	// File pointer 
	fstream fin, fout; 

	// Open an existing record 
	fin.open("inventory.csv", ios::in); 

	// Create a new file to store updated data 
	fout.open("inventorynew.csv", ios::out); 

	int rollnum, roll1, marks, count = 0, i; 
	char sub; 
	int index, new_marks; 
	string line, word; 
	vector<string> row; //to store like array

	// Get the roll number from the user 
	cout << "Enter the id of the item to be updated: "; 
	cin >> rollnum; 

	// Get the data to be updated 
	cout << "Enter the value to change(amount=a,price=p): "; 
	cin >> sub; 

	// Determine the index of the subject 
	// where Maths has index 2, 
	// Physics has index 3, and so on 
	if (sub == 'p' || sub == 'P') 
		index = 2; 
	else if (sub == 'a' || sub == 'A') 
		index = 3; 
	else { 
		cout << "Invalid Choice\n"; 
    remove("reportcardnew.csv");//delete new if invalid data
		return 1;
	} 

	// Get the new marks 
	cout << "Enter new value: "; 
	cin >> new_marks; 

	// Traverse the file 
	while (!fin.eof()) { 

		row.clear(); 

		getline(fin, line); 
		stringstream s(line); 

		while (getline(s, word, ',')) { 
			row.push_back(word); 
		} 

		roll1 = stoi(row[0]); 
		int row_size = row.size(); 

		if (roll1 == rollnum) { 
			count = 1; 
			stringstream convert; 

			// sending a number as a stream into output string 
			convert << new_marks; 

			// the str() converts number into string 
			row[index] = convert.str(); 

			if (!fin.eof()) { 
				for (i = 0; i < row_size - 1; i++) { 

					// write the updated data 
					// into a new file 'reportcardnew.csv' 
					// using fout 
					fout << row[i] << ","; 
				} 

				fout << row[row_size - 1] << "\n"; 
			} 
		} 
		else { 
			if (!fin.eof()) { 
				for (i = 0; i < row_size - 1; i++) { 

					// writing other existing records 
					// into the new file using fout. 
					fout << row[i] << ","; 
				} 

				// the last column data ends with a '\n' 
				fout << row[row_size - 1] << "\n"; 
			} 
		} 
		if (fin.eof()) 
			break; 
	} 
	if (count == 0) 
		cout << "Record not found\n"; 

	fin.close(); 
	fout.close(); 

	// removing the existing file 
	remove("inventory.csv"); 

	// renaming the updated file with the existing file name 
	rename("inventorynew.csv", "inventory.csv"); 
  return 0;
}

void delete_record() 
{ 

	// Open FIle pointers 
	fstream fin, fout; 

	// Open the existing file 
	fin.open("inventory.csv", ios::in); 

	// Create a new file to store the non-deleted data 
	fout.open("inventorynew.csv", ios::out); 

	int rollnum, roll1, marks, count = 0, i; 
	char sub; 
	int index, new_marks; 
	string line, word; 
	vector<string> row; 

	// Get the roll number 
	// to decide the data to be deleted 
	cout << "Enter the id of the item to be deleted: "; 
	cin >> rollnum; 

	// Check if this record exists 
	// If exists, leave it and 
	// add all other data to the new file 
	while (!fin.eof()) { 

		row.clear(); 
		getline(fin, line); 
		stringstream s(line); 

		while (getline(s, word, ',')) { 
			row.push_back(word); 
		} 

		int row_size = row.size(); 
		roll1 = stoi(row[0]); 

		// writing all records, 
		// except the record to be deleted, 
		// into the new file 'reportcardnew.csv' 
		// using fout pointer 
		if (roll1 != rollnum) { 
			if (!fin.eof()) { 
				for (i = 0; i < row_size - 1; i++) { 
					fout << row[i] << ", "; 
				} 
				fout << row[row_size - 1] << "\n"; 
			} 
		} 
		else { 
			count = 1; 
		} 
		if (fin.eof()) 
			break; 
	} 
	if (count == 1) 
		cout << "Record deleted\n"; 
	else
		cout << "Record not found\n"; 

	// Close the pointers 
	fin.close(); 
	fout.close(); 

	// removing the existing file 
	remove("inventory.csv"); 

	// renaming the new file with the existing file name 
	rename("inventorynew.csv", "inventory.csv"); 
}

int main()
{
  home:
  int opt1;
  cout<<"********************************************"<<endl;
  cout<<"************WELCOME TO RETAIL HUB***********"<<endl;
  cout<<"********************************************"<<endl;
  cout<<endl;
  cout<<"******************MAIN MENU*****************"<<endl;
  cout<<endl;
  cout<<"     Press 1,2,3 or 4"<<endl;
  cout<<"      1) Enter Inventory"<<endl;
  cout<<"      2) Enter Clientele"<<endl;
  cout<<"         3) Make Sales"<<endl;
  cout<<"         4) Contact Us"<<endl;
  cout<<"           5) Exit"<<endl;

  cin>>opt1;

  if(opt1 == 1)
  {
  inv_page:
  int opt2;
  cout<<"********************************************"<<endl;
  cout<<"************WELCOME TO RETAIL HUB***********"<<endl;
  cout<<"********************************************"<<endl;
  cout<<endl;
  cout<<"******************INVV MENU*****************"<<endl;
  cout<<endl;
  cout<<"     Press 1,2,3,4 or 5"<<endl;
  cout<<"      1) View All Records"<<endl;
  cout<<"      2) Add Records"<<endl;
  cout<<"      3) Update Records"<<endl;
  cout<<"      4) Delete Records"<<endl;
  cout<<"      5) Back"<<endl;

  cin>>opt2;

   if(opt2 == 1)
   {
     view_all_records();
   } 
   else if(opt2 == 2)
   {
     add_record();
   }
   else if(opt2 == 3)
   {
     update_record();
   }
   else if(opt2 == 4)
   {
     delete_record();
   }
   else if(opt2 == 5)
   {
    goto home;
   }
   else
   {
     cout<<"Invalid Choice"<<endl;
     goto inv_page;
   }
   goto inv_page;
   }

   else if(opt1 == 4)
   {
     view_contact_info();
     goto home;
   }
   else if(opt1 == 2)
   {
     cout<<"clientele not coded yet"<<endl;
     goto home;
   }
   else if(opt1 == 3)
   {
     cout<<"make sales not coded yet"<<endl;
     goto home;
   }
   else if(opt1 == 5)
   {
    return 0;
   }
   else
   {
     cout<<"Invalid Choice"<<endl;
     goto home;
   }
}
