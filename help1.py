#!/usr/bin/python3
from termcolor import colored,cprint
import pyfiglet
result=pyfiglet.figlet_format("Commands : )")
cprint(result,'red',attrs=['blink'])
