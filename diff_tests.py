from unittest import TestCase
import os, shutil, subprocess, difflib

#MY_ASM = './asm'
MY_ASM = './Resources/asm'
ZAZ_ASM = './Resources/asm'
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

class CompilationError(Exception):
	pass

def compile_champ(asm, champ):
	champ_cpy = os.path.join(COMPILE_DIR, os.path.basename(champ))
	shutil.copy(champ, champ_cpy)
	try:
		result = subprocess.check_output([asm, champ_cpy], stderr = subprocess.STDOUT).decode('utf-8')
	except subprocess.CalledProcessError:
		raise CompilationError
	result_file_name = os.path.splitext(champ_cpy)[0] + '.cor'
	with open(result_file_name, 'rb') as f:
		result_data = f.read()
	return bytearray(result_data)

class TestAsm(TestCase):
	def test(self):
		champs = list_champs()
		for champ in champs:
			print(champ)
			try:
				my_result_data = compile_champ(MY_ASM, champ)
				my_error = False
			except CompilationError:
				my_error = True
				my_result_data = b''
			try:
				zaz_result_data = compile_champ(ZAZ_ASM, champ)
				zaz_error = False
			except CompilationError:
				zaz_error = True
				zaz_result_data = b''
			my_len = len(my_result_data)
			zaz_len = len(zaz_result_data)
			#if my_len > 100: my_result_data[42] += 1 # simulate error
			self.assertEqual(my_error, zaz_error, 'error error')
			self.assertEqual(my_len, zaz_len, 'wrong length: {} instead of {}'.format(my_len, zaz_len))
			for i in range(my_len):
				my_byte = my_result_data[i]
				zaz_byte = zaz_result_data[i]
				self.assertEqual(my_byte, zaz_byte,	'difference at byte {}: {} instead of {}'.format(i, my_byte, zaz_byte))
