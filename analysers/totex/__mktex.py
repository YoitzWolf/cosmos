import sys
import os

from totex import *

have_to_make = [
    "g3/result_0"
]

def conver_all(here: str="./res", folder="./textables", funcname=None):
    r"./res/{}/tables/generations.csv"
    fn = funcname
    if not os.path.isdir(here):
        os.mkdir(here)
    if not os.path.isdir(folder):
        os.mkdir(folder)

    for func in os.scandir(here):
        if func.is_dir():
            fn = func.name if funcname is None else funcname

            if "_" in fn:
                fn = fn.replace("_", " ")
            
            for file in os.scandir(func):
                sub = ""

                if "result" in file.name:
                    #print("AA")
                    sub = f" (run {file.name.split('_')[-1]})"

                if file.is_file() and ".csv" in file.name:
                    texFromCsv(
                        here + "/" +func.name + "/" + file.name, # path
                        fn.replace(" ", "-") + "-" + '-'.join(file.name.split('.')[:-1]), #label
                        caption=f"{file.name.split('.')[0]} of {fn + sub} function",
                        folder=folder+"/"+func.name
                    )
                elif file.is_dir():
                    conver_all(here + "/" +func.name + "/" + file.name, folder=folder + "/" + func.name + "/" + file.name, funcname=fn+sub)

conver_all()