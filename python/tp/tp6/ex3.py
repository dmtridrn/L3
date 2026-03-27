import re

def parse_line(s):
    m = r"^(\d{4}),(\d+),(\d+),(\Z+)$"
    motif = re.compile(m)
    res = motif.match(s)
    if res:
        return int(res.group(1)), int(res.group(2)), int(res.group(3)), res.group(4)
    return None


