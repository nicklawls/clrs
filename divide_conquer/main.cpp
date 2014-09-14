/* 
 * CS141 Extra Credit
 * Nicolas Lawler
 * 5/29/14
 *
 *
 * All code is mine UNLESS OTHERWISE NOTED IN FUNCTION COMMENTS
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include "board.h"

using namespace std;


/* helper function headers */
vector<string> &split(const string&, char, vector<string>&);
void make_size_table(Board&, int &);
void store_instances(const Board&, const int, vector<pair<int,int>>&);
bool overlap(const Board&, pair<int,int>, pair<int,int>);
int min3(int, int, int);

int main(int argc, char** argv)
{
  vector<Board> boards_to_test;
  ifstream instream(argv[1]);

  if (instream.is_open()) {
    string line;
    unsigned int num_boards = 0, row = 0, col = 0;
    bool first_line = true;

    while (getline(instream, line)) { // parse one line at a time
      if (first_line) {
        if (line.size() == 0) {
          cout << "wrong first line" << endl;
          return -1;
        }
        num_boards = stoi(line,nullptr);
        cout << "Number of Boards: " << num_boards << endl;
        first_line = false;
      }

      else if (line.front() == 'F' || line.front() == 'R') {
        for (auto cell: line) {
          if (cell == 'F') {
            boards_to_test.back().set_cell(row, col, 1);
            col++;
          }
          else if (cell == 'R') {
            boards_to_test.back().set_cell(row, col, 0);
            col++;
          }
        }
        row++; col = 0;
      }

      else if (line.size() != 0) {  // line has board dimensions
        vector<string> dimensions;
        split(line, ' ', dimensions);
        boards_to_test.push_back(Board(stoi(dimensions[0],nullptr),
        stoi(dimensions[1],nullptr)));
        row = 0;
      }

      else { /*empty line, do nothing, so far...*/}
    }
    instream.close();
    if (num_boards != boards_to_test.size()) { // check your work
      cout << "CRITICAL BULLSHIT" << endl;
      return -1;
    }
  }

  else {
    cout << "FILE READ ERROR" << endl;
  }

  ofstream fout(argv[2]);

  if (!fout.is_open()) {
    cout << "output file failed to open" << endl;
    return -1;
  }

  for (auto board: boards_to_test) { // main calculation loop
    int max = 0;
    make_size_table(board, max);

    vector<pair<int,int>> max_instances;
    store_instances(board, max, max_instances);

    int second_biggest = 0;
    bool done = false;

    for(auto instance: max_instances) {
      for (int i = 0; i < board.depth() && !done; ++i) {
        for (int j = 0; j < board.length() && !done; ++j) {
          if (board.get_cell(i,j) > second_biggest) {
            if (!overlap(board, instance, make_pair(i,j))) {
              second_biggest = board.get_cell(i,j);
              if (second_biggest == max) {
                done = true;
              }
            }
          }
        }
      }
    }
    fout << max*max << " " << second_biggest*second_biggest << endl;
  }
  fout.close();
}

// checks if squares A and B in board b  overlap
bool overlap(const Board& b, pair<int,int> A2, pair<int,int> B2 )
{
  int Asize = b.get_cell(A2.first, A2.second);
  int Bsize = b.get_cell(B2.first, B2.second);

  pair<int,int> A1, B1;
  A1.first = A2.first - Asize + 1; A1.second = A2.second - Asize + 1;
  B1.first = B2.first - Bsize + 1; B1.second = B2.second - Bsize + 1;

  return (A1.first <= B2.first && A2.first >= B1.first &&
  A1.second <= B2.second && A2.second >= B1.second);
}

// finds instBnces of given number in board, stores coordinates in vector
void store_instances(const Board& board,
                     const int num,
                     vector<pair<int,int>>& instances) 
{
  for (int i = 0; i < board.depth(); ++i) {
    for (int j = 0; j < board.length(); ++j) {
      if (board.get_cell(i,j) == num) {
        instances.push_back(make_pair(i,j));
      }
    }
  }
}


// alters input board to store the sizes of squares with br corner (i,j)
// stores largest value found in max
void make_size_table(Board& source, int& max)
{
  for (int i = 1; i < source.depth(); ++i) { // table filling
    for (int j = 1; j < source.length(); ++j) {
      if (source.get_cell(i,j) == 1) {
        source.set_cell(i, j, 1 + min3(source.get_cell(i-1,j-1),
                                       source.get_cell(i,j-1),
                                       source.get_cell(i-1,j)));
        if (source.get_cell(i,j) > max) {
          max = source.get_cell(i,j);
        }
      }
    }
  }
}


// return minimum of 3 values
int min3(int a, int b, int c) {
  if (a <= b) {
    if (a <= c) {
      return a;
    } else {
      return c;
    }
  } else { // b < a
    if (b <= c) {
      return b;
    } else {
      return c;
    }
  }
}


// split a string on delim and store in predefined vector
// obtained at http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
// credit: Evan Teran
vector<string> &split(const string &s, char delim, vector<string> &elems) {
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}
