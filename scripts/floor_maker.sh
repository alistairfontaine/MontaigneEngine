#!/bin/bash
mkdir -p models

python3 << 'EOF'
import struct
import zlib

width, height = 512, 512
img_data = bytearray()

# Generate a classic alternating grid pattern matrix
for y in range(height):
    img_data.append(0) # Standard PNG row filter byte
    for x in range(width):
        # Create dark grey and mid-grey alternating floor grid lines
        val = 160 if ((x // 32) + (y // 32)) % 2 == 0 else 70
        img_data.extend([val, val, val])

# Manual PNG raw chunk structural compilation sequence strings
def make_chunk(tag, data):
    return struct.pack('>I', len(data)) + tag + data + struct.pack('>I', zlib.crc32(tag + data))

header = b'\x89PNG\r\n\x1a\n'
ihdr = make_chunk(b'IHDR', struct.pack('>IIBBxxx', width, height, 8, 2))
idat = make_chunk(b'IDAT', zlib.compress(img_data))
iend = make_chunk(b'IEND', b'')

with open('models/floor.png', 'wb') as f:
    f.write(header + ihdr + idat + iend)

print("[Python] Successfully synthesized asset file: models/floor.png")
EOF
