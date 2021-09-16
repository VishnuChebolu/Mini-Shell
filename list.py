#!/usr/bin/python3
from termcolor import colored,cprint
import pyfiglet
result=pyfiglet.figlet_format("Listing files..")
cprint(result,'green',attrs=['blink'])
