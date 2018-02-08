import os, shutil, subprocess, sys

MY_CW = './corewar'
ZAZ_CW = './resources/corewar'

ZAZ_ASM = './resources/asm'
COMPILE_DIR = '/tmp'

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
	os.rename(result_file_name, result_file_name)
	return False, bytearray(result_data), result_file_name

def get_dump(corewar, champ, n):
	try:
		with open(os.devnull, 'w') as shutup:
			output = subprocess.check_output([corewar, '-d', str(n), champ], stderr=shutup).decode('utf-8')
			return False, output
	except subprocess.CalledProcessError as cpe:
		return True, cpe.output

def hexdump(file_name, offset):
	subprocess.call(['hexdump', '-C', '-s {}'.format(offset), '-n 48', '-v', file_name])


champs = list_champs()
for champ in champs:
	print(champ)
	error, _, champ = compile_champ(ZAZ_ASM, champ)
	if error:
		continue
	for i in range(10):
		zaz_error, zaz_output = get_dump(ZAZ_CW, champ, i)
		my_error, my_output = get_dump(MY_CW, champ, i)
		if (zaz_error and not my_error) or (my_error and not zaz_error):
			if zaz_error:
				print zaz_output
				sys.exit(1)
			if my_error:
				print my_output
				sys.exit(1)
		if not my_error and zaz_output != my_output:
			print('dump number {}'.format(i))
			with open('/tmp/zaz', 'w') as f:
				f.write(zaz_output)
			with open('/tmp/me', 'w') as f:
				f.write(my_output)
			print(subprocess.check_output(['/usr/bin/diff', '/tmp/zaz', '/tmp/me']).decode('utf-8'))
			sys.exit(1)
