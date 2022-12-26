#
#
#   RAZMYSLOV KONSTANTIN. yoitz@yandex.ru (Yoitz Wolf - github)
#   EASY CSV -> TEX LONGTABLE CONVERTOR
#   
#   

import csv
import os
from typing import List, Tuple
from . import strutils

header_size = "l"
header_separator = "|"

header_scheme = r'\textbf{$~HERE~$}'
header_scheme_separator = " & "

line_elem_separator = " & "
line_separator = "\\\\ \n\\hline\n"

BASE = r"""

\begin{longtable}[H]{ |$~HEADER~$| }
    \caption{$~CAPTION~$}
    \label{tab:$~LABEL~$}\\
    \hline
    $~HEADERS~$
    $~LINES~$
    \hline
\end{longtable}


"""
def get_csv_data(filename: str, sep: str=";"):
    Data = []
    N = -1
    Headers = []
    with open(filename, mode ='r', encoding="utf8")as file:
        csvFile = csv.reader(file, delimiter=sep)
        Headers = next(csvFile)
        N = len(Headers)
        for line in csvFile:
            Data.append(
                tuple(map(
                    strutils.autotype,
                    line
                ))
            )

    return Headers, Data, N

def read_csv(filename: str, sep: str=";"):
    Data = []
    N = -1
    Headers = []
    with open(filename, mode ='r', encoding="utf8")as file:
        csvFile = csv.reader(file, delimiter=sep)
        Headers = next(csvFile)
        N = len(Headers)
        for line in csvFile:
            Data.append(
                line_elem_separator.join(line)
            )

    return Headers, Data, N 

def convertFromData(
    folder, label, caption,
    tHeaders: List[str], tData: List[Tuple]
):
    Headers: str = header_scheme_separator.join(
        map(
            lambda x: header_scheme.replace("$~HERE~$", x),
            tHeaders
        )
    )
    Data: str = line_separator + line_separator.join(
        list(map(
            lambda x: line_elem_separator.join(
                    map(strutils.autotype_to_str, x)
                ), tData))
    ) + line_separator
    
    rez = BASE \
        .replace(
            "$~HEADER~$", header_separator.join([header_size]*len(tHeaders))
        ) \
        .replace(
            "$~HEADERS~$", Headers
        ) \
        .replace(
            "$~CAPTION~$", caption
        ) \
        .replace(
            "$~LABEL~$", label
        ) \
        .replace(
            "$~LINES~$", Data
        )

    save(rez, folder + "/" + label + ".tex")


def convertFromCsv(filename: str, label: str, caption:str="", sep=";", folder="./textables"):
    Data: list = []
    Headers: list = []
    N:int = None

    if not os.path.isdir(folder):
        os.mkdir(folder)

    Headers, Data, N = read_csv(filename, sep=sep)
    convertFromData(folder, label, caption, Headers, Data)


def save(text, filename):
    with open(filename, 'w', encoding="utf8") as fs:
        fs.write(text)
        fs.close()