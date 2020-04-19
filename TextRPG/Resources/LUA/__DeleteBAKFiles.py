import os

files = [file for _, _, file in os.walk('.')][0]

for file in files:
    extension = os.path.splitext(file)
    if (extension[1] == '.bak'):
        print(f"Removing {file}")
        os.remove(file)
