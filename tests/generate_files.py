#!/bin/python3

# Source - https://stackoverflow.com/a
# Posted by Jacob Wan, modified by community. See post 'Timeline' for change history
# Retrieved 2025-12-17, License - CC BY-SA 3.0

import random

def get_random_unicode(length):
    try:
        get_char = unichr
    except NameError:
        get_char = chr

    # Update this to include code point ranges to be sampled
    include_ranges = [
        ( 0x0021, 0x0021 ),
        ( 0x0023, 0x0026 ),
        ( 0x0028, 0x007E ),
        ( 0x00A1, 0x00AC ),
        ( 0x00AE, 0x00FF ),
        ( 0x0100, 0x017F ),
        ( 0x0180, 0x024F ),
        ( 0x2C60, 0x2C7F ),
        ( 0x16A0, 0x16F0 ),
        ( 0x0370, 0x0377 ),
        ( 0x037A, 0x037E ),
        ( 0x0384, 0x038A ),
        ( 0x038C, 0x038C ),
    ]

    alphabet = [
        get_char(code_point) for current_range in include_ranges
            for code_point in range(current_range[0], current_range[1] + 1)
    ]
    return ''.join(random.choice(alphabet) for i in range(length))

def main():
    with open("./output/utf-8_test.txt", 'w') as file:
        line_count = random.randrange(1, 1024)
        content = ""
        for x in range(1, line_count):
            content = get_random_unicode(random.randrange(1, 1024))
        file.write(content) 

if __name__ == "__main__":
    main()
