/*

 The purpose of this program is to solve the Word Twist game.
 Input: 6 or 7 character string, and a dictionary file. 
 Output: list of all valid words in the dictionary.

*/

#include <iostream>
#include <iomanip> 
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;

const string filename = "dictionary.csv";

void runProgram ( set<string>& dictionary, const int& round, string& inputBuffer );
void algorithm ( const set<string>& dictionary, const string inputString, const unsigned int gameSize );
void deduction ( vector<string>& deductions, const string& inputString, const unsigned int& gameSize );
void loadDictionary ( set<string>& dictionary, const string& filename ); 
void addToDictionary ( set<string>& dictionary, const string& filename, const string& givenLetters );
bool checkContent( string base, const string &check );

int main () {
	
	// load dictionary file into memory
	set<string> dictionary;
	loadDictionary ( dictionary, filename ); 	
	
	int roundNumber = 1;
	string inputBuffer;

	while ( inputBuffer != "0" ) { 
		
		runProgram( dictionary, roundNumber, inputBuffer);
		roundNumber++;
	} 
	
	return 0;	
}

void runProgram ( set<string>& dictionary, const int& round, string& inputBuffer ) {
	

	// read user input
	cout << endl << "Round number " << round << endl
                << "Enter given letters: ";

	cin >> inputBuffer;
	
	if ( inputBuffer == "0" ) { 
		return;
	} 
	
	unsigned int gameSize = inputBuffer.size();
	int index = 0; 

	string inputString;
    
	// load user input into the initial string
	while ( inputString.size() < gameSize ) {
		
		// to weed out non-alphabetic characters and
		// to lowercase all capitals
		if ( inputBuffer[index] >= 'a' && inputBuffer[index] <= 'z') { 		
			
			inputString += inputBuffer[index];
			
		} else if (	inputBuffer[index] >= 'A' && inputBuffer[index] <= 'Z')  {
			
			inputBuffer[index] += 32;
			inputString += inputBuffer[index];
			
		} else {
			
			// so that the char array size matches the number of valid characters			
			gameSize--;
		} 
		
		index++;
	} 
	
	// run algorithm
	algorithm( dictionary, inputString, gameSize ); 
	
	// add any new words to dictionary file
	addToDictionary( dictionary, filename, inputString);
	
} 

// vector<string> matches is passed by reference in case the calling fn wants to use the matches.
void algorithm ( const set<string>& dictionary, const string inputString, const unsigned int gameSize ) {
	
	vector<string> d;
	set<string> seen;
	queue<string> q;

	vector<string> sev;
	vector<string> six;
	vector<string> fiv;
	vector<string> fou; 
	vector<string> thr;
	
	q.push( inputString );

	char * charptr = &q.front()[0];

	// because next_permutation() only works on sorted data
	sort( charptr, charptr + q.front().size() );

	while ( ! q.empty() ) { 

		charptr = &q.front()[0];
		
		do { 
	
			// if the random permutation is actually in the dictionary
			if ( seen.find( q.front() ) == seen.end() &&
				dictionary.find( q.front() ) != dictionary.end() ) {

				switch ( q.front().size() ) {
						
					case 3:
						thr.push_back( q.front() );
						break;
						
					case 4:
						fou.push_back( q.front() );
						break;
						
					case 5:
						fiv.push_back( q.front() );
						break;

					case 6:
						six.push_back( q.front() );
						break;
					
					case 7:
						sev.push_back( q.front() );
						break;

				} // end switch
			} // end if
			
			// remember it to skip next time we see it
			seen.insert( q.front() );
			
		} while ( next_permutation(charptr, charptr + q.front().size()) );

		// from a string size n, create all n possible
		// strings of size n-1, then add them to the queue
		// for later processing
		deduction(d, q.front(), q.front().size() );

		// remove the just-processed string
		q.pop();
	
		for ( unsigned int i = 0; i < d.size(); i ++ ) {
			
			q.push( d[i] ); 

		} // end for
	
		// clear the temp vector
		d.clear();

	} // end while ( ! q.empty() )

	unsigned int i = 0;
	int total = 0; 
	int totalPoints = 0;
	
        // output list of words and scores
	switch ( gameSize ) {	
		
		case 7: 
			
			if ( ! sev.empty() ) { 
			
				sort(sev.begin(), sev.end());
	
				cout << endl;
				for ( i = 0; i < sev.size(); i++ ) {
					cout << right << setw(2) << i + 1 << ": " << sev[i] << endl;

					totalPoints += 9;
					// to deal with the largest word bonus
					if ( gameSize == 7 ) {
						totalPoints += 25;
					} 					
				} 
	
				cout << " > Number of words of size 7: " << i << endl;
				total += i;
			} 
			
		case 6: 

			if ( ! six.empty() ) { 	
				
				sort(six.begin(), six.end());
				
				cout << endl;
				for ( i = 0; i < six.size(); i++ ) {
					cout << right << setw(2) << i + 1 << ": " <<  six[i] << endl;
					totalPoints += 6;
					
					// to deal with the largest word bonus
					if ( gameSize == 6 ) {
						totalPoints += 25;
					} 
				} 
				
				cout << " > Number of words of size 6: " << i << endl;
				total += i;
			}
			
		case 5: 
		
			if ( ! fiv.empty() ) { 	
			
				sort(fiv.begin(), fiv.end());
				
				cout << endl;
				for ( i = 0; i < fiv.size(); i++ ) {
					cout << right << setw(2) << i + 1 << ": " << fiv[i] << endl;
					totalPoints += 4;
				} 
				
				cout << " > Number of words of size 5: " << i << endl;
				total += i;
			} 
			
		case 4: 

			if ( ! fou.empty() ) { 	

				sort(fou.begin(), fou.end());
				
				cout << endl;
				for ( i = 0; i < fou.size(); i++ ) {
					cout << right << setw(2) << i + 1 << ": " << fou[i] << endl;
					totalPoints += 2;
				} 
				
				cout << " > Number of words of size 4: " << i << endl;
				total += i;
			}
			
		case 3: 

			if ( ! thr.empty() ) { 	

				sort(thr.begin(), thr.end());
				
				cout << endl;
				for ( i = 0; i < thr.size(); i++ ) {
					cout << right << setw(2) << i + 1 << ": " << thr[i] << endl;
					totalPoints += 1;
				} 
				
				cout << " > Number of words of size 3: " << i << endl;
				total += i;
			} 
	}
		
	cout << endl << " >> Total matches found: " << total << endl
	<< " >> With total points: " << totalPoints << endl;
	
} // end algorithm 

void deduction ( vector<string>& deductions, const string& inputString, const unsigned int& gameSize ) {
	
	// so you get a string of size  7, and you need to make a string of size 6. 
	// from i = 1 to 7, take i out of string. 
 
	string b;

	for ( unsigned int i = 0; i < gameSize; i++ ) {
	
		b = "";
		
		for ( unsigned int j = 0; j < gameSize; j++ ) {
		
			if ( j != i ) {
			
				b += inputString[j];
				
			} // end if
		} // end current strings
		
		deductions.push_back( b );

	} // end set of string
} // end void deduction

void loadDictionary ( set<string>& dictionary, const string& filename ) {

	ifstream inFile;
	inFile.open( filename.c_str() );
	if ( ! inFile.good() ) {
		cerr << " > Error: Failed to open " << filename << endl;
		return;
	} 
	
	string buffer; 
	string word;
	
	do { 
		
		inFile >> buffer; 
		
		for ( unsigned int i = 0; i < buffer.size(); i++ ) {
			
			if ( buffer[i] >= 'A' && buffer[i] <= 'Z' ) {
				
				buffer[i] += 32;
				word += buffer[i];
				
			} else if ( buffer[i] >= 'a' && buffer[i] <= 'z' ) {
				
				word += buffer[i];
				
/*			} else if ( buffer[i] == ',' ) {
				
				dictionary.insert( word );
				word = "";
*/				
			} 
		}
		
		dictionary.insert( word );
		word = "";
		
	} while ( ! inFile.eof() );

	inFile.close();

} 

void addToDictionary( set<string>& dictionary, const string& filename, const string& givenLetters ) {
	
	char response;
	cout << endl << "Would you like to add more words to the dictionary (y / n)? ";
	cin >> response;
	
	if ( response != 'y' && response != 'Y' ) { 
		return;
	} 	

	// open dictionary file again onto to append extra data at the end, not to rewrite the dictionary 
	ios_base::openmode app = ios_base::app;

	ofstream outfile;
	outfile.open( filename.c_str(), app );
	if ( ! outfile.good() ) {
		cerr << " > Error: Failed to open " << filename << ". " << endl;
		exit(3);
	} 
	
	string inputBuffer;
	string inputString;
	
	int count = 0;
	
	cout << endl << "Enter new words: " << endl;
	cout << right << setw(2) << ++count << ": ";
	cin >> inputBuffer;

	while ( inputBuffer != "0" ) { 

		unsigned int wordSize = inputBuffer.size();
		int index = 0; 
		
		// load user input into the initial string
		while ( inputString.size() < wordSize ) {
			// to weed out non-alphabetic characters and
			// to lowercase all capitals
			if ( inputBuffer[index] >= 'a' && inputBuffer[index] <= 'z') { 		
				inputString += inputBuffer[index];
			} else if (	inputBuffer[index] >= 'A' && inputBuffer[index] <= 'Z')  {
				inputBuffer[index] += 32;
				inputString += inputBuffer[index];
			} else {
				// so that the char array size matches the number of valid characters			
				wordSize--;
			} 
			index++;
		} 
		
		if ( inputString.size() >= 3 && checkContent( givenLetters, inputString) && dictionary.find( inputString ) == dictionary.end() ) {
			
			// output to dictionary.csv and add to set<string> dictionary 
			dictionary.insert( inputString );
			
            // add commas for csv arrangement, one column for each word length, and a column between
			// for ( unsigned int i = 3; i < inputString.size(); i++ ) {
			// 	outfile << ",,";	
			// } 
			
			outfile << inputString;
			outfile << endl;
			
		} else {
			cout << "Invalid entry." << endl;
			count--;
		} 
		
		// reset for next iteration
		cout << right << setw(2) << ++count << ": ";
		inputBuffer = "";
		inputString = "";
		cin >> inputBuffer;
		
	} 
	
	cout << "New words added: " << --count << endl;
	
	outfile.close();
}

bool checkContent( string base, const string &check ) {
		
	size_t found;
	
	// for each character in the check string, check it against the base array
	for ( unsigned int i = 0; i < check.length(); i++ ) {
		
		found = base.find( check[i] );
		
		if ( found == string::npos ) {
			
			// no match in base for check[i]
			return false;
			
		} else {
			
			// match, so discard character in base so that it's not counted twice
			base.erase(found, 1);
			
		} 
	}
	
	// if there hasn't been a reason to return false yet, then return true
	return true;
}
