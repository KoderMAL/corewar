import os, shutil, subprocess, sys

MY_CW = './corewar'
ZAZ_CW = './resources/corewar'

ZAZ_ASM = './resources/asm'
HOME_DIR = os.getenv('HOME')
COMPILE_DIR = os.path.join(HOME_DIR, 'goinfre')

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

champs = list_champs()
for champ in champs:
	print(champ)
	error, _, champ = compile_champ(ZAZ_ASM, champ)
	if error:
		continue
	os.system('./resources/corewar -v 31 {} {} > {}/goinfre/zaz'.format(champ, champ, HOME_DIR))
	os.system('./corewar -zaz -verbose {} {} > {}/goinfre/me'.format(champ, champ, HOME_DIR))
	zaz_output = open('{}/goinfre/zaz'.format(HOME_DIR), 'r').read()
	my_output = open('{}/goinfre/me'.format(HOME_DIR), 'r').read()
	if zaz_output != my_output:
		os.system('/usr/bin/vimdiff {}/goinfre/zaz {}/goinfre/me'.format(HOME_DIR, HOME_DIR))
		sys.exit(1)
