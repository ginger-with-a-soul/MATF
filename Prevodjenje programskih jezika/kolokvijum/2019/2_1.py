#! /usr/bin/env python
import sys, re

def get_data(file):
	try:
		with open(file, "r") as f:
			return f.read()
	except IOError as e:
		print(e)
		sys.exit()

def game_reg():
	reg = re.compile(r'<igra id=\"[1-9][0-9]*\">.*?<\/igra>', re.DOTALL)
	return reg


def find_game_info(game_data):
	try:
		name = re.findall('<naziv>(.*?)<\/naziv>', game_data)[0]
		year = re.findall('<godina>(19[5-9][0-9]|200[0-9]|201[0-8])<\/godina>', game_data)[0]
		publisher = re.findall('<izdavac>(([A-Z0-9][a-z0-9 ]*)+)<\/izdavac>', game_data)[0]
		plat = re.findall('<platforme>((Playstation|Nintengo|Xbox|PC|,)+)<\/platforme>', game_data)[0]
		score = re.findall('<ocena>([0-9]\.[0-9]|10\.0)<\/ocena>', game_data)[0]
	except IndexError:
		return None

	return {
		"name": name,
		"year": year,
		"publisher": publisher,
		"plat": plat,
		"score": score
	}

def main():

	if len(sys.argv) < 2 or len(sys.argv) > 3		:
		print("Invalid program arguments")
		sys.exit()
	
	data = get_data("igre.xml")

	reg = game_reg()

	games = []
	for game in reg.finditer(data):
		game_data = game.group()
		game_info = find_game_info(game_data)
		if game_info is not None:
			games.append(game_info)

	if str(sys.argv[1]) == "-all":
		games.sort(key=lambda x 	: x["name"])
		for game in games:
			print(game["name"])

	if str(sys.argv[1]) == "-info" and str(sys.argv[2]) is not None:
		for game in games:
			if str(sys.argv[1]).lower() in str(game["name"]).lower():
				print(game["name"] + "(" + game["score"] + "/10)\n")
	elif str(sys.argv[1]) == "-i" and str(sys.argv[2]) is not None:
		for game in games:
			print(game["publisher"])
			if game["publisher"] == str(sys.argv[2]):
				print(game["name"] + "(" + game["year"] + ")")
	elif str(sys.argv[1]) == "-p" and str(sys.argv[2]) is not None:
		games.sort(key=lambda x: x["score"])
		for game in games:
			if str(sys.argv[2]) in str(game["plat"]):
				print(game["name"] + '\n')


if __name__ == "__main__":
	main()