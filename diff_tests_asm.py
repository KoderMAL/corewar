import os, shutil, subprocess, sys

MY_ASM = './asm'
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

def compile_champ(asm, champ, suffix):
	champ_cpy = os.path.join(COMPILE_DIR, os.path.basename(champ))
	shutil.copy(champ, champ_cpy)
	try:
		result = subprocess.check_output([asm, champ_cpy], stderr = subprocess.STDOUT).decode('utf-8')
	except subprocess.CalledProcessError as cpe:
		return True, cpe.output, None
	result_file_name = os.path.splitext(champ_cpy)[0] + '.cor'
	with open(result_file_name, 'rb') as f:
		result_data = f.read()
	os.rename(result_file_name, result_file_name + suffix)
	return False, bytearray(result_data), result_file_name + suffix

def hexdump(file_name, offset):
	subprocess.call(['hexdump', '-C', '-s {}'.format(offset), '-n 48', '-v', file_name])


champs = list_champs()
for champ in champs:
	print(champ)
	zaz_error, zaz_result, zaz_file = compile_champ(ZAZ_ASM, champ, '.zaz')
	my_error, my_result, my_file = compile_champ(MY_ASM, champ, '.my')
	my_len = len(my_result)
	zaz_len = len(zaz_result)
	#if my_len > 100: my_result_data[42] += 1 # simulate error
	if my_error and not zaz_error:
		print('Our asm fails to compile but not zaz\'s:')
		print(my_result)
		sys.exit(1)
	if zaz_error and not my_error:
		print('Zaz\'s asm fails to compile but not ours:')
		print(zaz_result)
		sys.exit(1)
	if my_error == False and my_len != zaz_len:
		print('wrong length: {} instead of {}'.format(my_len, zaz_len))
		sys.exit(1)
	if my_error == False:
		for i in range(my_len):
			my_byte = my_result[i]
			zaz_byte = zaz_result[i]
			if my_byte != zaz_byte:
				print('difference at byte {:x}: {:02x} instead of {:02x}'.format(i, my_byte, zaz_byte))
				print('')
				offset = max(i - i % 16 - 16, 0)
				print('zaz\'s .cor:')
				hexdump(zaz_file, offset)
				print('')
				print('our .cor:')
				hexdump(my_file, offset)
				sys.exit(1)