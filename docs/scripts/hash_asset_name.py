import sys

args = sys.argv[1:]


# eg. aid_xwavebank_ghoulies_dvd1   ->  099edd11

for asset_name in args:
    hashed = 0

    for c in asset_name[4:]:
        hashed = (ord(c) & 0xdf) + hashed * 0x10
        has_flag = hashed & 0xf0000000
        if has_flag:
            hashed = hashed ^ (has_flag >> 24 | has_flag)

    print(f"{hashed:08x}")
