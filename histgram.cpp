#include <iostream>
#include <fstream>
using namespace std;



//int main(int argc, char** argv){
int main(int argc, char* argv[]){

	ifstream inFile;
	inFile.open(argv[1]);
	
	ofstream outFile;
	outFile.open(argv[2]);
	

	int numRows;
	int numCols;
	int minVal;
	int maxVal= 1000;
	int* hist = new int[maxVal + 1];

	
	if(!inFile.eof()){

	
		inFile >> numRows >> numCols >> minVal >> maxVal;

		 
		for(int i = 0; i < maxVal+1; i++){
            hist[i] = 0;
    	}	

   	
    	int temp;
		for(int i = 0; i < numRows; i++){
        	for(int j = 0; j < numCols; j++){
        		inFile >> temp;
          		hist[temp]++;
       	 	}
    	}

	
		outFile << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;		

		for(int i = 0; i < maxVal+1; i++){
        	outFile << i << " (" << hist[i] << "): ";
        	for(int j = 0; j < hist[i] && j<60; j++){
        		outFile << "+";
			}
			outFile << endl;
    	}
	
	}else{
		cout<<"File doesn't exist.";  
	}
		
	inFile.close();
	outFile.close();
	
	return 0;
}
