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

def get_dump(params):
	try:
		with open(os.devnull, 'w') as shutup:
			output = subprocess.check_output(params, stderr=shutup).decode('utf-8')
			return False, output
	except subprocess.CalledProcessError as cpe:
		return True, cpe.output.decode('utf-8')

champs = list_champs()
for champ in champs:
	print(champ)
	error, _, champ = compile_champ(ZAZ_ASM, champ)
	if error:
		continue
	zaz_error, zaz_output = get_dump([ZAZ_CW, '-v', '20', champ, champ])
	my_error, my_output = get_dump([MY_CW, '-verbose', champ, champ])
	if zaz_output != my_output:
		with open('/tmp/zaz', 'w') as f:
			f.write(zaz_output)
		with open('/tmp/me', 'w') as f:
			f.write(my_output)
		print(subprocess.check_output(['/usr/bin/diff', '/tmp/zaz', '/tmp/me']).decode('utf-8'))
		sys.exit(1)
