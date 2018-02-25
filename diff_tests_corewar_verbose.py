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
	return False, bytearray(result_data), result_file_name

champs = list_champs()
for champ in champs:
	print(champ)
	error, _, champ = compile_champ(ZAZ_ASM, champ)
	if error:
		continue
	os.system('./resources/corewar -v 30 {} {} > /tmp/zaz'.format(champ, champ))
	os.system('./corewar -zaz -verbose {} {} > /tmp/me'.format(champ, champ))
	zaz_output = open('/tmp/zaz', 'r').read()
	my_output = open('/tmp/me', 'r').read()
	if zaz_output != my_output:
		os.system('/usr/bin/vimdiff /tmp/zaz /tmp/me')
		sys.exit(1)
