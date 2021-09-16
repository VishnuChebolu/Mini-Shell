#!/usr/bin/python3
from termcolor import colored,cprint
import pyfiglet
result=pyfiglet.figlet_format("Loading ..")
cprint(result,'green',attrs=['blink'])
