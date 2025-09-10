"""
@author June
@time 2025/9/9
@description:
ord('a') 字符转ASKII
chr(97)  ASKII转字符
"""
import re
import sys

def letters_to_num(s):
    num = 0
    for c in s:
        num = num * 26 + (ord(c.upper()) - ord('A') + 1)
    return num

def num_to_letters(n):
    letters = ''
    while n > 0:
        n -= 1
        letters = chr(n % 26 + ord('A')) + letters
        n = n // 26
    return letters

def main():
    pattern_b = re.compile(r'^R(\d+)C(\d+)$')
    pattern_a = re.compile(r'^([A-Za-z]+)(\d+)$')
    n = int(sys.stdin.readline())
    for _ in range(n):
        line = sys.stdin.readline().strip()
        match_b = pattern_b.match(line)
        if match_b:
            row_str = match_b.group(1)
            col_num = int(match_b.group(2))
            letters = num_to_letters(col_num)
            row_int = int(row_str)
            print(f"{letters}{row_int}")
        else:
            match_a = pattern_a.match(line)
            if not match_a:
                continue
            letters_part = match_a.group(1)
            row_str = match_a.group(2)
            col_num = letters_to_num(letters_part)
            row_int = int(row_str)
            print(f"R{row_int}C{col_num}")

if __name__ == '__main__':
    main()