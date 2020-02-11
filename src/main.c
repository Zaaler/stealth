#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void *bitcpy (void *dest, const void *src, unsigned int bits);

int main()
{
    printf("Stealth Assignment\n");
    
    // Example: 100 = 110100
    int size = 20;
	int byte_len = 9;
	char mem_src[] = "Memcpy test string";
	char mem_dest[size];
	mem_dest[0] = '\0';

	// Memcpy Example
	printf("Source: %s\n", mem_src);
	printf("Initial Destination: %s\n", mem_dest);
	memcpy(mem_dest, mem_src, 9);
	mem_dest[byte_len + 1] = '\0'; 
	printf("Final Destination: %s\n", mem_dest);

	// Bitcpy Example
	int bit_len = 48;
	char bit_src[] = "Bitcpy test string";
	char bit_dest[size];
	bit_dest[0] = '\0';
	printf("Source: %s\n", bit_src);
	printf("Initial Destination: %s\n", bit_dest);
	bitcpy(bit_dest, bit_src, sizeof(bit_src)*8);
	bit_dest[bit_len+1] = '\0';
	printf("Final Destination: %s\n", bit_dest);

    return 0;
}

// Original memcpy function
void *memcpy (void *dest, const void *src, size_t len)
{
	char *d = dest;
	const char *s = src;
	while (len--)
		*d++ = *s++;
	return dest;
}

// Bitcpy function
void *bitcpy (void *dest, const void *src, unsigned int bits)
{
	// Local copies
	char *d = dest;
	const char *s = src;
	
	// Construct bit-mask
	// 0: 0    = 0  = 2^0 - 1
	// 1: 1    = 1  = 2^1 - 1
	// 2: 11   = 3  = 2^2 - 1
	// 3: 111  = 7  = 2^3 - 1
	// 4: 1111 = 15 = 2^4 - 1
	int bit_count = bits;
	unsigned int temp = 0;
	unsigned int acc = 0;
	unsigned int mask = 0;
	for(int i = 0; i < sizeof(s); i++)
	{
		// Determine the mask for this byte
		if(bit_count > 8)
		{
			mask = pow(2, 8) - 1;
		}
		else
		{
			mask = pow(2, bit_count) - 1;
		}
		
		// Mask the character 
		temp = s[i] & mask;

		// Shift the accumulator if past the first byte
		if(bit_count > 8 && i > 0)
		{
			acc = acc << 8;
		}
		else if(bit_count < 8 && i > 0)
		{
			acc = acc << bit_count;
		}

		// Add the byte to the current accumulator
		acc = acc | temp;
		printf("%i\n", temp);

		// Account for the processed bits
		bit_count = bit_count - 8;
	}
	
	printf("%i\n", acc);

	d = *s & mask;
	
return dest;	
}

/*void printBinary(const void *stuff)
{
	unsigned int val = 0;
	for(int i = 0; i < sizeof(stuff); i++)
	{
		for(int j = 7; j <= 0; j--)
		{
*/			

