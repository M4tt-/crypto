/****************************************************************************
 *                                                                          *
 * Filename: crutil.h                                                       *
 *																			*
 * Author: Matt Runyon							   						    *					
 *                                                                          *
 * Purpose : Header for crypto library			  		                    *
 *                                                                          *
 * Last Upated : 02-14-17   							 				    *
 *																		    *
 ****************************************************************************/

/*********************************************************************
*	BASE CONVERSIONS: Binary, Hex, Base64, ASCII(printable only)	 *
**********************************************************************/
extern char* hex2bin(char); // Convert hex char to binary string.
extern char* hexStr2bin(char*); // Convert hex string to binary string. Returns a pointer that must be freed.
extern char bin2hexChar(char*); // Convert binary string to hex char.
extern char* bin2hexStr(char*); // Convert binary string to hex string. Returns a pointer that must be freed.
extern int string_compare(char*, char*); // See if two strings are identical in contents.
extern char bin2b64Char(char*); // Convert binary string to base64 char.
extern char* bin2b64Str(char*); // Convert binary string to base64 string. Returns a pointer that must be freed.
extern char* b64Char2bin(char); // Convert base64 char to 6-bit binary.
extern char* b642bin(char*); // Converts base64 text into binary. Returns a pointer that must be freed.
extern char* dec2bin(int, int); // Convert decimal number (arg1) into n-bit (arg2) binary . Returns a pointer that must be freed.
extern char bin2prasciiChar(char*); // Converts an 8-bit binary string to corresponding 'printable' ASCII char.
extern char* bin2prasciiStr(char*);// Converts a binary string to corresponding 'printable' ASCII string. Returns a pointer that must be freed.
extern char* prasciiChar2bin(char); // Converts a 'printable' ASCII char to corresponding 8-bit binary string. Returns a pointer that must be freed.
extern char* prasciiStr2bin(char*); // Converts a 'printable' ASCII string to corresponding 8-bit binary string. Returns a pointer that must be freed.
extern char hex2prasciiChar(char*); // Converts hex byte to 'printable' ASCII char.
extern char* hex2prasciiStr(char*); // Converts hex string into 'printable' ASCII string. Returns a pointer that must be freed.
extern char* prasciiChar2hex(char); // Converts 'printable' ASCII char to hex byte. Returns a pointer that must be freed.
extern char* prasciiStr2hex(char*); // Converts 'printable' ASCII string to hex string. Returns a pointer that must be freed.

/*********************************************************************
*					LOGICAL OPERATIONS ON CHARS/STRINGS				 *
**********************************************************************/
extern char charand(char,char); // Perform 1-bit AND, bit casted as char
extern char* strand(char*,char*); // Perform N-bit AND, bitstreams casted as char. Returns a pointer that must be freed.
extern char charxor(char,char); // Perform 1-bit XOR, bits casted as char.
extern char* strxor(char*, char*); //Perform XOR on two char* casted bit streams of equal length. Returns a pointer that must be freed.
extern char* hexxor(char*, char*); // Perform XOR on two hex strings. Returns a pointer that must be freed.

/*********************************************************************
*					GENERAL UTILITIES								 *
**********************************************************************/
extern char** transposeCharArray(char**, int, int); // Transpose 2D array (arg1) with a finite number of rows (arg2) of finite length (arg3)
extern char* cat2dCharMat(char**, int, int); // Concatenates a 2D char matrix (arg1) with a specified number of rows (arg2) into a single string. Returns a pointer that must be freed.
extern void printNbitBin(int); // Prints a declarable char** of binary numbers 0-n.
extern char** textFile2Array(char*); // Reads a text file into a 2D char array. Max lines: 512, Max line length: 64 (nominal).Returns a pointer that must be freed.
extern char* textFile2String(char*); // Reads a text file, line by line, into a single string. Returns a pointer that must be freed.
extern int findMaxElement(double*,int); // Returns the index of the largest element in a numeric array (arg1) of size N (arg2).
extern int findMinElement(double*, int); // Returns the index of the smallest element in a numeric array (arg1) of size N (arg2).

/*********************************************************************
*					CRYPTOGRAPHIC UTILITIES							 *
**********************************************************************/
extern double scorePlaintext(char*); // Scores plaintext based on common letter frequency.
extern double scorePlaintext_chiSquare(char*); // Scores plaintext based on letter frequency and minimizing a chi squared test statistic
extern int getHammingDistance(char*, char*); // Returns the number of differing bits between two strings of equal length.
extern int gcd(int,int); // Returns the greatest common divisor of two integers via Euclid's algorithm
extern int multiple_gcd(int,int*); // Returns the greatest common divisor of two integers via Euclid's algorithm
extern int totient(int); // Returns the number of elements in the reduced set of residues of an int. This is Euler's totient function.
extern int modexp(int, int, int); // Performs addition chaining to exponentiate a number(arg1) modulo n (arg3)
extern int chinese_remainder(size_t, int*, int*); //Returns n such that n == u[k]%m[k]and n < m[0]*m[1]*...*m[r-1]. are1 is numel in arrays arg2 (pairwise rprime moduli) and arg3(coeff array)

/*********************************************************************
*					XOR-CIPHER STUFF								 *
**********************************************************************/
extern char* xorcyph_getSingleByteHexKey(char*); // Returns a single byte hex key for xor encrypted hex string.
extern char* xorcyph_encryptHexKey(char*, char*); // Uses a desired hex string (arg2) for N-byte repeated XOR encryption of some text (arg1).Returns a pointer that must be freed.
extern char* xorcyph_decryptHex(char*, char*); // Decrypts hex string (arg1) with a single byte hex key (arg2). Returns a pointer that must be freed.
extern char* xorcyph_encryptPlainKey(char*, char*); // Uses a desired plaintext string (arg2) for N-byte repeated XOR encryption of some text (arg1).Returns a pointer that must be freed.
extern char* xorcyph_getSingleByteBinKey(char*); // Returns a single byte hex key for xor encrypted hex string.
extern char* xorcyph_encryptBinKey(char*, char*); // Encrypts plaintext (arg1) with a single byte binary key (arg2). Returns a pointer that must be freed.
extern char* xorcyph_decryptBin(char*, char*); // Decrypts binary string (arg1) with a single byte binary key (arg2). Returns a pointer that must be freed.
extern int* xorcyph_findLeastNormalizedHammingBytes(char*, int); // Returns N (arg2) bytes of least normalized Hamming distance of a binary string (arg1). Returns a pointer that must be freed.
extern char* xorcyph_decryptNbyteRepKey(char*, int);// Returns the key to an N-byte XOR Repeated key (Vigenere) encrypted base64 string binary only.
extern int xorcyph_findEncryptedHexLine(char**, int); // Returns the index of a XOR encoded string within a set of N lines. The set is arg1, number of lines is arg2.
extern char* aes_128_ecb(char*, char*); // Decrypts a binary string (arg1) with the 128-bit binary key (arg2). Returns a pointer tht needs to be freed.
