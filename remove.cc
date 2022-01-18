/*

 The purpose of this program is to remove a word from the dictionary.csv file.

*/
#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;

void loadDictionary ( set<string>& dictionary, const string& filename ); 
void writeDictionary ( set<string>& dictionary, const string& filename );
void removeFromDictionary ( set<string>& dictionary );

int main() { 

	const string filename = "dictionary.csv";
	set<string> dictionary;

	loadDictionary ( dictionary, filename );
	
	removeFromDictionary ( dictionary );
	
	writeDictionary ( dictionary, filename );

	return 0;
} 

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
				
			} else if ( buffer[i] == ',' ) {
				
				dictionary.insert( word );
				word = "";
				
			} 
		}
		
		dictionary.insert( word );
		word = "";
		
	} while ( ! inFile.eof() );
	
	inFile.close();
	
} 

void writeDictionary ( set<string>& dictionary, const string& filename ) {

	ofstream outfile;
	outfile.open( filename.c_str() );
	if ( ! outfile.good() ) {
		cerr << " > Error: Failed to open " << filename << ". " << endl;
		exit(3);
	} 
	
	for ( set<string>::iterator iter = dictionary.begin(); iter != dictionary.end(); iter++ ) {
		
		outfile << endl;
		for ( unsigned int i = 3; i < iter->size(); i++ ) {
			outfile << ",,";	
		} 
		outfile << *iter;

	} 
	
	outfile.close();
}

void removeFromDictionary ( set<string>& dictionary ) {

	string target = "";
	
	while ( true ) {
	
		cout << "Enter word to remove: ";
		cin >> target;
	
		if ( target == "0" ) { 
			
			return;
		} 
		
		set<string>::iterator iter = dictionary.find( target );
		
		if ( iter == dictionary.end() ) {
			
			cout << " > " << target	<< " not found in dictionary. " << endl;
			continue;
		} 
			
		cout << "Are you sure you want to remove '" << target << "'?: ";
		char answer;
		cin >> answer;
	
		if ( answer == 'y' || answer == 'Y' ) {
			
			dictionary.erase( iter );
					
		} 
	
	
	} // end while ( target != "0" ) 

} // end removeFromDictionary

