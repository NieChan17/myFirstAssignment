#include "tay_nguyen_campaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

const int MAX_LINES = 5;         
const int MAX_LINE_LENGTH = 100;

// Task 0: Read input file
bool readFile(
    const string &filename,
    int LF1[], int LF2[],
    int &EXP1, int &EXP2,
    int &T1, int &T2, int &E)
{
  char data[MAX_LINES][MAX_LINE_LENGTH];
  int numLines = 0;

  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    return false;
  }

  while (numLines < MAX_LINES && ifs.getline(data[numLines], MAX_LINE_LENGTH))
  {
    numLines++;
  }
  ifs.close();

  if (numLines < MAX_LINES)
  {
    return false;
  }
  int a = strlen(data[0]);
  int b = strlen(data[1]);
  int idx = 0;
  int num = 0;
  // Extract LF1[]
  for (int i = 1; i < a; i++){
    if ( data[0][i] == ',' || data[0][i] == '[' || data[0][i] == ']'){
      LF1[idx] = num;
      idx ++;
      num = 0;
    }else{
      num = num*10 + data[0][i] - '0';   
    }   
  }
num = 0;
idx = 0;
// Extract LF2[]
for (int i = 1; i < b; i++){
    if ( data[1][i] == ',' || data[1][i] == '[' || data[1][i] == ']'){
      LF2[idx] = num;
      idx ++;
      num = 0;
    }else{
      num = num*10 + data[1][i] - '0';
    }    
  }
num = 0;
// Extract EXP1, EXP2
for (int j = 0; j < strlen(data[2]); ++j){
    if ( data[2][j] == ' '){
      EXP1 = num;
      num = 0;
    }else{
      num = num*10 + data[2][j] - '0';
    }
    EXP2 = num;    
  }
num = 0;
// Extract T1,T2
for (int j = 0; j < strlen(data[3]); ++j){
  if ( data[3][j] == ' '){
    T1 = num;
    num = 0;
  }else{
    num = num*10 + data[3][j] - '0';
  }
  T2 = num;    
}
num = 0;
idx = 0; 
// Extract E
for (int j = 0; j < strlen(data[4]); ++j){
  num = num*10 + data[4][j] - '0';
  E = num;  
}

// Set limit of data following requirements

for (int i = 0; i < 17; i ++){
  if(LF1[i] > 1000) LF1[i] = 1000;
  if(LF1[i] < 0) LF1[i] = 0;
  if(LF2[i] > 1000) LF2[i] = 1000;
  if(LF2[i]< 0) LF2[i] = 0;
}
if(EXP1 > 600 ) EXP1 = 600;
if(EXP1 < 0) EXP1 = 0;
if(EXP2 > 600 ) EXP2 = 600;
if(EXP2 < 0) EXP2 = 0;
if(T1 > 3000) T1 = 3000;
if(T2 > 3000) T2 = 3000;
if(T1 < 0) T1 = 0;
if(T2 < 0) T2 = 0;
if(E > 99) E = 99;
if(E < 0) E = 0;

return true;
}


// Finding a set that its sum satisfied shortfall
// Return sum;
int minSum = 3001;              
void find(int selection[], int start, int depth, int sum, int shortfall) {
    if (depth == 5) {
        if (sum >= shortfall && sum < minSum) {
            minSum = sum; 
        }
        return;
    }
    if (start > 25 - (5 - depth)){ 
      return;
    }
    for (int i = start; i < 25; i++) {
        int newSum = sum + selection[i];
        if (newSum >= minSum) continue;
        find(selection, i + 1, depth + 1, newSum, shortfall);
    }
}
void call(int shortfall, int selection[]) {
  find(selection, 0, 0, 0, shortfall);
  if (minSum != 3001) {
      return;
  } 
}
// Find lowest number in 2

int minNumber(int Cal){
  if( Cal > 3000) return 3000;
  return Cal;
}

// Find largest number (using for task 2)
int maxNumber(int a, int b, int c){
  int max = a;
  if (b > a && b > c){
      max = b;
  }else if(c > a){
      max = c;
  }else{}
  return max;
}
// Task 1
int gatherForces(int LF1[], int LF2[])
{
  int result = 0;
  int weight[17] = {1,2,3,4,5,7,8,9,10,12,15,18,20,30,40,50,70};
  for ( int i = 0; i < 17; ++i){
    result += (LF1[i] + LF2[i])*weight[i];
  }
  return result;
}
// Task 2
string determineRightTarget(const string &target)
{
  // TODO: Implement this function
  int extract[target.length()];
  int ID, idx = 0;
  // Extract number of string and update idx variable 1 unit after we find out one number
  for(int i = 0; i < target.length(); i++){
      if((target[i]) <= '9' && (target[i]) >= '0'){
      extract[idx] = (target[i]) - '0';
      idx++;
      }
  }
  // Using idx variable devided into many case and calculate IDs value
  string rightTarget;
  if (idx == 0 || idx > 3){
      rightTarget = "INVALID";
  }else{
      switch(idx){
          case 1:
          if(extract[0] > 7){
            rightTarget = "INVALID";
          }else if(extract[0] >= 0 && extract[0] <= 2){ 
            rightTarget = "DECOY";
          }else{
            ID = extract[0];
          }
          break;
          case 2:
          ID = ((extract[0] + extract[1]) % 5 + 3);
          break;
          case 3:
          ID = maxNumber(extract[0], extract[1], extract[2]) % 5 + 3 ; 
      }
  }
  // Compare ID value suitable with historical event name
  switch(ID){
      case(3): rightTarget = "Buon Ma Thuot"; break;
      case(4): rightTarget = "Duc Lap"; break;
      case(5): rightTarget = "Dak Lak"; break;
      case(6): rightTarget = "National Route 21"; break;
      case(7): rightTarget = "National Route 14"; break;
  }
  return rightTarget;
}

string decodeTarget(const string &message, int EXP1, int EXP2)
{
  // TODO: Implement this function
  int shift = (EXP1 + EXP2) % 26;
  string copyString1;
  string copyString2;
  string rightTarget;
  copyString1 = message;
// Check if the input string is valid or invalid
  if( copyString1.length() == 0){
      rightTarget = "INVALID";
  }
  if( copyString1.length() == 1 || copyString1[0] == ' '){
      rightTarget = "INVALID";
  }
  for(int i = 0; i < copyString1.length(); i++){
      if(copyString1[i] == ' ' || (copyString1[i] >= '0' && copyString1[i] <= '9')){}
      if(copyString1[i] < 'A' || copyString1[i] > 'z' || (copyString1[i] >'Z' && copyString1[i] <'a')){
          rightTarget = "INVALID";
      }
  }
// Decrypt the valid string by using Caesar Cipher method
// Decrypt the valid string by using reverse string method
  if(EXP1 >= 300 && EXP2 >= 300){
      for( int i = 0; i < copyString1.length(); i++){
          if(copyString1[i] == ' ' || (copyString1[i] >= '0' && copyString1[i] <= '9')){}
          if(copyString1[i] >= 'a' && copyString1[i] <= 'z') copyString1[i] = (copyString1[i] - 'a' + shift) % 26 + 'a';
          if(copyString1[i] >= 'A' && copyString1[i] <= 'Z') copyString1[i] = (copyString1[i] - 'A' + shift) % 26 + 'A';    
      }
  }else if( EXP1 < 300 || EXP2 < 300){
      copyString2 = copyString1;
      for( int i = 0; i <= copyString1.length(); i++){
        copyString1[i] = copyString2[copyString1.length()-1-i];
      }
  }
// Convert decrypted string to its correct form
  for ( int i = 0; i < copyString1.length(); i++){
      if(i == 0 || copyString1[i-1] == ' '){
          if(copyString1[i] >= 'a' && copyString1[i] <= 'z'){
            copyString1[i] -= 32;
          }
      }else{if(copyString1[i] >= 'A' && copyString1[i] <= 'Z') copyString1[i] += 32;
      }
  }
// Compare decrypted string with target
  if(copyString1 == "Buon Ma Thuot"){
      rightTarget = "Buon Ma Thuot";
  }else if(copyString1 == "Duc Lap"){
      rightTarget = "Duc Lap";
  }else if(copyString1 == "Dak Lak"){
      rightTarget = "Dak Lak";
  }else if(copyString1 == "National Route 21"){
      rightTarget = "National Route 21";
  }else if(copyString1 == "National Route 14"){
      rightTarget = "National Route 14";
  }else{
      rightTarget = "INVALID";
  }

  return rightTarget;
}

// Task 3
void manageLogistics(int LF1, int LF2, int EXP1, int EXP2, int &T1, int &T2, int E)
{

  // Calculate delta T1, delta T2 by using given formulas
  double deltaT1 = (LF1/(LF1+LF2)*(T1+T2))*(1+((EXP1 - EXP2)/100) + 0.0);
  double deltaT2 = (T1+T2) - deltaT1 + 0.0;
  // Calculate T1, T2 follow historical event value E
  if(E == 0){
  T1 = ceil(T1 + deltaT1);
  T2 = ceil(T2 + deltaT2);
  }
  if (E >= 1 && E <= 9){
    T1 = ceil(T1 - (0.01*E*T1));
    T2 = ceil(T2 - (0.005*E*T2));
  }else if( E >= 10 && E <= 29){  
    T1 = ceil(minNumber(T1 + E*50.0));
    T2 = ceil(minNumber(T1 + E*50.0));
  }else if( E >= 30 && E <= 59){
    T1 = ceil(minNumber(T1 + (0.005*E)));
    T2 = ceil(minNumber(T2 + (0.002*E)));
  }else{} 
  if(T1 > 3000) T1 = 3000;
  if(T1 < 0) T1 = 0;
  if(T2 > 3000) T2 = 3000;
  if(T2 < 0) T2 = 0;
}

// Task 4
int planAttack(int LF1, int LF2, int EXP1, int EXP2, int T1, int T2, int battleField[10][10])
{
  // TODO: Implement this function
  double S = (LF1 + LF2) + (EXP1 + EXP2)*5 + (T1+T2)*2;
  for( int i = 0; i < 10; i++ ){
    for( int j = 0; j < 10; j++){
      if( i % 2 == 1){
        S = S - (((battleField[i][j]*3.0)/2));
      }else{
        S = S - (((battleField[i][j]*2.0)/3));
      }
    }
  }
  return ceil(S);
}

// Task 5
int resupply(int shortfall, int supply[5][5])
{
  // TODO: Implement this function

  // Convert 2 dimension array into 1 dimension array(selection)
  int selection[25];
  int temp1 = 0;
  for(int i = 0; i < 5; ++i){
    for(int j = 0; j < 5; ++j){
      selection[temp1] = supply[i][j];
      temp1 ++;
      }
    }

  // Arrange elements of selection array from lowest to highest
  int idx = 0;
  for(int i = 0; i < 25; i++){
    for(int j = i + 1 ; j < 25; j++){
      if (selection[i] > selection[j]){
        idx = selection[i];
        selection[i]= selection[j];
        selection[j] = idx;
      }
    }
  }
  // Find 5 elements that its sum satisfy the requirement and return its sum 
  call(shortfall, selection);
  return minSum;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
