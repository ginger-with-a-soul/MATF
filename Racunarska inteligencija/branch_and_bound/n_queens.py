import numpy as np

def printSolution(board):
	n = board.shape[0]
	for i in range(n):
		for j in range(n):
			print(board[i][j], end = ' ')
		print()

def openTile(c, r, n, checkRow, checkD1, checkD2):
	return not (checkRow[r] or checkD1[c + r] or checkD2[c - r + n - 1])

def bnb(board, c, checkRow, checkD1, checkD2):
	n = board.shape[0]

	if c >= n:
		return True
	
	for r in range(n):
		if openTile(c, r, n, checkRow, checkD1, checkD2):
			board[r][c] = 'Q'
			checkRow[r] = True
			checkD1[c + r] = True
			checkD2[c - r + n - 1] = True
			if bnb(board, c + 1, checkRow, checkD1, checkD2):
				return True
			board[r][c] = '.'
			checkRow[r] = False
			checkD1[c + r] = False
			checkD2[c - r + n - 1] = False
	
	return False


def solve(n):
	board = np.full((n, n), '.', dtype = str)
	checkRow = np.full(n, False)
	checkD1 = np.full(2 * n - 1, False)
	checkD2 = np.full(2 * n - 1, False)

	if bnb(board, 0, checkRow, checkD1, checkD2):
		printSolution(board)
	else:
		print("No solution!")

if __name__ == "__main__":
	solve(int(input()))