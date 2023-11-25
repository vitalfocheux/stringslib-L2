#include "stringslib.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

size_t str_length(const char *str)
{
  if (str == NULL)
  { // vérifie que str est un pointeur NULL ou non
    return 0;
  }
  size_t i = 0;
  while (str[i] != '\0')
  {
    ++i;
  }
  return i;
}

int str_compare(const char *str1, const char *str2)
{
  // vérifie les cas où str1 ou str2 sont des chaines de caractères vides
  if (str1[0] == '\0')
  {
    if (str2[0] == '\0')
    {
      return 0;
    }
    return -1;
  }
  else if (str2[0] == '\0')
  {
    return 1;
  }

  int i = 0;

  // compare les caractères de str1 et str2 un par un
  while ((str1[i] != '\0') && (str2[i] != '\0'))
  {
    if (str1[i] < str2[i])
    {
      return -1;
    }
    else if (str1[i] > str2[i])
    {
      return 1;
    }
    ++i;
  }

  // compare si str1 ou str2 est plus grand de l'un que de l'autre
  if ((str1[i] == '\0') && (str2[i] != '\0'))
  {
    return -1;
  }
  else if ((str1[i] != '\0') && (str2[i] == '\0'))
  {
    return 1;
  }

  return 0;
}

const char *str_search(const char *needle, const char *haystack)
{
  // vérifie le cas où on cherche une chaine de caractère vide
  if (needle[0] == '\0')
  {
    return haystack;
  }

  size_t haystack_l = str_length(haystack);
  size_t needle_l = str_length(needle);

  for (size_t i = 0; i < haystack_l; ++i)
  {
    // vérifie le cas où le needle est un chaine plus longue que le haystack
    if ((haystack[i] == '\0') && (needle[i] != '\0'))
    {
      return NULL;
    }
    if (haystack[i] == needle[0])
    {
      // vérifie si le ,eedle est présent ou non dans le haystack
      for (size_t i_motif = 0; i_motif < needle_l; ++i_motif)
      {
        if (needle[i_motif] == haystack[i + i_motif])
        {
          if (needle[i_motif + 1] == '\0')
          {
            return (haystack + i);
          }
        }
      }
    }
  }
  return NULL;
}

const char *str_search_first_char(char needle, const char *haystack)
{
  size_t haystack_l = str_length(haystack);
  // on recherche si la lettre est présente de haystack
  for (size_t i = 0; i < haystack_l; ++i)
  {
    if (needle == haystack[i])
    {
      return haystack + i;
    }
  }
  return NULL;
}

const char *str_search_last_char(char needle, const char *haystack)
{
  size_t haystack_l = str_length(haystack);

  int i_temp = -1;
  // on recherche si la dernière fois que la lettre est présente dans le haystack avec une variable temporaire
  for (size_t i = 0; i < haystack_l; ++i)
  {
    if (needle == haystack[i])
    {
      i_temp = i;
    }
  }
  if (i_temp != -1)
  {
    return haystack + i_temp;
  }
  return NULL;
}

size_t str_prefix_accept(const char *str, const char *chars)
{
  //on vérifie le cas où str est une chaine vide
  if (str[0] == '\0')
  {
    return 0;
  }

  size_t char_len = str_length(chars);
  size_t str_len = str_length(str);
  size_t res = 0;
  size_t j = 0;
  //on regarde si le premier caractère de str est situé à un endroit dans chars
  //           sinon on retourne 0
  for(size_t i = 0; i < str_len; ++i){
    while((j < char_len) && (res == i)){
      if(chars[j] == str[i]){
        ++res;
      }
      ++j;
    }
    j = 0;
    if(res == 0){
      return res;
    }
  }
  return res;
}

size_t str_prefix_reject(const char *str, const char *chars)
{
  //on vérifie le cas où str est une chaine vide
  if(str[0] == '\0'){
    return 0;
  }

  size_t char_len = str_length(chars);
  size_t str_len = str_length(str);
  size_t res = 0;
  size_t j = 0;

  for(size_t i = 0; i < str_len; ++i){
    while((j < char_len)){
      if(chars[j] == str[i]){
        return i;
      }
      ++j;
    }
    j = 0;
    ++res;
  }

  return res;
}

int str_to_integer(const char *str)
{
  size_t str_l = str_length(str);
  size_t nombre = 0;

  for (size_t i = 0; i < str_l; ++i)
  {
    if ((str[i] <= '9') && (str[i] >= '0'))
    {
      nombre = nombre * 10 + str[i] - '0';
    }
  }
  return nombre;
}

int str_to_integer_ex(const char *str, const char **endptr, int base)
{
  size_t str_len = str_length(str);
  int nombre = 0;
  
  for(size_t i = 0; i < str_len; ++i){
    if(base <= 10){
      if((str[i] <= '9')&&(str[i] >= '0')){
        if(base <= str[i] - '0'){
          return nombre;
        }
        nombre = nombre * base + str[i] - '0';
      }else if(endptr){
        *endptr = str + i;
        return nombre;
      }else{
        return nombre;
      }
    }else{
      if((str[i] <= '9')&&(str[i] >= '0')){
        nombre = nombre * base + str[i] - '0';
      }else if((str[i] >= 'a')&&(str[i]<= 'z')){
        nombre = nombre * base + str[i] - 'a' + 10;
      }else if((str[i] >= 'A')&&(str[i] <= 'Z')){
        nombre = nombre * base + str[i] - 'A' + 10;
      }else if(endptr){
        *endptr = str + i;
        return nombre;
      }else{
        return nombre;
      }
    }
  }
  if(endptr){
    *endptr = str + str_len;
  }
  return nombre;
}

void str_from_integer(char *dest, size_t size, int n)
{
  // on vérifie les cas où on peut mettre qu'un seul caractère
  if (size == 1)
  {
    dest[0] = '\0';
    dest[1] = 'X';
  }
  else if (n < 10)
  { // on vérifie le cas où n est un chiffre
    dest[0] = (char)n + '0';
    dest[1] = '\0';
    dest[2] = 'X';
  }
  else
  {
    // on initialise un tableau d'entier où l'on va insérer les chiffres de n un par un
    size_t dest_len = str_length(dest);
    int *tabInteger = malloc(dest_len * sizeof(int));

    size_t indice_int = 0;
    while (n > 0)
    {
      tabInteger[indice_int] = n % 10;
      n /= 10;
      ++indice_int;
    }

    // on modifie les premiers indice de dest en fonction de la taille de tabInteger ou de size
    if ((size - 2) >= (indice_int - 1))
    {
      for (int i = (indice_int - 1); i > -1; --i)
      {
        dest[(indice_int - 1) - i] = (char)(tabInteger[i]) + '0';
      }
      dest[indice_int] = '\0';
    }
    else
    {
      for (int i = (indice_int - 1); (indice_int - 1 - i) < (size - 1); --i)
      {
        dest[(indice_int - 1) - i] = (char)(tabInteger[i]) + '0';
      }
      dest[size - 1] = '\0';
    }
    free(tabInteger);
  }
}

void str_copy(char *dest, size_t size, const char *str)
{
  // on vérifie le cas où l'on peut mettre qu'un seul caractère
  if (size == 1)
  {
    dest[0] = '\0';
    dest[1] = 'X';
  }

  size_t str_len = str_length(str);
  // on compare la longueur de la chaine avec le nombre de caratère que l'on peut mettre
  // si le size est plus grand alors on va insérer les caractères en fonction de la longueur de la chaine
  // sinon en fonction du nombre de caractère que l'on peut insérer
  if (str_len < size)
  {
    for (size_t i = 0; i < str_len; ++i)
    {
      dest[i] = str[i];
    }
    dest[str_len] = '\0';
    dest[str_len + 1] = 'X';
  }
  else
  {
    for (size_t i = 0; i < size - 1; ++i)
    {
      dest[i] = str[i];
    }
    dest[size - 1] = '\0';
    dest[size] = 'X';
  }
}

char *str_duplicate(const char *str)
{
  // on vérifie le cas où str est null
  if (str == NULL)
  {
    return NULL;
  }
  int str_len = str_length(str);
  char *duplicate = malloc((str_len+1) * sizeof(char));
  // on vérifie le cas où str est chaine de caractère vide
  if (str[0] == '\0')
  {
    duplicate[0] = '\0';
    return duplicate;
  }
  for (int i = 0; i < str_len; ++i)
  {
    duplicate[i] = str[i];
  }
  duplicate[str_len] = '\0';
  return duplicate;
}

void str_concat_string(char *dest, size_t size, const char *str)
{
  size_t indiceNul = 0;
  // on récupère l'indice où est situé le caractère nul
  while (dest[indiceNul] != '\0')
  {
    ++indiceNul;
  }
  // si le size est plus grand que l'indice du caractère nul on effectue la concaténation jusqu'à la fin de chaine de str ou que l'indiceNul+1 soit supérieur ou égal à size
  if (size > indiceNul)
  {
    size_t i = 0;
    while ((str[i] != '\0') && (indiceNul + 1 < size))
    {
      dest[indiceNul] = str[i];
      ++indiceNul;
      ++i;
    }
    dest[indiceNul] = '\0';
  }
}

void str_concat_char(char *dest, size_t size, char c)
{
  size_t indiceNul = 0;
  while(dest[indiceNul] != '\0'){
    ++indiceNul;
  }

  if(indiceNul+1 < size){
    dest[indiceNul] = c;
    dest[indiceNul+1] = '\0';
  }
}

void str_concat_integer(char *dest, size_t size, int n)
{
  //on récupère l'indice du caractère nul
  size_t indiceNul = 0;
  while(dest[indiceNul] != '\0'){
    ++indiceNul;
  }

  if(size > indiceNul){
    //on vérifie le cas où n est un chiffre
    if((n < 10)&&(n >= 0)){
      dest[indiceNul] = (char)n + '0';
      dest[indiceNul+1] = '\0';
    }else{
      //on récupère les chiffres de n un par un en les plaçant dans un tableau
      size_t dest_len = str_length(dest) + str_length(dest+indiceNul+1) + 2;

      int *tabInteger = malloc(dest_len * sizeof(int));

      size_t indice_int = 0;
      while(n > 0){
        tabInteger[indice_int] = n%10;
        n /= 10;
        ++indice_int;
      }

      //on insère les éléments du tableau d'entier dans le dest
      for(size_t i = indice_int; i > 0; --i){
        if(indiceNul+1 >= size){
          i = -1;
        }else{
          dest[indiceNul] = (char)(tabInteger[i-1]) + '0';
          ++indiceNul;
        }
      }
      dest[indiceNul] = '\0';
      free(tabInteger);
    }
  }
}

void str_concat_array(char *dest, size_t size, const char *args[], char separator)
{
  size_t i = 0;
  while(args[i] != NULL){
    str_concat_char(dest, size, separator);
    str_concat_string(dest, size, args[i]);
    ++i;
  }
  
}

char *str_join_string(const char *str1, const char *str2, char separator)
{
  size_t str1_len = str_length(str1);
  size_t str2_len = str_length(str2);
  char *str3 = malloc((str1_len + str2_len + 2)* sizeof(char));
  str3[0] = '\0';
  str_concat_string(str3, (str1_len+str2_len+2),str1);
  str_concat_char(str3,(str1_len+2),separator);
  str_concat_string(str3,(str1_len+str2_len+2),str2);
  return str3;
}

char *str_join_array(const char *args[], char separator)
{
  size_t str_len = 0;
  size_t i = 0;
  //on récupère la taille que devra être la nouvelle chaine
  while(args[i] != NULL){
    str_len += str_length(args[i]);
    ++i;
  }

  //on initialise la chaine en allouant la place pour les caractère sépérateur et le caractère nul
  char *str = malloc((str_len + i + 1)* sizeof(char));
  str[0] = '\0';

  if(i == 0){
    return str;
  }else if(i == 1){
    str_concat_string(str,(str_len + i),args[i-1]);
    return str;
  }

  for(size_t j = 0; j < i; ++j){
    str_concat_string(str,(str_len+i+1),args[j]);
    str_concat_char(str,(str_len+i+1),separator);
  }
  str[str_len+i-1] = '\0';
  return str;
}
