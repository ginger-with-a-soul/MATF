def rec_perms(i, code, code_len):
	if i == code_len:
		print(code)
		return
	
	code[i] = True
	rec_perms(i + 1, code, code_len)
	code[i] = False
	rec_perms(i + 1, code, code_len)

if __name__  == "__main__":
	code = 4 * [None]
	rec_perms(0, code, len(code))