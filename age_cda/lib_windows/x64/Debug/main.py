import ctypes
import os

file_path = os.path.join( os.path.dirname(os.path.abspath(__file__)), 'lib_windows.dll' )
# Load the library
mylib = ctypes.cdll.LoadLibrary(file_path)

# Declare the function prototype
mylib.sum.restype = ctypes.c_int
mylib.sum.argtypes = [ctypes.c_int, ctypes.c_int]

# Call the function
result = mylib.sum(5, 2)
print(result)  # Output: 3
