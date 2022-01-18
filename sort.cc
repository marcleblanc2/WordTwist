/*

 The purpose of this program is to sort the dictionary.csv file.

*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const string inputFilename = "dictionary.csv";
const string outputFilename = "dictionary2.csv";
void sort ();

int main () { 
    
    sort(); 
   
    return 0;
}

void sort () { 

    // read in the dictionary
    ifstream inFile;
    inFile.open( inputFilename.c_str() );
    if ( ! inFile.good() ) {
        cerr << " > Error: Failed to open " << inputFilename << endl;
        return;
    } 
    
    vector<string> dictionary;
    string buffer, word;
    
    do { 
        
        inFile >> buffer; 
       
        for ( unsigned int i = 0; i < buffer.size(); i++ ) {
			
			if ( buffer[i] >= 'A' && buffer[i] <= 'Z' ) {
				
				buffer[i] += 32;
				word += buffer[i];
				
			} else if ( buffer[i] >= 'a' && buffer[i] <= 'z' ) {
				
				word += buffer[i];
			
			} 
		}
		
        dictionary.push_back( word );
	word = "";
        
    } while ( ! inFile.eof() );
    
    inFile.close(); 

    /*cout << endl << "Read:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << dictionary[ dictionary.size() -10 + i ] << endl;
    }*/
    
    // sort the dictionary in memory
    sort( dictionary.begin(), dictionary.end() );

    /*cout << endl << "Sorted:" << endl;
     for (int i = 0; i < 10; i++) {
     cout << dictionary[ dictionary.size() -10 + i ] << endl;
     }*/
    
    // rewrite .csv file
    ofstream outfile;
    outfile.open( outputFilename.c_str() );
    
    if ( ! outfile.good() ) {
        cerr << " > Error: Failed to open " << outputFilename << ". " << endl;
        exit(3);
    } 
    
    // iterate through the dictionary vector
    for ( unsigned int i = 0; i < dictionary.size(); i++ ) {

        // add commas for csv arrangement, one column for each word length, and a column between
        // for ( unsigned int j = 3; i < dictionary[i].size(); j++ ) {
        //     outfile << ",,";	
        // } 
        
        outfile << dictionary[i];
        outfile << endl;
    
    } 
    

    outfile.close();
    return;
} 













