from unittest import TestCase
import os, shutil, subprocess

MY_ASM = './asm'
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
	return result_data

class TestAsm(TestCase):
	def test(self):
		champs = list_champs()
		for champ in champs:
			print(champ)
			try:
				compile_champ(ZAZ_ASM, champ)
				my_error = False
			except CompilationError:
				my_error = True
				my_result_data = b''
			try:
				compile_champ(ZAZ_ASM, champ)
				zaz_error = False
			except CompilationError:
				zaz_error = True
				zaz_result_data = b''
			self.assertEqual(my_error, zaz_error)
			self.assertEqual(my_result_data, zaz_result_data)
