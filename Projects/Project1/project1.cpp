#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

// Declare functions
int calculateAge(const std::string& birthDateStr);
void printMaxAndMinCount(int array[][2]);

using namespace std;
using namespace cgicc;

int main(){
	Cgicc cgi;

	/// Initialize inputed data from the HTML page
	string name = cgi("name");
	string gender = cgi("gender");
	string ageStr = cgi("age"); // Used in case value is a string and not int
	int age = 54728; // Actual age value (54728 is being used to indicate empty value)
	bool isValid = true; // Used to indicate if stoi(cgi"age") can be used on age
	
	// Will make it so webserver does not crash if "age" does not have an int value
	// Also checks to make sure it is not empty
	if (!cgi("age").empty()){
		try {
			age = std::stoi(ageStr);
		} catch (const exception& e) {
			cout << "Content-type:text/html\r\n\r\n";
			cout << "<html>\n"; cout << "<head>\n";
			cout << "<title>Project 1</title>\n";
			cout << "</head>\n"; cout << "<body>\n";
			isValid = false;
			cout << "</body></html>\n";		
		}
	}

	int actualAge = 0;

	// Initialize birthday string and check if value from HTML is empty
	// If it is not empty it will take the value from the form
	string birthday;
	if (!cgi("birthday").empty()){
		birthday = cgi("birthday");
		actualAge = calculateAge(birthday);
	}

	string town = cgi("town");
	string myData = cgi("mydata");
	bool CPS1231_flag = cgi.queryCheckbox("CPS1231");
	bool CPS2231_flag = cgi.queryCheckbox("CPS2231");
	bool CPS2232_flag = cgi.queryCheckbox("CPS2232");
	bool CPS3250_flag = cgi.queryCheckbox("CPS3250");
	
	// For String Table
	// 128 ascii characters with 2 columns
	// The first columns holds the ASCII #
	// The second holds the count number
	int charCount[128][2] = {0}; // by default there are no counts

	// Counts each character in input string
	if (!myData.empty()){
		for (char c : myData){
			// Char input gets converted to ASCII value 
			// in int array
			charCount[c][0] = c;
			charCount[c][1]++; // Increases count by 1 
		}
	}
	
	cout << "Content-type:text/html\r\n\r\n";
	cout << "<html>\n"; cout << "<head>\n";
	cout << "<title>Project 1</title>\n";
	cout << "<style>\nul {\nmargin-top: 0;\npadding-top: 0;\n}\n</style>\n";
	cout << "</head>\n"; cout << "<body>\n";
	cout << "<h2>CPS 3525 project 1</h2>\n";
	cout << "<span style=\"font-size: 18px; font-weight: bold\"><br>Rafael Toledo</span>\n";	

	cout << "<br>Input information:\n";
	
	// Name is displayed here
	// And error message occurs if Name is missing
	if (!name.empty()) {cout << "<br>Name: " << name << endl;}
	else {cout << "<br>Name: <span style=\"color:Red;\"><br>Name Missing!</span>"<< endl;}
	
	// Gender is displayed here
	// And error message occurs if Gender is missing
	if (!gender.empty()) {cout << "<br>Gender: " << gender << endl;}
        else {cout << "<br>Gender: <span style=\"color:Red;\"><br>Gender Missing!</span>"<< endl;}
	
	// Age is displayed here
	// And error message occurs if Age is missing
	// If age is not an integer
	// And if age is not between 1-99
	if (age != 54728 && isValid) {cout << "<br>Age: " << age << endl;}
	else if (age == 54728 && isValid) {cout << "<br>Age: <span style=\"color:Red;\"><br>Age Missing! " << "</span>"<< endl;}
	else if (age == 54728 && !isValid) {cout << "<br>Age: <span style=\"color:Red;\"><br>Age is not an integer!</span>"<< endl;}
	if ((age > 99 || age < 1) and age != 54728) {cout << "<span style=\"color:Red;\"><br>Age is not in range! It should be from 1-99.</span>"<< endl;}
	
	// Birthday is displayed here
	// And error message occurs if Birthday is missing
	// Or if Age does not match expected age from birthday
	if (!birthday.empty()) {cout << "<br>Birthday: " << birthday << endl;}
	else {cout << "<br>Birthday: <span style=\"color:Red;\"><br>Birthday Missing!</span>"<< endl;}

	if ((age != 54728 && isValid) && (!birthday.empty()) && (age != actualAge)){
		cout << "<br><span style=\"color:Red;\">Your age should be " << actualAge << ", NOT " << age << "</span>" <<endl;
	}
	
	// Courses selected displayed here
	// And error message occurs if none are selected
	cout << "<br>Courses Selected:";
	if (CPS1231_flag || CPS2231_flag || CPS2232_flag || CPS3250_flag){
		cout << "<ul>";
		if (CPS1231_flag) { cout << "<li>CPS1231</li>"; }	
		if (CPS2231_flag) { cout << "<li>CPS2231</li>"; }
		if (CPS2232_flag) { cout << "<li>CPS2232</li>"; }
		if (CPS3250_flag) { cout << "<li>CPS3250</li>"; }
		cout << "</ul>";
	}
	else {
                cout << "<br><span style=\"color:Red;\">No Courses Selected!</span>";
        }
	


	// Town displayed here
	// And errer message if not selected
	if (!town.empty()) {cout << "Township: " << town << endl;}
        else {cout << "Township: <span style=\"color:Red;\"><br>Town Missing!</span>"<< endl;}
	
	// Input String displayed here
	// And error message if not inputed
	if (!myData.empty()) {cout << "<br>Input String: " << myData << endl;}
        else {cout << "<br>Input String: <span style=\"color:Red;\"><br>Input String Missing!</span>"<< endl;}

	// Table of String displayed
	// As well as letter(s) with the min, and max count
	// If input string is empty nothing is displayed
	if(!myData.empty()){
		cout << "<TABLE border = 1>\n";
		cout << "<TR><TD align='center'>ASCII #";
		cout << "<TD align='center'>Char";
		cout << "<TD align='center'>Count";
		
		for (int i = 0; i < 128; i++){
			if (charCount[i][1] > 0) { // Needs to be in string to be displayed
				cout << "<TR><TD align='center'>" << charCount[i][0]; // Shows ASCII #
				cout << "<TD align='center'>" << static_cast<char>(charCount[i][0]); // Shows Char from  ASCII
				cout << "<TD align='center'>" << charCount[i][1]; // Shows count
			}
		}
		
		cout << "</TABLE>\n";

		// Print Chars with Min and Max Counts
		printMaxAndMinCount(charCount);

	}	

	cout << "</body>\n"; cout << "</html>\n";
	
	return 0;
}

// Function to Print the Chars with the Min and Max Counts
void printMaxAndMinCount(int array[][2]){
	
	// Initialize min and max count
	int maxCount = array[0][1]; 
	int minCount = 1;
	
	// For loop to find the min and max
	for (int i = 0; i < 128; i++){
		if (array[i][1] > maxCount) { maxCount = array[i][1];}
		if ((array[i][1] < minCount) && array[i][1] != 0) { minCount == array[i][1];}
	}

	// Print Results
	// First Max
        cout << "<br>Character: ";

        for (int i = 0; i < 128; i++) {
		if (array[i][1] == maxCount) {cout << static_cast<char>(array[i][0]) << " ";}
        }	
        
	cout << "has maximum count: " << maxCount;

	// Now Min
        cout << "<br>Character: ";

        for (int i = 0; i < 128; i++) {
		if (array[i][1] == minCount) {cout << static_cast<char>(array[i][0]) << " ";}
        }

	cout << "has minimum count: " << minCount;

}


// Function to take the string and turn it into an int to find the expected age
int calculateAge(const std::string& birthDateStr) {

	// Convert Parts of the String to ints to compare to Current Date
	int birthYear = std::stoi(birthDateStr.substr(0,4));
	int birthMonth = std::stoi(birthDateStr.substr(5,2));
	int birthDay = std::stoi(birthDateStr.substr(8,2));

	int currentYear = 2023;
	int currentMonth = 10;
	int currentDay = 22;

	int calculatedAge = currentYear-birthYear;
	
	// Adjust age on whether birthday has passed or not
	if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)){
		--calculatedAge;
	}
		

	return calculatedAge;
}
