#!/usr/bin/env python3
# 
# Notes: 
#    (must be run from scripts folder for this to work)
#

import os
import subprocess
# TODO: python check validation
# import CheckPython

# change to root directory
os.chdir('../')

print("Running premake...")

if (os.name == 'posix'):
    # dumps makefiles to root project directory
    subprocess.call(['3rdparty/external/premake/unix/premake5', 'gmake2'])

elif(os.name == 'nt'):
    # dumps msvc 2019 solution to root project directory
    subprocess.call(['3rdparty/external/premake/windows/premake5.exe', 'vs2022'])

else:
    print("Sorry, but your OS is not supported at this time...")
