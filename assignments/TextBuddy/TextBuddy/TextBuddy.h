/*


*/

#define SIZE 1024

class TextBuddy{
  std::array<std::string, SIZE> StrArray;
  int freePos;

public:
  TextBuddy();
  int loadFile(char * fileName);
  int saveFile(char * fileName);

  void clear(void);
  void display(void);
  int add(std::string& strData);
  int remove(int pos);   // delete is a keyword and hence can't use it.

};

int TextBuddyManager(char* fileName);



