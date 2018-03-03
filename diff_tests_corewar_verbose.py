import os, shutil, subprocess, sys, shlex


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

def run_command(command_1, command_2):
	print command_1
	print command_2
	process_1 = subprocess.Popen(shlex.split(command_1), stdout=subprocess.PIPE)
	process_2 = subprocess.Popen(shlex.split(command_2), stdout=subprocess.PIPE)
	while True:
		output_1 = process_1.stdout.readline()
		output_2 = process_2.stdout.readline()
		if output_1 != output_2:
			print output_1.ljust(50) + output_2
		if output_1 == '' and process_1.poll() is not None and output_2 == '' and process_2.poll() is not None:
			break

champs = list_champs()
iterator = iter(champs)
name_champ2 = next(iterator)
for champ in iterator:
	name_champ1 = name_champ2
	name_champ2 = next(iterator)
	print('{} vs. {}'.format(name_champ1, name_champ2))
	error, _, champ1 = compile_champ(ZAZ_ASM, name_champ1)
	if error:
			continue
	
	error, _, champ2 = compile_champ(ZAZ_ASM, name_champ2)
	if error:
			continue
	run_command('./resources/corewar -v 31 {} {}'.format(champ1, champ2),
	'./corewar -zaz -verbose {} {}'.format(champ1, champ2))
	print('')
	# zaz_output = open('{}/goinfre/zaz'.format(HOME_DIR), 'r').read()
	# my_output = open('{}/goinfre/me'.format(HOME_DIR), 'r').read()
	# if zaz_output != my_output:
	# 		# os.system('/usr/bin/vimdiff {}/goinfre/zaz {}/goinfre/me'.format(HOME_DIR, HOME_DIR))
	# 	sys.exit(1)
