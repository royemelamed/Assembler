#define MAX_LINE_CHARS 80

typedef enum
{
	VALID=100,
	FILE_NOT_FOUND, /*code is 101*/
	NO_ASSEMBLER_POSTFIX, /*code is 102*/
	UNKNOWN_COMMAND, /*code is 103*/
	INVALID_PARAMS, /*code is 104*/
	MISSING_PARAM, /*code is 105*/
	EXTRA_TEXT, /*code is 106*/
	PATH_NOT_FOUND, /*code is 107*/
	PATH_FOR_MACRO_NOT_FOUND, /*code is 108*/
	INVALID_MACRO_NAME, /*code is 109*/
	DOUBLE_MACRO_DECLERATION, /*code is 110*/
	MISSING_LADDER, /*code is 111*/
	OPERAND_NOT_NUMBER, /*code is 112*/
	SYMBOL_ALREADY_DECLARED, /*code is 113*/
	DOUBLE_LABEL_DECLERATION, /*code is 114*/
	LABEL_NOT_FOUND, /*code is 115*/
	INVALID_LABEL_NAME, /*code is 116*/
	INVALID_SYMBOL_NAME, /*code is 117*/
	LABEL_NOT_VALID_ON_SENTENCE, /*code is 118*/
	WRONG_STRUCT_FIELD, /*code is 119*/
	WRONG_USE_OF_REGISTER_NAME, /*code is 120*/
	WRONG_ADDRESSING_METHOD, /*code is 121*/
	STRING_WITHOUT_APOSTROPH, /*code is 122*/
	BAD_OPERAND_DECLERATION, /*code is 123*/
	ALLOCATION_FAILED, /*code is 124*/
	UNKNOWN_ERROR /*code is 125*/
} validation_code;

/*Print the correct error text, based on the validation code*/
void print_code(validation_code code);


/*Print the correct error text with the error line, based on the validation code*/
void print_code_with_line(int line, validation_code code);

/*Use to update the path for errors prints*/
void updateProcessedFile(char *path);
