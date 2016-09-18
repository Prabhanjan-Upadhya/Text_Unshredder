#include<iostream>
#include<unordered_map>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace std;

void create_dict(unordered_map<string, int>& corpus){

  /*
     Creates a dictionary of 4-grams with its frequency distribution
  */  
  cout << "Creating a dictionary" << endl;
  ifstream file("dict.txt");
  string str("");
  char c, prev;
  file.get(prev);
  str += prev;
  for( uint i=1; i< 4; ++i){
    file.get(c);
    if(prev == ' ' && c == ' '){
      while(file.get(c)){
        if(c != prev)
	  break;
      }
    }
    str += c;
    prev = c;
  }
  corpus[str]++;
  corpus["count"]++;
  while(file.get(c)){
    if( prev == ' ' && c == ' '){
      while(file.get(c)){
        if(c != prev){
	  break;
        }
      }
    }
    prev = c;
    str += c;
    str.erase(str.begin());
    corpus[str]++;
    corpus["count"]++;
  }
  file.close();
  cout << "Done with the dictionary" << endl;
}


/*
  Returns likelihood of substring str being a valid 4-gram.
*/
float probability(unordered_map<string, int>& corpus, string str){
  return float((float)(corpus[str]+1)/ (float)(corpus.size()+corpus["count"]));
}

/*
  Reads the scrambled input data from input.txt file.
*/
void read_input(vector<vector<string> >& input){
  ifstream file("input.txt");
  string line;

  while(getline(file, line)){
    vector<string> temp;
    size_t newpos;
    size_t pos=0;
    while(pos < line.size()){
      newpos = line.find_first_of("|", pos);
      if(pos != newpos){
        temp.push_back(line.substr(pos,newpos-pos));
      }
      pos = newpos + 1;
    }
    input.push_back(temp);
  }
  file.close();
}

/*
 Calculates and returns the probability of 2 rows being next to each other from the transposed input matrix. 
*/

float strip_correction(unordered_map<string, int>& corpus, vector<string> left, vector<string> right){
  float prod = 1;
  for( uint i=0; i< left.size(); ++i){
    prod *= probability(corpus, (left[i]+right[i]) );
  }
  return prod;
}

/*
  Prints a vector of vector of strings.
*/

void print_vec(const vector<vector<string> >& input){
  for( uint i=0; i< input.size(); ++i){
    for( uint j=0; j< input[i].size(); ++j)
      cout << "(" << input[i][j] << ")" ;
    cout << endl;
   }
}

/*
  Displays the unscrambled output.
*/

void display_out(const vector<vector<string> >& input){
  for( uint i=0; i< input.size(); ++i){
    for( uint j=0; j< input[i].size(); ++j)
      cout << input[i][j];
    cout << endl;
   }
}

/*
  Takes in the transposed form of the original input data.
  Reorders the strips into corrected data.
*/

vector<vector<string> > reorder(unordered_map<string, int>& corpus, vector<vector<string> >& input){
  int ele1, ele2;
  float max_pair_prob = float(-INT_MAX);
  vector<vector<string> > correct_strips;
  for( uint i=0; i < input.size(); ++i){
    for( uint j=0; j< input.size(); ++j){
      if( i != j){
        float pair_prob = strip_correction(corpus, input[i], input[j]);
	if(pair_prob > max_pair_prob){
          ele1 = i; ele2 = j;
          max_pair_prob = pair_prob;
        }
      }
    }
  }
  correct_strips.push_back(input[ele1]);
  correct_strips.push_back(input[ele2]);
  
  if(ele1 > ele2){
    input.erase(input.begin() + ele1);
    input.erase(input.begin() + ele2);
  }
  else{
    input.erase(input.begin() + ele2);
    input.erase(input.begin() + ele1);
  }
  
  while(input.size()){
    float max_left = float(-INT_MAX);
    float max_right = float(-INT_MAX);
    int right_index;
    int left_index;
    int del_index;
 
    for( uint i=0; i< input.size(); ++i){
      float left_prob = strip_correction(corpus, input[i], correct_strips[0]);
      if(left_prob > max_left){
        left_index = i;
        max_left = left_prob;
      }

      float right_prob = strip_correction(corpus, correct_strips[correct_strips.size()-1], input[i]);
      if(right_prob > max_right){
        right_index = i;
        max_right = right_prob;
      }
    }
    if(max_right >= max_left){
      correct_strips.push_back(input[right_index]);
      del_index = right_index;
    }  
    else{
      correct_strips.insert(correct_strips.begin(), input[left_index]);
      del_index = left_index;
    }
    input.erase(input.begin()+del_index);
  } 
  return correct_strips;
}

/*
  Transposes input matrix for ease of accessing each strips.
*/

vector<vector<string> > transpose_matrix(vector<vector<string> >& input){
  uint height = input.size();
  uint width = input[0].size();
  
  vector<vector<string> > result;

  for( uint i=0; i < width; ++i){
    vector<string> temp;
    for( uint j=0; j< height; ++j){
      temp.push_back(input[j][i]);
    }
    result.push_back(temp);
  }
  return result;
}

int main(){
  unordered_map<string, int> corpus;
  create_dict(corpus);

  
  vector<vector<string> > input;
  read_input(input);
  print_vec(input);
  cout << endl; 

  vector<vector<string> > input_transpose = transpose_matrix(input);
  vector<vector<string> > result = reorder(corpus,input_transpose);
  
  display_out(transpose_matrix(result));
  return 0;
}
