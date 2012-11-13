#!/usr/bin/python
from __future__ import division
import struct
import serdecode
import math

outfile = open("softscope.fifo", "w")

serdecode.resync()

while True:
    s = serdecode.read_frame()

    (speed, control) = struct.unpack("=hh", s)

    outfile.write(struct.pack("=ffff", speed, control, 0, 0))
    outfile.flush()

outfile.close()
