#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (argc < 2 || argc > 3)
  {
    printf("Usage: ./a.out row columns\n");
  }
  else
  {
    int rows = atoi(argv[1]);
    int columns = atoi(argv[2]);

    int counter = 0;
    for (int i = 1; i <= rows; i++)
    {
      for (int j = 1; j <= i*columns; j++)
      {
        printf("*");
        counter++;
      }
      printf("\n");
    }
    printf("TOtalt: %d\n", counter);
    return 0;
  }
}

#include <stdio.h>  // Include standard input-output library
#include <stdlib.h> // Include standard library for functions like atoi

int main(int argc, char *argv[]) {
    // Check if the number of command-line arguments is less than 2 or more than 3
    if (argc < 2 || argc > 3) {
        // Print usage message if the number of arguments is incorrect
        printf("Usage: ./a.out row columns\n");
    } else {
        // Convert the first command-line argument to an integer (number of rows)
        int rows = atoi(argv[1]);
        // Convert the second command-line argument to an integer (number of columns)
        int columns = atoi(argv[2]);

        int counter = 0; // Initialize a counter to keep track of the number of stars printed

        // Loop through each row
        for (int i = 1; i <= rows; i++) {
            // Loop through each column in the current row
            for (int j = 1; j <= i * columns; j++) {
                // Print a star
                printf("*");
                // Increment the counter
                counter++;
            }
            // Print a newline character after each row
            printf("\n");
        }
        // Print the total number of stars printed
        printf("Total: %d\n", counter);
        return 0; // Return 0 to indicate successful execution
    }
}