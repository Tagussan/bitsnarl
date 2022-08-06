# bitsnarl: A light and fast data scrambler for zero-redundant bit error detection

This library performs reversible data scrambling such that a bit error in any location affects the whole bytes. Because even a tiny bit error turns the entire data into completely different one, error detection can be performed without excess bits using the potential constraints of the data.



## Principle: we put a strong constraint on data

We have ASCII codes to represent strings. The number of ASCII codes that correspond to actual characters is 99 (33 to 126 for characters, 32 for spaces, 13 for CR, 10 for LF, 9 for Tab, and 0 for NUL), including spaces and terminating characters, and usually one byte is allocated for each character. Essentially, one byte can represent 256 different numbers, so less than half of the numbers are effectively used. In more detail, there is a 39% probability that a random 1-byte number is an actual character. A 10-character string is represented by 10 bytes, but when 10 bytes of data are randomly chosen, the probability that it is a string is only 0.08%. So, we are using very little of the amount of information that a byte sequence has when representing a string of characters.