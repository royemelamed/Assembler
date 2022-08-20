#define BINARY_DIGITS_PER_32CHAR 5
#define MAX_32_NUMBER_LEN 2 /*we won't have any 32-base number with more than 2 chars*/

/*Recived BINARY_DIGITS_PER_32CHAR digit binary code number and return the number in base 32*/
char getBaseCharBy5Binary(char binary[BINARY_DIGITS_PER_32CHAR]);

/*Recived 10 digit binary code and saves in finalCode the number in  base 32*/
void getBaseCharsBy10Binary(char *binary, char finalCode[MAX_32_NUMBER_LEN]);

/*Recived a decimal id (lower then 32), and return the number in base 32*/
char getBaseCharsById(int id);

/*Recived a decimal number and saves in finalCode the number in  base 32*/
void getBaseCharsByDecimal(int decimal, char *finalCode);
