#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("DEBUG: isatty(0) = %d\n", isatty(0));
    
    // Check if we're receiving any input
    char buffer[100];
    int bytes_read = read(0, buffer, sizeof(buffer)-1);
    printf("DEBUG: bytes_read = %d\n", bytes_read);
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("DEBUG: Received: %s\n", buffer);
    }
    
    system("find . -maxdepth 1 -name '*.c' | wc -l");
    return 0;
}