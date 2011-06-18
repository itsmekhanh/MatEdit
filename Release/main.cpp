#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

DIR *dir;
struct dirent *ent;

int main(){


dir = opendir("textures");

if(dir != NULL){
  while (( ent = readdir (dir)) != NULL){
    printf("%s\n", ent->d_name);
  }
  closedir (dir);

	} 
else{
  perror("");
  return EXIT_FAILURE;
	}

return 0;
}
