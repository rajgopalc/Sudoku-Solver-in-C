#include<stdio.h>
#include<stdlib.h>

int a[9][9] = {
                  8,0,0,0,0,0,0,0,0,
                  0,0,3,6,0,0,0,0,0,
                  0,7,0,0,9,0,2,0,0,
                  0,5,0,0,0,7,0,0,0,
                  0,0,0,0,4,5,7,0,0,
                  0,0,0,1,0,0,0,3,0,
                  0,0,1,0,0,0,0,6,8,
                  0,0,8,5,0,0,0,1,0,
                  0,9,0,0,0,0,4,0,0
               };
int b[9][9];
int backtrack = 0;
int curr_row;
int curr_col;
int prev_row;
int prev_col;
int prev_val;
int rInsert = 100;

int check_violation(row,col,val){
    int column;
    int row_pos;

    /*Checking row-wise*/
        for(column=0;column<9;column++){
            if(a[row][column] == val){
               return(1);
            }
        }
    /*Checking column-wise*/
        for(row_pos=0;row_pos<9;row_pos++){
            if(a[row_pos][col] == val){
                return(1);
            }
        }

    /* Checking subgrid*/
    row = (row / 3)*3;
    col =  (col / 3)*3;
    for(row_pos=0;row_pos<3;row_pos++){
        for(column=0;column<3;column++){
            if(a[row+row_pos][col+column] == val){
                return(1);
            }
        }
    }

return(0);
}

//int checkEmptySlot(int row, int col){
//     int r1,c1;
//     for(r1=row;r1<9;r1++){
//        for(c1=col;c1<9;c1++){
//            if(a[r1][c1] == 0){
//                return 1;
//            }
//            else{
//                return 0;
//            }
//        }
//    }
//}

int getRow(int row,int col){
    int r,c;

    if(col==0){
                col=9;
                row=row-1;
            }

    for(r=row;r>=0;r--){
        if(c+1==0){
            col=9;
           }
        for(c=col-1;c>=0;c--){
                if(b[r][c]==0){
                    return r;
                }
        }
    }
}

int getCol(int row,int col){
    int r,c;

    if(col==0){
                col=9;
                row=row-1;
        }

    for(r=row;r>=0;r--){
        if(c+1==0){
            col=9;
           }
        for(c=col-1;c>=0;c--){
                if(b[r][c]==0){
                    return c;
                }
        }
    }
}

int insertValue(int row, int col,int prev_val){
    int k=1;
    
    curr_row = row;
    curr_col = col;

	if(prev_val != 0){
      //printf("Prev val = %d, Row=%d, col=%d\n",prev_val,row,col);
	  backtrack=0;
      a[row][col]=0;
    }

    if(a[row][col] == 0){
        for(k = prev_val+1;k<=9;k++){
            //printf("Val of k - %d, row - %d, col - %d\n",k,row,col);
            if(check_violation(row,col,k) == 0){
                a[row][col] = k;
              	//printf("Assigned val k = %d at row = %d, col = %d\n",k,row,col);
				return(1);
            }
        }
        if(a[row][col]==0 && k-1 == 9){
        	return(0); //Backtracking
        }
    }
    
    return(99); //case where a[row][col] != 0
}



int main(){

   int i = 0;
   int j = 0;
  
  
	printf("\nSo, the sudoku you gave me is as follows!\n\n");

    for(i=0;i<9;i++){
        printf("\n");
        for(j=0;j<9;j++){
           printf("%d ", a[i][j]);
           b[i][j]=a[i][j];
        }
   }

    printf("\n\n");

	printf("Hmm...Seems fun! Thinking & Solving..Will reply in a Jiffy!");

    printf("\n\n");
    
    curr_col = 0;
    curr_row = 0;
    
  //  printf("%d\n", getRow(6,1));
  //  printf("%d\n", getCol(6,1));
    
    rInsert = insertValue(0,0,0);
	while(rInsert != 100){
		while(rInsert==1){
			if(curr_col==8){
                    curr_row=curr_row+1;
                    curr_col=-1;
                }
                if(curr_row>8){
                    rInsert = 100;
                }
                else{
                    //printf("Pt. of recursion - row = %d, col = %d\n",curr_row,curr_col+1);
					rInsert = insertValue(curr_row,curr_col+1,0);
                }
		}
	
		if(rInsert == 0){
				backtrack = rInsert;
				if((curr_row+curr_col)!=0){
                	//printf("I am being called at location %d,%d!\n",curr_row,curr_col);
                	prev_row=getRow(curr_row,curr_col);
                	prev_col=getCol(curr_row,curr_col);
                	prev_val=a[prev_row][prev_col];
                	//printf("Backtracking = %d now towards %d,%d!\n",backtrack,prev_row,prev_col);
                	backtrack = 0;
                	rInsert = insertValue(prev_row,prev_col,prev_val);
        		}
		        else if(curr_row==0 && curr_col==0){
		               //printf("Called at origin\n");
		                backtrack=0;
		                rInsert = insertValue(0,0,0);
		        }
		        else{
		                printf("No solution...Exiting\n");
		                exit(0);
		            }
     	} 
     	if(rInsert == 99){
 		 		if(curr_col==8){
	                curr_row=curr_row+1;
                    curr_col=-1;
                }
                if(curr_row>8){
                    return(1);
                }
                else{
                    //printf("Pt. of recursion2 - row = %d, col = %d\n",curr_row,curr_col+1);
                    rInsert = insertValue(curr_row,curr_col+1,0);
                }
     	}
	}
	
	for(i=0;i<9;i++){
        printf("\n");
        for(j=0;j<9;j++){
           printf("%d ", a[i][j]);
        }
     }
    printf("\n\nIts done\n");
   return(1);
}
