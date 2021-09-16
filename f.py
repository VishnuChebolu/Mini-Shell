#!/usr/bin/python3
from termcolor import colored,cprint
import pyfiglet
result=pyfiglet.figlet_format("Shell v1.0")
cprint(result,'green',attrs=['blink'])
