//  Data Structures and Algorithms
//  Programming Project 1
//  IrmaMoves.c
//
//  IrmaMoves
//
//  Created by Kyle Spomer on 10/8/17.
//  Copyright © 2017 Kyle Spomer. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IrmaMoves.h"

char **createMapBoard(void){
    char **board = malloc(8*sizeof(char *)); //dynamically allocate memory for rows
    
    for(int i = 0 ; i < 8 ; i++) //dynamically allocate memory for indiviual elements
        board[i] = malloc( 8*sizeof(char) );
    
    board[0][0] = 'F'; //initialize the array with the map layout
    board[0][1] = 'F';
    board[0][2] = ' ';
    board[0][3] = ' ';
    board[0][4] = ' ';
    board[0][5] = ' ';
    board[0][6] = ' ';
    board[0][7] = ' ';
    board[1][0] = ' ';
    board[1][1] = 'F';
    board[1][2] = ' ';
    board[1][3] = ' ';
    board[1][4] = ' ';
    board[1][5] = ' ';
    board[1][6] = ' ';
    board[1][7] = ' ';
    board[2][0] = ' ';
    board[2][1] = 'F';
    board[2][2] = 'F';
    board[2][3] = ' ';
    board[2][4] = ' ';
    board[2][5] = ' ';
    board[2][6] = ' ';
    board[2][7] = ' ';
    board[3][0] = ' ';
    board[3][1] = ' ';
    board[3][2] = 'F';
    board[3][3] = ' ';
    board[3][4] = ' ';
    board[3][5] = ' ';
    board[3][6] = ' ';
    board[3][7] = ' ';
    board[4][0] = ' ';
    board[4][1] = ' ';
    board[4][2] = 'K';
    board[4][3] = ' ';
    board[4][4] = ' ';
    board[4][5] = ' ';
    board[4][6] = ' ';
    board[4][7] = ' ';
    board[5][0] = 'C';
    board[5][1] = ' ';
    board[5][2] = ' ';
    board[5][3] = 'B';
    board[5][4] = ' ';
    board[5][5] = ' ';
    board[5][6] = ' ';
    board[5][7] = ' ';
    board[6][0] = ' ';
    board[6][1] = 'C';
    board[6][2] = 'C';
    board[6][3] = ' ';
    board[6][4] = 'D';
    board[6][5] = ' ';
    board[6][6] = ' ';
    board[6][7] = ' ';
    board[7][0] = ' ';
    board[7][1] = ' ';
    board[7][2] = 'C';
    board[7][3] = ' ';
    board[7][4] = ' ';
    board[7][5] = 'D';
    board[7][6] = 'D';
    board[7][7] = ' ';
    
    return board;
};


char **destroyMapBoard(char **board){
    //frees up the memory allocated to the board
    free(board);
    return NULL;
};

void printMapBoard(char **board){
    //printing the map in the specified format
    printf("========\n");
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            printf("%c",board[i][j]);}
        printf("\n");}
    printf("========");
    printf("\n");
    printf("\n");
};


int colToInt(char col){
    //this is a helper function to convert the char col index to a usable int index
    if (col == 'a')
        return 0;
    if (col == 'b')
        return 1;
    if (col == 'c')
        return 2;
    if (col == 'd')
        return 3;
    if (col == 'e')
        return 4;
    if (col == 'f')
        return 5;
    if (col == 'g')
        return 6;
    if (col == 'h')
        return 7;
    else{
        puts("Column Error!");
        return 0;
        
    }
};

void vertMove(char **board, Move *Irma){
    //this is a helper function to handle N->S and S->N movements
    int direction = 0;
    
    //Determing the direction
    if (Irma->from_loc.row > Irma->to_loc.row)
        direction = -1; //North
    if (Irma->from_loc.row < Irma->to_loc.row)
        direction = 1; //South
    if (Irma->from_loc.row == Irma->to_loc.row)
        direction = 0; //No movement
    
    //Handles wind speeds and wind gusts for each space moved
    for(int i = Irma->from_loc.row; i != Irma->to_loc.row; i+= direction){
        if(board[i+direction][colToInt(Irma->to_loc.col)] == ' '){
            Irma->irma.ws+=6;
            Irma->irma.wg+=3;
        }
        else if(board[i+direction][colToInt(Irma->to_loc.col)] != ' '){ //else if implemented due to bugs with else
            Irma->irma.ws-=2;
            Irma->irma.wg-=1;
        }
    }
};

void horizMove(char **board, Move *Irma){
    //this is a helper function to handle E->W and W->E movements
    int direction = 0;
    
    //Determining the direction
    if (colToInt(Irma->from_loc.col) > colToInt(Irma->to_loc.col))
        direction = -1; //West
    if (colToInt(Irma->from_loc.col) < colToInt(Irma->to_loc.col))
        direction = 1; //East
    if (colToInt(Irma->from_loc.col) == colToInt(Irma->to_loc.col)){
        direction = 0; // No movement
    }

    //Handles wind speeds and wind gusts for each space moved
    for(int i = colToInt(Irma->from_loc.col); i != colToInt(Irma->to_loc.col); i += direction){

        if(board[Irma->from_loc.row][i+direction] == ' '){
            Irma->irma.ws+=10;
            Irma->irma.wg+=5;
        }
        else if(board[Irma->from_loc.row][i+direction] != ' '){ //else if implemented due to bugs with else
            Irma->irma.ws-=15;
            Irma->irma.wg-=10;
        }
    }
};

char **predictIrmaChange (char* str, Move *irmaMove){
    //initialize empty board
    char **board = createMapBoard();
    
    //parse the input string
    parseNotationString(str, irmaMove);
    
    //get initial coordinates
    int row = irmaMove->from_loc.row;
    int col = colToInt(irmaMove->from_loc.col);
    
    //print Initial Location
    board[row][col] = 'I';
    printMapBoard(board);
    destroyMapBoard(board);
    
    //calculate moves effect on ws and wg
    horizMove(board, irmaMove);
    vertMove(board, irmaMove);
    
    //get final coordinates
    row = irmaMove->to_loc.row;
    col = colToInt(irmaMove->to_loc.col);
    
    //print final Location
    board = createMapBoard();
    board[row][col] = 'I';
    printMapBoard(board);
    
    return board;
};

void parseNotationString(char *str, Move *Irma){
    //parse start location
    Irma->from_loc.col = str[0];
    Irma->from_loc.row = atoi(&str[1]);
   
    char temp[3];
    
    //parse wind speeds
    for (int i = 0; i < 3; i ++)
        temp[i] = str[i+3];
    Irma->irma.ws = atoi(temp);
    
    //parse wind gusts
    for (int i = 0; i < 3; i ++)
        temp[i] = str[i+7];
    Irma->irma.wg = atoi(temp);
    
    //parse final location
    Irma->to_loc.col = str[11];
    Irma->to_loc.row = atoi(&str[12]);
    
};


double difficultyRating(void){
    return 3;
};


double hoursSpent(void){
    return 5;
};
