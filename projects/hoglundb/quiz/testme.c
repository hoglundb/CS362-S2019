#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    int randInt = 50;
    char randChar = ' ';
  //  while(randInt >44 && randInt < 90){
      randInt = (rand() %(127)) + 32;
      randChar = randInt;
  //  }

    return randChar;
}

char *inputString()
{
  //The imput domain for the random test
  char inputDomain[4] = {'r','e','s','t'};

  //Generating a string of random length from 1 to 60
  int randStringLen = (rand() % (50)) + 1;
  static char randString[51];
  memset(randString,'\0', sizeof(randString));
  int i;
  for(i = 0; i < randStringLen; i++){
    int randStringChar =  (rand() % (4));
    randString[i] = inputDomain[randStringChar];
  }

  //null terminate the sting at the point we it is randomly ended
  randString[i] = '\0';

  return randString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;

  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error \n\n");
return ;
     //exit(200);
    }
  }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
  //  inputChar();
  printf("test\n\n\n");
    return 0;
}
