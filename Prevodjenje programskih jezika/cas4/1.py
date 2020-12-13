#! /usr/bin/env python

import sys
import re

def do_my_regex():
    return re.compile(r'{(.*?),[.]NE\+(.*?):\d+[a-zA-Z]+}', re.DOTALL)

def main():

    if len(sys.argv) != 2:
        sys.exit("bar arg count")

    try:
        with open(sys.argv[1], "r") as f:
            data = f.read()
    
    except IOError as e:
        print(e.message)
        sys.exit("open failure")

    our_regex = do_my_regex()

    new_data = re.sub(our_regex, r'<\2>\1</\2>', data)

    new_file_name = sys.argv[1].split('.')[-1] + ".xml"

    try:
        with open(new_file_name, "w") as f:
            f.write("<xml>\n")
            f.write(new_data)
            f.write("</xml>")
    except IOError as e:
        print(e.message)
        sys.exit("write failure")
        
if __name__ == "__main__":
    main()