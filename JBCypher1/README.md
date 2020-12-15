# An experimental block encryption utility

OK, this was basically just something I made to see if I could make my own 
block cipher.  Its not vetted in any way, and may very well be a naive and 
not very good system.

Anyway, It does have a few things going for it:

* It has a large block size (encrypts in 2048 bit blocks)
* Key of practically any size (internal entropy maxes out to 1748 bit worth)
* If two identical blocks occur, they will produce different ciphertext
* It is designed for to use a modular RNG (currently with a modified ARC4 rng inserted)

What it does to each block (algorithm);

1. First, it shuffle bytes within the block (perhap superflous)
2. Next, it shuffles bits between bytes (each bit sent to a random byte)
3. Then, it rotates the bits in each byte
4. The xors each byte with a random byte (much like a stream cipher)
5. And finally, xors each byte with another, randomly seleced byte in the block

And there you go!

The program is just a small commandline utility -- I don't really have any need 
for this and understand the value of vetted cryptography software.  All I wanted 
was a proof of concept; here it is and it works.

I suppose it could be used to encrypt personal files.

---

This program is the property and copyright of Jared Blackburn (c) 2018, all 
rights reserved. It is not licensed for anyones use due to concerns of legality for export 
and possible malicious use.  Any use of this code or a dirivative thereof 
is a violation of the intelectual property rights of the author and owner,
Jared Blackburn.
