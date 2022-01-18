/*

 The purpose of this program is to scan through the dictionary.csv file, and find the highest scoring 7 letter words.

*/

#include <iostream>
//#include <iomanip> 
#include <fstream>
#include <string>
//#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;

const string filename = "dictionary.csv";

void loadDictionary ( set<string>& dictionary, vector<string>& sevens, const string& filename );
void algorithm ( const set<string>& dictionary, const string& inputString, int& resultsBuffer, int& pointBuffer, const unsigned int gameSize = 7 );
void deduction ( vector<string>& deductions, const string& inputString, const unsigned int& gameSize );
void readSevens ( const set<string>& dictionary, const vector<string>& sevens );
	
int main () {
	
	set<string> dictionary;
	vector<string> sevens;
	
	loadDictionary ( dictionary, sevens, filename ); 	
	readSevens ( dictionary, sevens );
    
	return 0;
} 

// vector<string> matches is passed by reference in case the calling fn wants to use the matches.
void algorithm ( const set<string>& dictionary, const string& inputString, int& resultsBuffer, int& pointBuffer, const unsigned int gameSize ) { 
	
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
	
	switch ( gameSize ) {	
			
		case 7: 
			
			if ( ! sev.empty() ) { 
				
				sort(sev.begin(), sev.end());
				
//				cout << endl;
				for ( i = 0; i < sev.size(); i++ ) {
//					cout << right << setw(2) << i + 1 << ": " << sev[i] << endl;
					pointBuffer += 9;

					// to deal with the largest word bonus
					pointBuffer += 25;
				} 
				
//				cout << " > Number of words of size 7: " << i << endl;
				resultsBuffer += i;
			} 
			
		case 6: 
			
			if ( ! six.empty() ) { 	
				
				sort(six.begin(), six.end());
				
//				cout << endl;
				for ( i = 0; i < six.size(); i++ ) {
//					cout << right << setw(2) << i + 1 << ": " <<  six[i] << endl;
					pointBuffer += 6;
					
					// to deal with the largest word bonus
					if ( gameSize < 7 ) {
						pointBuffer += 25;
					} 
				} 
				
//				cout << " > Number of words of size 6: " << i << endl;
				resultsBuffer += i;
			}
			
		case 5: 
			
			if ( ! fiv.empty() ) { 	
				
				sort(fiv.begin(), fiv.end());
				
//				cout << endl;
				for ( i = 0; i < fiv.size(); i++ ) {
//					cout << right << setw(2) << i + 1 << ": " << fiv[i] << endl;
					pointBuffer += 4;
				} 
				
//				cout << " > Number of words of size 5: " << i << endl;
				resultsBuffer += i;
			} 
			
		case 4: 
			
			if ( ! fou.empty() ) { 	
				
				sort(fou.begin(), fou.end());
				
//				cout << endl;
				for ( i = 0; i < fou.size(); i++ ) {
//					cout << right << setw(2) << i + 1 << ": " << fou[i] << endl;
					pointBuffer += 2;
				} 
				
//				cout << " > Number of words of size 4: " << i << endl;
				resultsBuffer += i;
			}
			
		case 3: 
			
			if ( ! thr.empty() ) { 	
				
				sort(thr.begin(), thr.end());
				
//				cout << endl;
				for ( i = 0; i < thr.size(); i++ ) {
//					cout << right << setw(2) << i + 1 << ": " << thr[i] << endl;
					pointBuffer += 1;
				} 
				
//				cout << " > Number of words of size 3: " << i << endl;
				resultsBuffer += i;
			} 
	}
	
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

void loadDictionary ( set<string>& dictionary, vector<string>& sevens, const string& filename ) {
	
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
				
			} 
			
			/* else if ( buffer[i] == ',' ) {
				
				dictionary.insert( word );
				word = "";
				
			} */
		}
		
		dictionary.insert( word );

		if ( word.length() == 7 ) {
			sevens.push_back( word );
		} 
		
		word = "";
		
	} while ( ! inFile.eof() );
	
	inFile.close();
	
}  // end void loadDictionary

void readSevens ( const set<string>& dictionary, const vector<string>& sevens ) {
	
	int indexOfLargestSeven = 0;
	int productOfLargestSeven = 0;
	int resultsBuffer = 0;
	vector<int> numberOfDescendants; 

	int indexOFLargestPoints = 0;
	int largestPoints = 0;
	int pointBuffer = 0;
	vector<int> pointValue;
	
	for ( unsigned int i = 0; i < sevens.size(); i++ ) {
		
		resultsBuffer = 0;
		pointBuffer = 0;
		
		// deal with each of the seven letter words
		algorithm( dictionary, sevens[i], resultsBuffer, pointBuffer );
		numberOfDescendants.push_back( resultsBuffer );
		pointValue.push_back( pointBuffer );
		
		// to record the word with the largest number of descendants
		if ( resultsBuffer > productOfLargestSeven ) { 
			
			indexOfLargestSeven = i;
			productOfLargestSeven = resultsBuffer;
			
		} // end if
		
		// to record the word with the largest point value
		if ( pointBuffer > largestPoints ) {
		
			largestPoints = pointBuffer;
			indexOFLargestPoints = i;
			
		} // end if 
		
		
	} // end for 
	
/*	for ( unsigned int i = 0; i < sevens.size(); i++ ) {
		if ( numberOfDescendants[i] > productOfLargestSeven - 10 ) { 
			cout << " > " << sevens[i] << " has " << numberOfDescendants[i] << " words generated." << endl;
		} 
//		cout << sevens[i] << " has " << numberOfDescendants[i] << " decendants." << endl;
	} */
	
	cout << " > Of " << sevens.size() << " size seven words in the dictionary: " << endl;
	
	cout << " >> " << sevens[indexOfLargestSeven] << " wins with " << productOfLargestSeven << " words generated. " << endl
	<< " >> " << sevens[indexOFLargestPoints] << " wins with " << largestPoints << " points scored. " << endl;
	
} // end void readSevens