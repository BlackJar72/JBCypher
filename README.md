# JBCypher1 and JBCypher2 

A pair of unvetted block cyphers I created just to see if I could 
design and code my own original cryptography -- not recommended for
any serious use.  Probably the best idea in them is under-untilized 
in favor of inferior procedures.

1. First, it shuffle bytes within the block (perhap superflous)
2. Next, it shuffles bits between bytes (each bit sent to a random byte)
3. Then, it rotates the bits in each byte
4. The xors each byte with a random byte (much like a stream cipher)
5. And finally, xors each byte with another, randomly seleced byte in the block

These cyphers will got through a series of manipulations, including 
shuffling bytes, shuffling bits between bytes, rotating bits within 
byte, xoring bytes with random numbers, and xoring bytes with other 
randomly selected bytes in the same block.  Blocks used are 2048 bit, 
based handled as 256 bytes.  A modified ARC4 PRNG is used to select 
bytes, determine rotation amount, and as random numbers.

The modified ARC4 generator differs from a standard implementation in 
that instead of proceeding through its shuffled bytes in order it 
jumps between them using a form of enhanced xorshift as a secondary 
generator to determine which byte is used next.  The combinations 
of the two generators allows 1748 bit of entropy. Keys may be of 
any length.

In retrospect, step (1) should not have been used, as it is superflous 
with step (2); step (5) should have been repeated more, perhap using 
sixteen rather than twelve numbers per encrypted byte to allow six 
passes rather than one of step (5).

The difference between the two generators is in how they handle the ends 
of files and blocks.  The first takes note of the bytes in the last 
block and stores it as the first byte of the encrypted file.  The 
second technically only encryptes 2040 bits of data per block, using 
the 256th byte to record the number of bits in the byte; this is to 
allow streaming of data rather than being limited to use on local files 
of pre-known size.

JUST TO BE SURE IT'S UNDERSTOOD: I AM NOT A CRYPTOGRAPHER, AND DID THIS 
TO SEE IF I COULD AFTER TAKING BASIC CLASS IN SECURITY FOR SECURITY+ 
CERTIFICATION. THIS HAS NOT BEEN VETTED. I WOULDN'T HAVE A CLUE HOW TO 
CRACK IT BUT AN EXPERT MIGHT.  THIS SHOULD NOT BE USED FOR REAL-WORLD 
SECURITY PURPOSES OR ANYTHING PARTICULARLY IMPORTANT.  IT IS AN AMATURE 
PROJECT BY A NOVICE EXPERIMENTING TO SEE IF HE COULD MAKE A CYPHER, 
NOTHING MORE!

This software is under the MIT License:

Copyright 2018 Jared Blackburn

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
