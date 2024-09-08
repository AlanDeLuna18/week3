#include <stdlib.h>
#include <string.h>

unsigned int num_bytes(char b) {
  if((b & 0b10000000) == 0) { return 1; }
  else if((b & 0b11100000) == 0b11000000) { return 2; }
  else if((b & 0b11110000) == 0b11100000) { return 3; }
  else if((b & 0b11111000) == 0b11110000) { return 4; }
  else { return -1; }
}
unsigned int utf8_strlen(char* unicode) {
  unsigned int len = strlen(unicode); // count of bytes in this string
  unsigned int bytes_seen = 0;
  unsigned int unicode_characters_seen = 0;
  while(bytes_seen < len) {
    unsigned int bytes_this_char = num_bytes(unicode[bytes_seen]);
    bytes_seen += bytes_this_char;
    unicode_characters_seen += 1;
  }
  return unicode_characters_seen;
}
unsigned int bytes_for(char* unicode, unsigned int n) {
  unsigned int unicode_characters_seen = 0;
  unsigned int bytes_seen = 0;
  unsigned int total_chars = utf8_strlen(unicode);
  if(total_chars < n) { return -1; }
  if(n < 0) { return -1; }
  while(unicode_characters_seen < n) {
    unsigned int bytes_this_char = num_bytes(unicode[bytes_seen]);
    bytes_seen += bytes_this_char;
    unicode_characters_seen += 1;
  }
  return bytes_seen;
}

/*
  char long_str[] = "José Ülo 成龙";
  utf8_substring(long_str, 0, 4) -> José
  utf8_substring(long_str, 5, 8) -> Ülo
  utf8_substring(long_str, 9, 11) -> 成龙
*/
char* utf8_substring(char* utf8str, unsigned int start, unsigned int end) {
  // Should check start <= end, check that end <= utf8_strlen(utf8str), and so on
  unsigned int start_bytes = bytes_for(utf8str, start);
  char* start_char = utf8str + start_bytes;
  unsigned int size = end - start;
  unsigned int bytes_to_copy = bytes_for(start_char, size);

  // Make a new string! Use malloc
  // +1 is because all of our char* c strings end in \0
  char* to_return = malloc(bytes_to_copy + 1);

  for(int i = 0; i < bytes_to_copy; i += 1) {
    to_return[i] = start_char[i];
  }
  to_return[bytes_to_copy] = '\0';
  return to_return;
}














// Find the index (in terms of utf8 characters) where utf8_str_to_find appears
// in utf8str_to_search, or -1 if it does not appear
int utf8_find(char* utf8str_to_search, char* utf8str_to_find) 
{
  unsigned int stringLength = utf8_strlen(utf8str_to_search);

  for(int a = 0; a < stringLength; a++)
  {
    if(utf8str_to_search[a] == *utf8str_to_find)
    {
      return a; 
    }
  } 

  return -1;
}

// Return a reversed version of the utf8str.
// utf8_reverse("Ülo") -> "olÜ"
char* utf8_reverse(char* utf8str) 
{
  unsigned int stringLength = utf8_strlen(utf8str); 
  char* finalString = malloc(stringLength + 1);

  for(int forward = 0, backward = stringLength - 1; forward < stringLength; forward++, backward--)
  {
    finalString[forward] = utf8str[backward];  
  }

  finalString[stringLength] = '\0';  
  return finalString; 






}

