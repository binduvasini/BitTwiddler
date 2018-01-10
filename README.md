$ nt 713
0000 0000 0000 0000 0000 0010 1100 1001 (base 2) 
0b00000000000000000000001011001001 (base 2) 
0x000002C9 (base 16)
713 (base 10 unsigned)
713 (base 10 signed)

Note that nt detects that 713 is a decimal number (more later). It then outputs the equivalent binary and the hexadecimal values. You need to output binary values in two forms: separate groups of 4 bits and a single number prefixed with 0b. The first format is easier to read, the second format is useful for cutting and pasting into a C program. The default size for binary and hexadecimal is 32 bits (4 bytes).

$ nt -713
1111 1111 1111 1111 1111 1101 0011 0111 (base 2) 
0b11111111111111111111110100110111 (base 2)
0xFFFFFD37 (base 16)
4294966583 (based 10 unsigned)
-713 (base 10 signed)

Note we get the binary and hexadecimal versions of the 2's complement representation of -713

$ nt 0b11100011
0000 0000 0000 0000 0000 0000 1110 0011 (base 2)
0b00000000000000000000000011100011 (base 2)
0x000000E3 (base 16)
227 (base 10 unsigned)  
227 (base 10 signed)  

In this case, nt recognized that 0b11100011 is a binary number and converted it to the equivalent unsigned base 10 equivalent of 227 and the base 10 signed equivalent of -29. It also displays the hexadecimal equivalent.

$ nt 0xE3
0000 0000 0000 0000 0000 0000 1110 0011 (base 2)  
0b0000000000000000000011100011 (base 2) 
0x000000E3 (base 16)
227 (base 10 unsigned) 
227 (base 10 signed)

In this case nt recognizes 0xE3 as a hexadecimal number and converts it to binary, decimal, and signed decimal.


Changing the Bit Width

The default bit width for nt is 32. You can change this default with the -b option:

$ nt -b 16 713
0000 0010 1100 1001 (base 2) 
0b0000001011001001 (base 2) 
0x02C9 (base 16)
713 (base 10 unsigned)
713 (based 10 signed)  

$ nt -b 16 -713
1111 1101 0011 0111 (base 2) 
0b111110100110111 (base 2)
0xFD37 (base 16)
64823 (base 10 unsigned)
-713 (base 10 signed)

$ nt -b 8 0xE0
1110 0000 (base 2)
0b11100000 (base 2)
0xE0 (base 16)
224 (base 10 unsigned)
-32 (base 10 signed)


Bit Twiddling

You can select the range of bits to use for conversion using the -r option:

$ nt -b 4 -r 4,7 0b000010100000
1010 (base 2)
0b1010 (base 2)
0xA (base 16)
10 (base 10 unsigned)
-6 (base 10 signed)
