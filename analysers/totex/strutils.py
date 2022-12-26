

# 
# TO STRING BLOCK
# 

from ast import Num


def make_tex_safe(val: str) -> str:
    # make all Tex symbols safe
    # Example: make_tex_safe("$\Delta$") -> "\$\\Delta\$"
    pass


def to_float_str(val: float, rounds: int = None) -> str:
    return str(round(val, rounds) if rounds is not None else val).replace(".", ",")

def to_int_str(val: float, rounds: int = None) -> str:
    return str(round(val, rounds) if rounds is not None else val)

def autotype_to_str(val: Num, **kwargs) -> str:
    if val.__class__ is float:
        return to_float_str(val, **kwargs)
    elif val.__class__ is int:
        return to_int_str(val, **kwargs)
    
    return val

# 
# FROM STRING BLOCK
#

def to_float(val: str) -> float:
    return float(val.replace(",", "."))

def to_int(val: str) -> int:
    return int(val)

def autotype(val: str) -> Num:
    if "." or "," in val:
        return to_float(val)
    elif val.isdigit():
        return to_int(val)
    else:
        return val
