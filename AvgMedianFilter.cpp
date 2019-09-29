#include <iostream>
#include <fstream>
using namespace std;

ifstream inFile;
ofstream outFile1,outFile2;

class imageProcessing{
	
	public:
		
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int newMin;
	int newMax;
	
	int ** mirrorFramedAry;
	int ** avgAry;
	int ** medianAry;
	
	int * neighborAry;
	
	imageProcessing(){
		
		inFile >> numRows >> numCols >> minVal >> maxVal;
		
		mirrorFramedAry = new int* [numRows + 2];
		avgAry = new int* [numRows + 2];
		medianAry = new int* [numRows + 2];
		neighborAry = new int[9];
		
		for(int i = 0; i < numRows + 2; i++){
            mirrorFramedAry[i] = new int[numCols + 2];
            avgAry[i] = new int[numCols + 2];
            medianAry[i] = new int[numCols + 2];
        }    		
	}
	
	void mirrorFraming(){
		
		for(int i = 0; i < numRows + 2; i++){
            mirrorFramedAry[i][0] = mirrorFramedAry[i][1];
            mirrorFramedAry[i][numCols + 1] = mirrorFramedAry[i][numCols];
            for(int j = 0; j < numRows + 2; j++){
                mirrorFramedAry[0][j] = mirrorFramedAry[1][j];
            	mirrorFramedAry[numRows + 1][j] = mirrorFramedAry[numRows][j];
            }
        }
			
	}
	
	void loadImage(){
		
		int temp;
        for(int i = 1; i <= numRows; i++){
            for(int j = 1; j <= numCols; j++){
                inFile >> temp;
                mirrorFramedAry[i][j] = temp;
            }
        }
        
	}
	
	int * loadNeighbors(int i, int j){
		
		int c = 0;		
		for(int x = i - (3/2); x <= i + (3/2); x++){
			for(int y = j - (3/2); y <= j + (3/2); y++){
				neighborAry[c] = mirrorFramedAry[x][y];
				c++;
			}
		} 
		
		return neighborAry;
	}
		
		
	int averageAry(int i, int j){
		
		int sum = 0;
		for(int x = i - (3/2); x <= i + (3/2); x++){
			for(int y = j - (3/2); y <= j + (3/2); y++){
				sum += mirrorFramedAry[x][y];
			}
		}	
		return sum / 9;
		
	}	
		
	void computeAVG(){
		
		for(int i = 1; i <= numRows; i++){
			for(int j = 1; j <= numCols; j++){				
				loadNeighbors(i,j);	
				avgAry[i][j] = averageAry(i, j);
			}
		}
		
		//tracking newMin and new Max 
		newMin = avgAry[1][1];
		newMax = avgAry[1][1];
		
		for(int i = 1; i <= numRows; i++){
			for(int j = 1; j <= numCols; j++){
				if(avgAry[i][j] < newMin){
					newMin = avgAry[i][j];
				} 
				if(avgAry[i][j] > newMax){
					newMax = avgAry[i][j];
				} 
			}
		}
		
	}
	
	int sort(int* neighborAry) {

		int temp, j;		
		for(int i = 1; i < 9; i++) {
			temp = neighborAry[i];
			j = i - 1;	
			for(j = i - 1; j >= 0 && neighborAry[i] > temp; j--){
				neighborAry[j + 1] = neighborAry[j];
			}		
			neighborAry[j + 1] = temp;
		}
		return neighborAry[4];
	}
	
	void computeMedian(){
		
		for(int i = 1; i <= numRows; i++){
            for(int j = 1; j <= numCols; j++){
                loadNeighbors(i,j);
                medianAry[i][j] = sort(neighborAry);
            }
        }
        
        newMin = medianAry[1][1];
        newMax = medianAry[1][1];
        
        for(int i = 1; i <= numRows; i++){
            for(int j = 1; j <= numCols; j++){
                if(medianAry[i][j] < newMin){
                	newMin = medianAry[i][j];
				}
                if(medianAry[i][j] > newMax){
                	newMax = medianAry[i][j];
				} 
            }
        }
	}
	
		
	//output average			
	void printAry2File1(){
		
		outFile1 << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
		
		for(int i = 1; i <= numRows; i++){
			for(int j = 1; j <= numCols; j++){
				outFile1 << avgAry[i][j] << " ";
			}
			outFile1 << endl;	
		}  
	} 	
	
	//output median			
	void printAry2File2(){
		
		outFile2 << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
		
		for(int i = 1; i <= numRows; i++){
			for(int j = 1; j <= numCols; j++){
				outFile2 << medianAry[i][j] << " ";
			}
			outFile2 << endl;	
		}				  
	} 
}; 

int main(int argc, char** argv){
	
	inFile.open(argv[1]);
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);		

	
	if( !inFile.eof()){
		
		imageProcessing* processing = new imageProcessing();
		
		processing->loadImage();
		processing->mirrorFraming();
		processing->computeAVG();
		processing->printAry2File1();
		processing->computeMedian();
		processing->printAry2File2();
		
	}else{
		cout << "File doesn't exist.";
	}
	
	    
    inFile.close();
    outFile1.close();
    outFile2.close();
	
	return 0;
}

