#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <ctime>

bool merge_num(std::vector<int>& v, int bi, int ei);
void rotate_anti_clock(std::vector<int>& v);
bool game_over(const std::vector<int>& v);
void print_grid(const std::vector<int>& v);

int xytoi (int x, int y, int rowlen);
bool up (std::vector<int>& v);
bool down (std::vector<int>& v);
bool left (std::vector<int>& v);
bool right (std::vector<int>& v);
void random_two (std::vector<int>& v);

int main () {

  srand(time(0));
  std::vector<int> v;
  std::string inputvector;

  std::cout << "enter initial configuration file name: " << std::endl;
  std::cin >> inputvector;

  std::ifstream inputfile;
  inputfile.open(inputvector.c_str());

  // if inputfile is not valid
  if(!inputfile.is_open()){
      std::cout << "file not found, using default start configuration: " << std::endl;

      //setting vector "v"
      for (int i = 0; i < 15; i++){
          v.push_back(0);
      }
      v.push_back(2);
  }

  //if inputfile is valid
  else {
      int tmpvec;
      while(inputfile >> tmpvec){
          v.push_back(tmpvec);
      }
  }

  print_grid(v); //print on the screen intial configuration

  bool gameover = game_over(v);
  bool mergecomplete = false;
  while (gameover == false) {
    //reads movement command from user and executes it
    bool inputvalid = false;
    while (inputvalid == false) {
      std::string move;
      std::cin >> move;
      std::cout<<std::endl;


      if (move == "w"){
        mergecomplete = up(v);
        inputvalid = true;
      }

      else if(move == "s"){
        mergecomplete = down(v);
        inputvalid = true;
      }

      else if(move == "a"){
        mergecomplete = left(v);
        inputvalid = true;
      }

      else if(move == "d"){
        mergecomplete = right(v);
        inputvalid = true;
      }
    }
    //prints grid after each change, and generates a random 2
    if (mergecomplete) {
      random_two(v);
      print_grid(v);
      std::cout<<std::endl;
    }
    gameover = game_over(v);
  }
  std::cout << "game over" << std::endl;
  return 0;
}

int xytoi(int x, int y, int rowlen){
    return x*rowlen+y;
}

bool merge_num(std::vector<int>& v, int bi, int ei){
  std::vector<int> vtemp;
  bool movement = false;

  for (int i = bi; i < ei; i++){
    if (v[i] != 0){
      vtemp.push_back(v[i]);
    }
  }
  vtemp.push_back(0);
  //vtemp.push_back(0);

  for (int i=0; i < vtemp.size()-1; i++){
    if (vtemp[i] == vtemp[i+1]){
    vtemp[i] = 2*vtemp[i];
    vtemp[i+1] = 0;
    i++;
    }
  }

  std::vector<int> vmerged;
  vmerged = v;

  for(int i =0; i < v.size(); i++){
    vmerged[i] = v[i];
  }

  for (int i = bi; i < ei; i++){
    vmerged[i] = 0;
  }

  int counter = 0;
  for (int i = bi; counter < vtemp.size() ; counter++){
    if (vtemp[counter] != 0){
      vmerged[i] = vtemp[counter];
      i++;
    }
  }

  for (int i=0; i < v.size() && movement == false; i++){
    if (v[i] != vmerged[i]){
      movement = true;
    }
  }

  v = vmerged;
  return movement;
}

void rotate_anti_clock(std::vector<int>& v){
  int side = std::sqrt(v.size());
  std::vector<int> vtemp;
  for(int j=side-1; j >= 0 ; j--){
    for (int i=0; i < side; i++){
      vtemp.push_back(v[xytoi(i,j,side)]);
    }
  }

  for(int i =0; i <vtemp.size(); i++){
    v[i] = vtemp[i];
  }
}

bool game_over(const std::vector<int>& v){
  for(int i = 0; i < v.size(); i++){
    if(v[i] == 0){
      return false;
    }
  }

  int side = std::sqrt(v.size());

  //checking vertical
  for(int i = 0; i < side; i++){
    for(int j = 0; j <side - 1; j++){
      if(v[xytoi(i,j,side)] == v[xytoi(i,j+1,side)]){
        return false;
      }
    }
  }

  //checking horizontal
  for(int i = 0; i <side - 1; i++){
    for(int j = 0; j < side; j++){
      if(v[xytoi(i,j,side)] == v[xytoi(i+1,j,side)]){
        return false;
      }
    }
  }

  return true;
}

void print_grid(const std::vector<int>& v){
  int side = std::sqrt(v.size());
  for (int j=0; j < side; j++){
    for(int i=0; i < side ; i++){
      std::cout << v[xytoi(j,i, side)] <<"\t";
    }
    std::cout << std::endl;
  }
}

bool up (std::vector<int>& v) {
  int side = std::sqrt(v.size());
  //rotate the vector anticlockwise once
  rotate_anti_clock(v);
  //call the merge function, so that the rows all get shifted correctly
  bool operation = false;
  for (int i = 0;i < side;i++) {
    if(operation){
      merge_num (v,(i*side),((i+1)*side));
    }
    else {
      operation = merge_num (v,(i*side),((i+1)*side));
    }
  }
  //rotate the vector three times (set it back)
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  return operation;
}

bool down (std::vector<int>& v) {
  int side = std::sqrt(v.size());
  //rotate the vector anticlockwise
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  //call the merge function, so that the rows all get shifted correctly
  bool operation = false;
  for (int i = 0;i < side;i++) {
    if(operation){
      merge_num (v,(i*side),((i+1)*side));
    }
    else {
      operation = merge_num (v,(i*side),((i+1)*side));
    }
  }
  //rotate the vector back
  rotate_anti_clock(v);
  return operation;
}

bool left (std::vector<int>& v) {
  int side = std::sqrt(v.size());
  //call the merge function, so that the rows all get shifted correctly
  bool operation = false;
  for (int i = 0;i < side;i++) {
    if(operation){
      merge_num (v,(i*side),((i+1)*side));
    }
    else {
      operation = merge_num (v,(i*side),((i+1)*side));
    }
  }
  return operation;
}

bool right (std::vector<int>& v) {
  int side = std::sqrt(v.size());
  //rotate the vector anticlockwise
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  //call the merge function, so that the rows all get shifted correctly
  bool operation = false;
  for (int i = 0;i < side;i++) {
    if(operation){
      merge_num (v,(i*side),((i+1)*side));
    }
    else {
      operation = merge_num (v,(i*side),((i+1)*side));
    }
  }
  //rotate the vector back
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  return operation;
}

void random_two(std::vector<int>& v){
  std::vector<int> zeroposition;

  for(int i =0; i < v.size(); i++){
    if(v[i] == 0){
      zeroposition.push_back(i);
    }
  }
  v[zeroposition[rand() % zeroposition.size()]] = 2;
}
