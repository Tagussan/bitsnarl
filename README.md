# bitsnarl: A light and fast data scrambler for zero-redundant bit error detection

This library performs reversible data scrambling such that a bit error in any location affects the whole bytes. Because even a tiny bit error turns the entire data into a completely different one, **error detection can be performed without excess bits**, thanks to the potential constraints of the data.



## Principle: we put very strong constraints on data

We have ASCII codes to represent strings. The number of ASCII codes that correspond to actual characters is 99 (33 to 126 for characters, and Space, CR, LF, Tab, NUL), and usually one byte is allocated for each character. 

Essentially, one byte can represent 256 different numbers, so less than half of the numbers are effectively used. In more detail, there is a **99/256 = 39%** probability that a random 1-byte number is an actual character. 

A 10-character string is represented by 10 bytes, but when 10 bytes of data are randomly chosen, the probability that it is a string is only **0.39^10=0.08%**. So, we are using very little of the amount of information that a byte sequence has when representing a string of characters.

String is just one example; the JSON format imposes stronger constraints. Binary data is also constrained by its format.

## Scrambling and error detection using constraints

