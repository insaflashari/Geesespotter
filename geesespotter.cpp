//////////GEESESPOTTER PROJECT 3 final submission
/////////INSAF LASHARI
////////NOVEMBER 10, 2023

#include "geesespotter_lib.h"
#include <iostream>




///FUNCTIONS FOR 1ST TEST ( 1 to 5)



///Allocate a 1-dimensional char array with x_dim * y_dim elements and initialize each element with zero. Note
//that the initialization value is the value 0 and not the character '0'. The data type of the array is char not
//because ASCII characters are going to be stored in each element, but because char is an 8-bit data type.

char *create_board(std::size_t x_dim, std::size_t y_dim) {

    //initialize size
    std::size_t array_size {0};
    //elements in array
    array_size = x_dim * y_dim;

    //allocate array, type char
    char *array{new char [array_size]{0}};

    return array;

}


///Deallocate the given board - clears that board from memory
void clean_board(char *board) {

  delete[] board;
  board = nullptr;

}


  //////OUPUT: print the content of the board to std::cout 
  /////hidden field uses '*'
  ////marked filed uses 'M'
  ///otherwise field value is displayed ('0' to '9')
  //Note: only time filed with goose is displayed is at end of game (win or loss)
void print_board(char *board, std::size_t x_dim, std::size_t y_dim) {

    std::size_t count{0};
    //marked bit and hidden bit

///print contents of the 2D board into a 1D arrangement. ROW MAJOR ORDER
    for (int column{0}; column < y_dim; column++) {
        for (int row{0}; row < x_dim; row++) {

            //if marked print "M" to board
            //marked_bit AND field value should == marked_bit
            if ( (marked_mask() & board[count]) == marked_mask() ) {
                std::cout << "M";

            //if hidden print "*" to board
            //hidden_bit AND field value should == hidden_bit
             } else if ( (hidden_mask() & board[count]) == hidden_mask() ) {
                 std::cout << "*";

            //otherwise print numerical value at that point
            } else {
                std::cout << (int) (board[count] & value_mask());
            }
            //increment count variable (next index) for bit manipulation
            ++count;
        }
        std::cout << std::endl;
    }

}





///Hide all the field values. The hide_board function is called after a board has been created, geese spread (by
///geesespotter_lib.cpp), and neighbours calculated
void hide_board(char *board, std::size_t x_dim, std::size_t y_dim) {
    //array size
    std::size_t array_size{0};
    array_size = x_dim * y_dim;

    //go through the board
    
    for (std::size_t index{0}; index < array_size; index++) {
        //to hide all field, use hidden bit OR field value
        board[index] = hidden_mask() | board[index];
    }
    
}


///This function is called when the player attempts to mark a field. If the field is already revealed, its state
//should not be changed and the function returns the value 2. Otherwise, the Marked bit for the field is
//toggled and the function returns 0. If the Marked bit is on, then this function turns it off. If the Marked bit
//is off, then this function turns it on.
int mark(char *board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc) {
    //board
    char field = (y_loc * x_dim) + x_loc;
    
    if ( (hidden_mask() & board[field]) != hidden_mask() ) {
        //if field is already revealed (hidden bit AND field value 
        //does not equal hidden bit) return 2
        return 2;

    } else if ( (marked_mask() & board[field] ) == marked_mask() ) {
        //if it is marked(urunary (NOT) marked bit AND field value equals unmarked bit), unmark field
        board[field] = (board[field] & ~marked_mask());
        //exit function
        return 0;

    } else {
        //if field unmarked, mark it (field value OR marked bit equals marked field)
        board[field] = (board[field] | marked_mask() );
        //exit function
        return 0;
    }

}







///FUNCTIONS FOR FINAL TEST 



void compute_neighbours(char *board, std::size_t x_dim, std::size_t y_dim) {
    /// This function receives a board array with all elements set to the values 0 or 9. The function updates the
    //////board array such that all fields that do not have a goose (value 9) have their value set to the number of
    /////geese adjacent to that field


    // iterate through all the fields to see if value is 0 or 9
    for (int row{0}; row < y_dim; ++row) {
        for (int column{0}; column < x_dim; ++column){

            // calculate row and columnn indices for a 2D grid based on one-dimensional index
            // convert 2D grid coordinates into 1D coordinates (indices)

            // Calculate the 1D index corresponding to the current cell
            int index = row * x_dim + column;

            //// Skip if the current cell contains a goose (value 9)
            ///changed revealed geese, (hidden geese)
            if ((board[index] & value_mask()) == 0x09) { continue; }

            int goose_count{0}; // keep track of number of geese in board

            // checks neighbouring cells around current cell (creates (x_dim -1) * (y_dim - 1) grid)
            // bounds are row - 1 and row +1, and for column its -1 and +1 to create a smaller grid
            // NESTED FOR LOOP for smaller grid
            for (int x = {row - 1}; x <= (row + 1); ++x) {
                for (int y = {column - 1}; y <= (column + 1); ++y) {
                    if ((x < 0) || (x >= y_dim) || (y < 0) || (y >= x_dim) || ((x == row) && (y == column)) ) { 
                        continue; 
                    } // skips fields out of bounds

                    // Calculate neighbouring cell (1D index)
                    std::size_t coordinate{(x * x_dim) + y};

                    //// Increment goose_count if the neighboring cell contains a goose
                    //*****
                    if ((board[coordinate] & value_mask()) == 9)
                    {
                        //std::cout << coordinate << std::endl;
                        ++goose_count;
                    }
                }

            }
            // increase board coordinate by amnount of geese and new value in lower four bits
            // Update the current cell with the number of neighboring geese
            board[index] = goose_count;
        }
    }
}


bool is_game_won(char *board, std::size_t x_dim, std::size_t y_dim) {
      ///Determine whether the board is in a won state. The game is won when all fields that do not have a goose
//////have been revealed. Returns true if the game is won and false otherwise. Note the following special case.
/////By creating a 5 by 5 board with 25 geese on it, you would expect that you win immediately as every field
////contains a goose, however, this check is only made after a player has made an action

    std::size_t playing_board = x_dim * y_dim;

//go through all fields on the board
    for (std::size_t index{0}; index < playing_board; ++index) {
        //check if current field is hidden and does not contain a goose (9)
        if ( ((board[index] & hidden_mask()) == hidden_mask()) && ((board[index] & 0x09) != 0x09) )  {
            return false;
        }
    }
//if all unmarked fields without a goose are revealed, the game is won
    return true;

    
}



int reveal(char *board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc)
{

    /// This function reveals a field if it is hidden and unmarked. Revealing a field means
    //////to set the hiddenBit to zero for the specific field. If the field is marked, the function returns the value 1
    // without modifying the field. Marked fields can only be unmarked. If the field is already revealed, the
    // function returns the value 2 without modifying the field. If there is a goose in the field the function reveals
    // the field and then returns the value 9. For all other cases, the function returns the value 0.
    // If an empty field is revealed (it contains the value zero), also reveal the values of all unmarked neighboring
    // fields. Do not recursively reveal neighboring fields if they also are fields with zero geese. Reveal only the
    // neighboring 8 fields. The following shows the difference between the expected result and a recursive
    // reveal, when the location (2, 3) is revealed.

    // x_loc and y_loc are coordinates that the player chooses (x,y)
    std::size_t coordinate{(y_loc * x_dim) + x_loc};

    // if field is marked return 1
    if ((marked_mask() & board[coordinate]) == marked_mask())
    {
        return 1;
    }

    // if field is already revealed, return value 2
    if ((hidden_mask() & board[coordinate]) != hidden_mask())
    {
        return 2;
    }

    // if contains a goose, return value 9
    if ((board[coordinate] & value_mask()) == 9)
    {
        board[coordinate] = (board[coordinate] & ~hidden_mask());
        return 9;
    }

    // if value equals 0, reveal it and neighbouring fields
    if ((board[coordinate] & value_mask()) == 0) /// check
    {
        // reveal current field
        board[coordinate] &= ~hidden_mask();

        // iterare through the neighbouring fields
        for (int x = static_cast<int>(x_loc - 1); x <= static_cast<int>(x_loc + 1); ++x) {
            for (int y = static_cast<int>(y_loc - 1); y <= static_cast<int>(y_loc + 1); ++y){

                // break out of loop if (checking bounds)
                if ((x < 0) || (x >= y_dim) || (y < 0) || (y >= x_dim) || ((x == x_loc) && (y == y_loc)) ) { 
                    continue; 
                    }
             
                // Calculate neighbouring cell
                std::size_t neighbour{x * x_dim + y};

                // If the neighboring field is not marked, reveal it
                if ((board[neighbour] & marked_mask()) != marked_mask()) {
                    board[neighbour] &= ~hidden_mask();
                }
            }
        }

        //return 0;
    }

    // If the field contains a non-zero value, reveal it and return 0
    board[coordinate] &= ~hidden_mask();
    return 0;
}

 
