import sys
import os
import subprocess
import re
from time import time

def benchmark(func):
  def timer():
    start = time()
    func()
    stop = time()
    print('Time taken : %.3fs' %(stop - start))
    return
  return timer


section = ['section', 'subsection', 'subsubsection', 'paragraph']
text = ''

def gen(level):
  
  global text

  folders = [x for x in os.listdir(".") if os.path.isdir(x)]
  files = [x for x in os.listdir(".") if os.path.isfile(x)]
  
  folders.sort()
  files.sort()

  parent = os.getcwd()
  for folder in folders:
    text = text + '\\' + section[level] + '{' + folder + '}\n'
    child = parent + "/" + folder
    os.chdir(child)
    gen(level + 1)
    os.chdir(parent)

  for file in files:
    name, ext = os.path.splitext(file)
    if ext not in ['.cpp', '.py', '.java', '.tex']:
      continue
    name = re.sub('_','\\_', name)

    text = text + '\\' + section[level] + '{' + name + '}\n'
    text = text + ('\\input{' if ext == '.tex' else '\\cpp{') + '\"' + os.getcwd() + '/' + file + '\"' + '}\n'

@benchmark
def main():

  global text

  main_dir = os.getcwd()

  try:
    os.chdir('code')
  except:
    print("Error!\nFolder \'code\' not found!")
    sys.exit()

  gen(0)

  try:
    os.chdir(main_dir + '/template')
  except:
    print("Error!\nFolder \'template\' not found!")
    sys.exit()

  text = text + '\\end{multicols}{3}\n'
  text = text + '\\end{document}'

  file = open('template.tex', 'r')
  text = file.read() + text
  file.close()
  file = open('notebook.tex', 'w')
  file.write(text)
  file.close()
  print("Generating Notebook...")
  print("This may take a while. Please wait...")
  for i in range(2):
    subprocess.run('pdflatex -interaction=nonstopmode --shell-escape notebook.tex', shell=True, stdout=subprocess.PIPE)
  os.system('rm -r _minted-notebook')
  os.system('mv notebook.pdf ' + '\"' + main_dir + '\"')
  os.system('rm notebook.*')
  print('Done!')

main()