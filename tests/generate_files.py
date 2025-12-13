#!/bin/python3

import random

for num in range(1,2):
    with open("./tests/output/test" + str(num) + ".txt", 'w') as file:
        content = ""
        char_count = random.randrange(0, 4096)
        for x in range(1, char_count):
            content += chr(random.randrange(1,127))
        file.write(content) 
