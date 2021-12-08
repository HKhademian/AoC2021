#!/usr/bin/env python3

bitCount = lambda x: sum(1 for i in range(8) if (x&(1<<i)!=0))

DIGITS = [
  0b01011111, 0b00100100, 0b01011101, 0b01101101, 0b00101110,
  0b01101011, 0b01111011, 0b00100101, 0b01111111, 0b01101111,
]

COUNTS = list(bitCount(DIGITS[i]) for i in range(10))

PROBS = list(
  list(i for i in range(10) if bitCount(DIGITS[i])==c)
  for c in range(8)
) 

print(DIGITS)
print(COUNTS)
print(PROBS)
