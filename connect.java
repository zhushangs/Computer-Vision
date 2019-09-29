package CV;

import java.io.PrintWriter;
import java.util.Scanner;

public class connect{
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int newMin;
	int newMax;
	int newLabel;
	int numNb;
	
	int[] EQAry;
	int[] NonZeroNeighbor;
	
	int[][] zeroFramedAry;
	
	connect(Scanner inFile){
		
		numRows = inFile.nextInt();
		numCols = inFile.nextInt();
		minVal = inFile.nextInt();
		maxVal = inFile.nextInt();
		
		zeroFramedAry = new int [numRows + 2][numCols + 2];
		NonZeroNeighbor = new int[numNb];
		
		numNb = 5;
		
		int size = (numRows * numCols) / 4;
		for(int i = 0; i < size; i++) {
			EQAry[i] = i;
		}	
	}
	
	void zeroFramed() {
		for(int i = 0; i < numRows + 2; i++){
			zeroFramedAry[i][0] = zeroFramedAry[i][1];
			zeroFramedAry[i][numCols + 1] = zeroFramedAry[i][numCols];
            for(int j = 0; j < numRows + 2; j++){
            	zeroFramedAry[0][j] = zeroFramedAry[1][j];
                zeroFramedAry[numRows + 1][j] = zeroFramedAry[numRows][j];
            }
        }
	}
	
	void loadImage(Scanner inFile) {
		
		int temp;
		for(int i = 1; i < numRows; i++) {
			for(int j = 1; j < numCols; j++) {
				temp = inFile.nextInt();
				zeroFramedAry[i][j] = temp;
			}
		}
	
	}
	
	int[] loadNonZero(int i, int j) {
		
		NonZeroNeighbor[0] = zeroFramedAry[i - 1][j - 1];
		NonZeroNeighbor[1] = zeroFramedAry[i - 1][j];
		NonZeroNeighbor[2] = zeroFramedAry[i - 1][j + 1];
		NonZeroNeighbor[3] = zeroFramedAry[i][j - 1];
		NonZeroNeighbor[4] = zeroFramedAry[i][j + 1];
		NonZeroNeighbor[5] = zeroFramedAry[i + 1][j - 1];
		NonZeroNeighbor[6] = zeroFramedAry[i + 1][j];
		NonZeroNeighbor[7] = zeroFramedAry[i + 1][j + 1];		
		
		return NonZeroNeighbor;
	}
	
	void connect8CC_Pass1(PrintWriter outFile1) {
	
		newLabel = 1;
		
		for(int i = 1; i < numRows + 1; i++){
            for(int j = 1; j < numCols + 1; j++){
            	loadNonZero(i,j);
                
                if(zeroFramedAry[i][j] > 0){
                    if(NonZeroNeighbor[0] == 0 && NonZeroNeighbor [1] == 0 && NonZeroNeighbor [2] == 0 && NonZeroNeighbor [3] == 0){ 
                        
                    	zeroFramedAry[i][j] = newLabel;
                    	newLabel++;
                    	
                    }else if( NonZeroNeighbor[0] != 0 && NonZeroNeighbor[1] != 0 && NonZeroNeighbor[2] != 0 && NonZeroNeighbor[3] != 0){
                    	if(NonZeroNeighbor[0] == NonZeroNeighbor[1] && NonZeroNeighbor[1] == NonZeroNeighbor[2] && NonZeroNeighbor[2] == NonZeroNeighbor[3]) {
                    		
                    		zeroFramedAry[i][j] = NonZeroNeighbor[3];
                   		
                    	}else {
                    		int min = NonZeroNeighbor[0];
                    		for(int k = 0; k < NonZeroNeighbor.length; k++) {
                    			if( NonZeroNeighbor[i] < min) {
                    				min = NonZeroNeighbor[i];
                    			}
                    		}
                    		zeroFramedAry[i][j] = min;
                    		updateEQ(NonZeroNeighbor[i], min);
                    	}
                    }
                }
            }
        }
		
	}
	
	void connect8CC_Pass2() {
		
		newLabel = 1;
		
		for(int i = numRows; i > 0; i--){
            for(int j = numCols; j > 0; j--){
            	loadNonZero(i,j);
            	
            	if(zeroFramedAry[i][j] > 0){
                    if(NonZeroNeighbor[7] == 0 && NonZeroNeighbor[6] == 0 && NonZeroNeighbor[5] == 0 && NonZeroNeighbor[4] == 0){  //case 1
                    	
                    }else if( NonZeroNeighbor[0] != 0 && NonZeroNeighbor[1] != 0 && NonZeroNeighbor[2] != 0 && NonZeroNeighbor[3] != 0){
                    	if(NonZeroNeighbor[7] == NonZeroNeighbor[6] && NonZeroNeighbor[6] == NonZeroNeighbor[5] && NonZeroNeighbor[5] == NonZeroNeighbor[4]) {
                    		
                    	}else {
                    		
                    		int min = NonZeroNeighbor[7];
                    		for(int k = NonZeroNeighbor.length; k > 0; k++) {
                    			if( NonZeroNeighbor[i] < min) {
                    				min = NonZeroNeighbor[i];
                    			}
                    		}
                    		zeroFramedAry[i][j] = min;
                    		updateEQ(NonZeroNeighbor[i], min);
                    	}
                    }
            	}
            }
		}
	}
	
	void connect8CC_Pass3() {
	}
	
	void updateEQ(int i, int j) {
		EQAry[i] = j;
	}
	
	void manageEQAry() {

		int c = 1;
		for(int i = 1; i < newLabel; i++) {
			if(i == EQAry[i]) {
				EQAry[i] = c;
				c++;
			}else {
				EQAry[i] = EQAry[EQAry[i]];
			}
		}
		
	}
	
	void printCCproperty(PrintWriter outFile) {
		
		outFile.write(numRows + "" + numCols + "" + newMin + " " + newMax + '\n');
		
		
	}
	
	void prettyPrint(PrintWriter outFile) {
		
		for(int i = 0; i < numRows; i++){
			for(int j = 0; j < numCols; j++){
				if(zeroFramedAry[i][j] == 0) {
					outFile.write("  ");
				}else {
					outFile.write(zeroFramedAry[i][j] + " ");
				}
			}
			outFile.write("\n");
		}
	}
	
	void printEQAry(PrintWriter outFile) {
		
		for(int  i = 1; i < newLabel; i++) {
			outFile.write(EQAry[i] + " ");
		}
		outFile.write('\n');
		
	}
	
}
