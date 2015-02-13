// TextBuddy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TextBuddy.h"

using namespace std;

// TextBuddy class constructor.
TextBuddy::TextBuddy(){
  freePos = 0;
}

int TextBuddy::loadFile(char * fileName)
{
  int retCode = -1;
  clear(); // Clear all the existing data And the load data from file.

  ifstream infile(fileName,std::ios::_Nocreate);

  if (infile.is_open())
  {
    char strBuf[SIZE];
    while (!infile.eof()){
      infile.getline(strBuf, SIZE); // Read one line at a time.
      StrArray[freePos].assign(strBuf); // Copy read string to Array.
      ++freePos;
    }
    infile.close();
    retCode = 0;
  }
  return retCode;
}

int TextBuddy::saveFile(char * fileName)
{
  int retCode = -1;
  ofstream outfile(fileName);

  if (!outfile.bad())
  {
    for (int i = 0; i < freePos; ++i)
    {
      outfile << StrArray[i] << endl;
    }
    outfile.close();
    retCode = 0;
  }
  return retCode;
}
					
void TextBuddy::clear(void)
{
  for (int i = 0; i < freePos; ++i)
  {
    StrArray[i].erase();
  }
  freePos = 0; // Reset the free position index.
}

void TextBuddy::display(void)
{
  for (int i = 0; i < freePos; ++i)
  {
    if (!StrArray[i].empty())
      cout << i+1 << ". " << StrArray[i] << endl; // 0 offset corresponds to first string.
  }
}

int TextBuddy::add(string & str)
{
  StrArray[freePos].assign(str);
  ++freePos;
  return freePos;
}

int TextBuddy::remove(int pos)
{ 
  int retCode = -1;
  int index = pos - 1; // String offset starts from 0.
                       // but user string offset starts from 1.
  if ((index >= 0) && (index < freePos))
  {
    if (StrArray[index].empty())
      cout << "Warning: String was deleted earlier at position " << pos << endl;
    else
      StrArray[index].erase();

    retCode = index;
  }
  return retCode;
}


// Text Buddy Manger which takes user input and manipulates the 
// Text Buddy class object.
int TextBuddyManager(char *fileName)
{
  int retCode = -1;
  if (fileName){
    TextBuddy tb;
    tb.loadFile(fileName); // Load input file.

    // get user action and process it.
    string ipStr;
    string action, rest;
    while (1){ // infinite loop. breaks on exit command.
      cout << "command: ";
      getline(cin, ipStr);

      int pos = ipStr.find_first_of(" \t");  // parse the user input string to separate
      action.assign(ipStr.substr(0, pos));   // action and rest of the string.
      if (pos > 0){
        pos = ipStr.find_first_not_of(" \t", pos);
        rest.assign(ipStr.substr(pos, -1));    // require for 'add' and 'delete' command.
      }

      // tramsform all the character to lower case so that we can get case insensitive comparision.
      std::transform(action.begin(), action.end(), action.begin(), ::tolower);
      if (action.compare("clear") == 0)
        tb.clear();
      else if (action.compare("display") == 0)
        tb.display();
      else if (action.compare("add") == 0)
        tb.add(rest);
      else if (action.compare("delete") == 0)
      {
        int pos = atoi(rest.c_str());
        if (tb.remove(pos) == -1)
          cout << "Error: " << rest << " illegal range specified." << endl;
      }
      else if (action.compare("exit") == 0)
      {
        retCode = tb.saveFile(fileName); // Save output file.
        break; // come out of the loop;
      }
      else{
        cout << "Error: " << action << " action not defined." << endl;
      }
    }
  }
  return retCode;
}


// Main Application entry point.
int main(int argc, char* argv[])
{
	if(argc != 2){
	  cout<< "Error: Input arguments are not properly specified" << endl;
	 return -1;
	}
	cout << "Welcome to " << argv[1] << " is ready for use" << endl;
	return TextBuddyManager(argv[1]);
}

