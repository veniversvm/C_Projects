/* wordle.txt */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define ResultGreen 0
#define ResultYellow 2
#define ResultRed 4
#define max 5195

typedef char Result;

// Structs //
struct s_result
{
  char color[5];
};

struct s_word {
  char **array;
  int n;
};

typedef struct s_word Words;

// This is a function definition/signature
int main(int, char **);
void cw(char *guess, char *word, Result *output_res);
Result check_char(char, int, char *);
void Example_print_result(Result *res);
bool insin(char, char *);

// Funciton Implementations
Words readfile(char *filename)
{
  char buf[8];
  static char ret[max][5];
  int i, size;
  FILE *fd;

  // Words words;


  fd = fopen(filename, "r");
  if (!fd)
  {
     perror("fopen");
     Words words = {
      .array = (char **)0,
      .n = 0,
     };
     return words;
  }

  size = max * 5;


  i= 0;


  memset(buf, 0 , 8);
  while (fgets(buf, 7, fd))
  {
    size = strlen(buf);
    size = size >= 5 ? 5 : -1 ;
    
    if (size == -1)
    {
      memset(buf, 0, 8);
      continue;
    }

    buf[size] = 0;

    if (size != 5)
    {
      memset(buf, 0, 8);
      continue;
    }

    ret[i][0] = buf[0];
    ret[i][1] = buf[1];
    ret[i][2] = buf[2];
    ret[i][3] = buf[3];
    ret[i][4] = buf[4];

    memset(buf, 0, 8);
    i++;

    if  (max <= i)
    {
      break;
    }

  }

  fclose(fd);
  Words words = {
    .array = (char **)&ret,
    .n = i
  };
  
  return words;
}

bool isin(char c, char *str)
{
  bool ret;
  int i, size;

  ret = false;
  size = strlen(str);

  for (i = 0; i < size; i++)
  {
    if (str[i] == c)
    {
      ret = true;
      break;
    }
  }

  return ret;
}

void Example_print_result(Result *res)
{
  int i;

  for (i = 0; i < 5; i++)
    switch (res[i])
    {
    case ResultGreen:
      printf("%s\n", "Green");
      break;
    case ResultYellow:
      printf("Yellow\n");
      break;
    case ResultRed:
      printf("Red\n");
      break;
    default:
      printf("Unknow\n");
      break;
    }
  return;
}

Result check_char(char guess, int index, char *word)
{
  char correct;

  correct = word[index];

  if (guess == correct)
  {
    return ResultGreen;
  }
  else if (isin(guess, word))
  {
    return ResultYellow;
  }

  return ResultRed;
}

void cw(char *guess, char *word, Result *output_res) // Cambiado a void
{
  int i;

  for (i = 0; i < 5; i++)
  {
    output_res[i] = check_char(guess[i], i, word); // Escribir en el puntero de salida
  }
  // Ya no retorna nada
}

int main(int argc, char *argv[])
{
  char *correct, *guess;
  Result game_result[5]; // Declarar un array para almacenar el resultado
  
  printf("Welcome to Wordle!\n");
  if (argc < 3)
  {
    fprintf(stderr, "USAGE: %s CORRECTWORD GUESS\n", argv[0]);
    return -1;
  }

  correct = argv[1]; // Mueve esto antes de la llamada a cw
  guess = argv[2];   // Mueve esto antes de la llamada a cw

  // Llamada a la función
  cw(correct, guess, game_result);
  Example_print_result(game_result); // Pasar el array completo


  return 0;
}


  return 0;
}
