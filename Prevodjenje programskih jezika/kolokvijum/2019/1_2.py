#! /usr/bin/evn python

import sys, re, os

def read_file(name):
    try:
        with open(name, "r") as d:
            return d.read()
    except IOError as e:
        print(e)
        sys.exit()

def parse_args(args):

    arg_map = {
        "name" : False,
        "version" : False,
        "repo" : False,
        "web" : False,
        "desc" : False,
        "all" : False
    }

    if "-a" in args:
        arg_map["all"] = True
        return arg_map, None

    if "-n" in args: arg_map["name"] = True
    if "-v" in args: arg_map["version"] = True
    if "-r" in args: arg_map["repo"] = True
    if "-w" in args: arg_map["web"] = True
    if "-d" in args: arg_map["desc"] = True

    return arg_map, args[-1]

def get_pack_reg():
    reg = re.compile(r'<paket\s*id=\"[1-9][0-9]*\">.*?<\/paket>', re.DOTALL)
    return reg

def get_package_details(pack):
    try:
        name = re.findall('<naziv>([a-z0-9]+?)<\/naziv>', pack)[0]
        version = re.findall('<verzija>([0-9]\.[0-9]\.[0-9])<\/verzija>', pack)[0]
        repo = re.findall('<repo>(gitlab|github|bitbucket)<\/repo>', pack)[0]
        desc = re.findall('<opis>(.*?)<\/opis>', pack)[0]
        web = re.findall('<veb>((www\.)?(.*?)\.(org|com))<\/veb>', pack)[0]
    except IndexError:
        return None

    return {
        "name" : name,
        "version" : version,
        "desc" : desc,
        "repo" : repo,
        "web" : web
    }

def pretty_package_show(p):
    return '[{}] v{} {}\n{}\n{}'.format(p["name"], p["version"], p["repo"], p["web"], p["desc"])

def main():
    if(len(sys.argv) < 2 or len(sys.argv) > 6):
        print("Invalid program arguments")
        sys.exit()

    data = read_file("paketi.xml")

    args, package_name = parse_args(sys.argv)

    reg = get_pack_reg()
    packages = []

    for package in reg.finditer(data):
        pack_data = package.group()
        package_details = get_package_details(pack_data)
        if package_details != None:
            packages.append(package_details)

    if args["all"]:
        packages.sort(key=lambda x : x["name"])
        for pack in packages:
            print(pretty_package_show(pack))
            print()
    else:
        i = -1
        for k, p in enumerate(packages):
            if p["name"] == package_name:
                i = k
                break
        if i != -1:
            if args["desc"]: print(packages[i]["desc"])
            if args["web"]: print(packages[i]["web"])
            if args["version"]: print(packages[i]["version"])
            if args["repo"]: print(packages[i]["repo"])
        else:
            print("Package " + package_name + "was not found")

if __name__ == "__main__":
    main()