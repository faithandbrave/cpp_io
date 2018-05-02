import glob
import os

include_dir = "include/cpp_io"
dir_queue = ["stream", "traits", "format", "printer", "unified", ""]

single_header = "#pragma once\n"
for dir_s in dir_queue:
    for p in glob.glob("{}/{}/*.hpp".format(include_dir, dir_s)):
        with open(p) as f:
            for line in f:
                if line.startswith("#pragma once"):
                    continue

                if line.startswith("#include \""):
                    continue

                single_header = single_header + line

target_dir = "single_header/cpp_io"
os.makedirs(target_dir, exist_ok=True)
with open("{}/io.hpp".format(target_dir), 'w') as f:
    f.write(single_header)
