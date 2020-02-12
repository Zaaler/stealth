#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void *bitcpy (void *dest, const void *src, unsigned int bits);

void printBinary(const void *stuff);

int main()
{
    printf("Stealth Assignment\n"); 
	printf("OS is %i bits\n\n", sizeof(void *) * 8);
	printf("----------------------------------------------\n");

    // Example: 100 = 110100
	int size = 100;
	int byte_len = 20;
	char mem_src[] = "Memcpy test string";
	char mem_dest[size];
	mem_dest[0] = '\0';

	// Memcpy Example
	printf("MEMCOPY EXAMPLE\n");
	printf("Source: %s\n", mem_src);
	printf("Bytes to take: %i\n", byte_len);
	memcpy(mem_dest, mem_src, byte_len);
	mem_dest[byte_len + 1] = '\0'; 
	printf("Final Destination: %s\n\n", mem_dest);
	printf("----------------------------------------------\n");

	// Bitcpy Example
	printf("BITCOPY EXAMPLE\n");
	
	// Number of Bits to copy
	int bit_len = 100;
	
	// String to copy bits from
	char bit_src[] = "Bitcpy test string";
	
	// Initialize copy location
	char bit_dest[sizeof(bit_src)*8];
	bit_dest[0] = '\0';

	// Summary
	printf("Source: %s\n", bit_src);
	printf("Bits to take: %i\n", bit_len);
	
	// Call to bitcpy
	bitcpy(bit_dest, bit_src, bit_len);
	bit_dest[(int) ceil(bit_len/8) + 1] = '\0';
	printf("Copy:   %s\n", bit_dest);

	// Binary summary
	printf("BINARY SOURCE: \n");
	printBinary(bit_src);
	printf("BINARY COPY:   \n");
	printBinary(bit_dest);
	printf("\n");

	printf("This solution pads the remaining bits of the final byte with zeros\n");
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
	
	// Tricky Case: Less than 8 remaining
	// 4 remaining: 00001111
	// Assume all : 11111111
	// all - 4 = 11110000	
	int bit_count = bits;
	
	// Account for bit copies greater than one char 
	unsigned int temp = 0;
	unsigned int mask = 0;
	unsigned int char_count = 0;
	while(bit_count > 0)
	{
		//printf("BITS LEFT = %i", bit_count);
		// Determine the mask for this byte
		if(bit_count >= 8)
		{
			mask = pow(2, 8) - 1;
			//printf("BIT MASK: %i\n", mask);
		}
		else
		{
			mask = 255 - (pow(2, 8-bit_count) - 1);
			//printf("BIT MASK: %i\n", mask);
		}
		
		// Mask the character 
		temp = s[char_count] & mask;
		
		// Add the byte to the current accumulator
		d[char_count] = temp;
		
		// Account for the processed bits
		bit_count = bit_count - 8;
		char_count++;
	}
	
	// Fill the remaining destination with zeros
	while(char_count < sizeof(s))
	{
		// Add the byte to the current accumulator
		temp = 0;
		d[char_count] = temp;
		char_count++;
	}
	return dest;	
}

void printBinary(const void *stuff)
{
	char *s = stuff;
	char check_size = s[0];
	unsigned int size = 1;

	// Determine length of the character buffer
	while(check_size != '\0')
	{
		size++;
		check_size = s[size];
	}
	
	// Remove extra character from the \0
	size--;

	// Print the binary from the memory
	//printf("String length = %i\n", size);
	unsigned int val = 0;
	for(int i = 0; i < size; i++)
	{
		for(int j = 7; j >= 0; j--)
		{
			printf("%i", (s[i] >> j) & 1);
		}
	}
	printf("\n");
}
