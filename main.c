#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void debug_str(char * str, int size) {
    printf("STR DEBUG: ");
    for (int i = 0; i < size; i++) printf("%d ", str[i]);
    printf("\n");
}

char * read_file(char * path) {
    int read_count = 0;
    char * read = NULL;
    char * buffer = malloc(sizeof(char) * 100);

    FILE * file_stream = fopen(path, "r");

    if(file_stream == NULL) {
        free(buffer);
        return NULL;
    }

    while(fgets(buffer, 100, file_stream) != NULL) {
        int recently_read = strlen(buffer);

        if (recently_read == 0) continue;

        char * new = malloc(sizeof(char) * (read_count + recently_read + 1));

        strncpy(new, read, read_count);
        
        free(read);

        read = new;
        
        strncpy(read + read_count, buffer, recently_read);

        read[read_count + recently_read] = '\0';

        read_count += recently_read;
    }

    fclose(file_stream);
    free(buffer);

    return read;
}

int main(int argc, char ** argv) {
    char * ptr = read_file("./template.txt");

    if(ptr == NULL) printf("You're trying to use a not defined template, man!\n");

    if(argc < 2) {
        printf("Please provide an argument!\n");
        free(ptr);
        return 0;
    }
    
    printf(ptr); 
    free(ptr);
    return 0;
}
