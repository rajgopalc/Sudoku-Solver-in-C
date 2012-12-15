#include<stdio.h>
#include<stdlib.h>

int a[9][9] = {
                  6,0,0,5,0,8,0,0,9,
                  0,3,0,2,0,7,0,5,0,
                  0,0,8,0,3,0,2,0,0,
                  0,6,5,0,0,0,8,1,0,
                  8,0,0,0,0,0,0,0,3,
                  0,2,4,0,0,0,5,9,0,
                  0,0,7,0,2,0,1,0,0,
                  0,1,0,6,0,4,0,7,0,
                  2,0,0,7,0,1,0,0,4
               };
int b[9][9];
int backtrack = 0;
int prev_row;
int prev_col;


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

int checkEmptySlot(int row, int col){
     int r1,c1;
     for(r1=row;r1<9;r1++){
        for(c1=col;c1<9;c1++){
            if(a[r1][c1] == 0){
                return 1;
            }
            else{
                return 0;
            }
        }
    }
}

int getRow(int row,int col){
    int r,c;

    if(col==0){
                col=9;
                row=row-1;
            }

    for(r=row;r>=0;r--){
        if(c+1==0){
            col==9;
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
            col==9;
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
    int rval;

    if(prev_val != 0){
        printf("Prev val = %d, Row=%d, col=%d\n",prev_val,row,col);
        backtrack=0;
        a[row][col]=0;
    }

    if(a[row][col] == 0){
        for(k = prev_val+1;k<=9;k++){
            //printf("Val of k - %d, row - %d, col - %d\n",k,row,col);
            if(check_violation(row,col,k) == 0){
                a[row][col] = k;
              	printf("Assigned val k = %d at row = %d, col = %d\n",k,row,col);
                if(col==8){
                    row=row+1;
                    col=-1;
                }
                if(row>8){
                    break;
                }
                else{
                    printf("Pt. of recursion - row = %d, col = %d\n",row,col+1);
                    insertValue(row,col+1,0);
                }
            }
        }
    }
    if(a[row][col] == 0 && k-1==9){
        if(checkEmptySlot(row,col) == 1 && (row+col)!=0){
                printf("I am being called at location %d,%d!\n",row,col);
                prev_row=getRow(row,col);
                prev_col=getCol(row,col);
                prev_val=a[prev_row][prev_col];
                backtrack=1;
                printf("Backtracking = %d now towards %d,%d!\n",backtrack,prev_row,prev_col);
        }
        else if(row==0 && col==0){
                printf("Called at origin\n");
                backtrack=0;
                insertValue(0,0,0);
        }
        else{
                printf("R = %d, C = %d",row,col);
                printf("No solution...Exiting\n");
                return(0);
            }
     }
    // printf("Backtrack = %d\n",backtrack);
     if(a[row][col] != 0 && backtrack==0){
        if(col==8){
                    row=row+1;
                    col=-1;
                }
                if(row>8){
                    return(1);
                }
                else{
                    printf("Pt. of recursion2 - row = %d, col = %d\n",row,col+1);
                    insertValue(row,col+1,0);
                }
     }
    if(backtrack){
        printf("PR=%d,PC=%d,PV=%d\n",prev_row,prev_col,prev_val);
        insertValue(prev_row,prev_col,prev_val);
        backtrack=0;
    }
}


int main(){

   int i = 0;
   int j = 0;
   int rval;


    for(i=0;i<9;i++){
        printf("\n");
        for(j=0;j<9;j++){
           printf("%d ", a[i][j]);
           b[i][j]=a[i][j];
        }
   }

    printf("\n\n");

        for(i=0;i<9;i++){
        printf("\n");
        for(j=0;j<9;j++){
           printf("%d,%d ",i,j);
        }
   }

    printf("\n\n");
    
    insertValue(0,0,0);
	
	for(i=0;i<9;i++){
        printf("\n");
        for(j=0;j<9;j++){
           printf("%d ", a[i][j]);
        }
     }
    printf("\n\nIts done\n");

   return(1);
}
