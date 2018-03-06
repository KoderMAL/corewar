import os, shutil, subprocess, sys, shlex, time, signal, io
 
 
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
    return True, cpe.output.decode('utf-8'), None
  result_file_name = os.path.splitext(champ_cpy)[0] + '.cor'
  with open(result_file_name, 'rb') as f:
    result_data = f.read()
  return False, bytearray(result_data), result_file_name
 
def run_command(command_1, command_2):
  print(command_1)
  print(command_2)
  print('\n')
  process_1 = subprocess.Popen(shlex.split(command_1), stdout=subprocess.PIPE)
  process_2 = subprocess.Popen(shlex.split(command_2), stdout=subprocess.PIPE)
  reader_1 = io.BufferedReader(process_1.stdout)
  reader_2 = io.BufferedReader(process_2.stdout)
  t0 = time.time()
  differences = 0
  while True:
    output_1 = reader_1.readline().decode('utf-8').lstrip()
    output_2 = reader_2.readline().decode('utf-8').lstrip()
    if output_1 != output_2:
      print(output_1.ljust(80) + output_2)
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
 
try:
  n_champs = int(sys.argv[1])
  if n_champs < 1 or n_champs > 4:
    raise Exception('Wrong number of champions')
except Exception:
  print('Usage:')
  print('  python3 diff_tests_corewar_verbose.py [n_champs]')
  print('  n_champs must be 1, 2, 3 or 4')
  sys.exit(0)

champs = list_champs()
iterator = iter(champs)
name_champs = []
for i in range(n_champs):
      name_champs.append(next(iterator))
while 1:
	print('')
	print(' vs. '.join(name_champs))
	compiled_champs = []
	for name_champ in name_champs:
		error, error_msg, champ = compile_champ(ZAZ_ASM, name_champ)
		if error:
			print(error_msg)
			break
		compiled_champs.append(champ)
	if not error:
		run_command('./resources/corewar -v 31 {}'.format(' '.join(compiled_champs)),
								'./corewar -zaz -verbose {}'.format(' '.join(compiled_champs)))
	for i in range(n_champs - 1):
		name_champs[i] = name_champs[i + 1]
	try:
		name_champs[-1] = next(iterator)
	except StopIteration:
		break
