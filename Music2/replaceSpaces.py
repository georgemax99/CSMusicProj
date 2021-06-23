import os
path  = os.getcwd() + "/Songs"
filenames = os.listdir(path)
for filename in filenames:
  os.rename(os.path.join(path, filename), os.path.join(path, filename.replace(' ', '-')))
