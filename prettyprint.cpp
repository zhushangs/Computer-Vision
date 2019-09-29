#include <iostream>
#include <fstream>
using namespace std;



int main(int argc, char** argv){

	ifstream inFile;
	inFile.open(argv[1]);
	
	ofstream outFile;
	outFile.open(argv[2]);
	

	
	if(!inFile.eof()){
		
		int numRows;
		int numCols;
		int minVal;
		int maxVal;
		int pixel_vale;
	
		inFile >> numRows >> numCols >> minVal >> maxVal;
		outFile << numRows << " " << numCols << " " << minVal << " " << maxVal;
	
		for(int i = 0; i < numRows; i++){
			for(int j = 0; j < numCols; j++){
					inFile >> pixel_vale;
					if(pixel_vale > 0){
						outFile << 1 << " ";
					}else{
						outFile << "  ";
					}
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
