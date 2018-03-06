import os, shutil, subprocess, sys, shlex, time, signal
 
 
MY_CW = './corewar'
ZAZ_CW = './resources/corewar'
 
ZAZ_ASM = './resources/asm'
HOME_DIR = os.getenv('HOME')
COMPILE_DIR = os.path.join(HOME_DIR, 'goinfre')
 
TIMEOUT = 30
 
def list_champs():
  champs = []
  for root, subfolder, files in os.walk('.'):
    for file in files:
      name, ext = os.path.splitext(file)
      if ext == '.s':
        path = os.path.join(root, file)
        champs.append(path)
  return champs
 
def compile_champ(asm, champ):
  champ_cpy = os.path.join(COMPILE_DIR, os.path.basename(champ))
  shutil.copy(champ, champ_cpy)
  try:
    result = subprocess.check_output([asm, champ_cpy], stderr = subprocess.STDOUT).decode('utf-8')
  except subprocess.CalledProcessError as cpe:
    return True, cpe.output, None
  result_file_name = os.path.splitext(champ_cpy)[0] + '.cor'
  with open(result_file_name, 'rb') as f:
    result_data = f.read()
  return False, bytearray(result_data), result_file_name
 
def run_command(command_1, command_2):
  print command_1
  print command_2
  print('\n')
  process_1 = subprocess.Popen(shlex.split(command_1), stdout=subprocess.PIPE)
  process_2 = subprocess.Popen(shlex.split(command_2), stdout=subprocess.PIPE)
  t0 = time.time()
  differences = 0
  while True:
    output_1 = process_1.stdout.readline().lstrip()
    output_2 = process_2.stdout.readline().lstrip()
    if output_1 != output_2:
      print output_1.ljust(80) + output_2
      differences += 1
    if output_1 == '' and process_1.poll() is not None and output_2 == '' and process_2.poll() is not None:
      break
    if time.time() - t0 > 30.:
      print('{}s elapsed: aborting'.format(TIMEOUT))
      break
    if differences > 42:
      print('Too many errors: aborting')
      break
  if process_1.poll() is None:
    process_1.kill()
  if process_2.poll() is None:
    process_2.kill()
 
champs = list_champs()
iterator = iter(champs)
name_champ2 = next(iterator)
while 1:
  print('')
  name_champ1 = name_champ2
  try:
    name_champ2 = next(iterator)
  except StopIteration:
    break
  print('{} vs. {}'.format(name_champ1, name_champ2))
  error, error_msg, champ1 = compile_champ(ZAZ_ASM, name_champ1)
  if error:
    print(error_msg)  
    continue
  error, error_msg, champ2 = compile_champ(ZAZ_ASM, name_champ2)
commit:c84275
WIP on master: Auto stash before merge of "master" and "origin/master"
