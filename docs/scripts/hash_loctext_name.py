import sys
import struct

args = sys.argv[1:]

for asset_name in args:
    acc = 0
    ret = 0

    for c in asset_name:
        acc = acc * 0x10 + ord(c)
        masked = acc & 0xf000
        if masked & 0xffff:
            acc = acc ^ (masked >> 8 | masked)

        ret: int = struct.unpack("<H", acc.to_bytes(2, byteorder="big"))[0]

    print(f"{ret:04x}")
