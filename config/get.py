import sys
import httplib

if (len(sys.argv) != 2):
    exit(1)

file = sys.argv[1]

conn = httplib.HTTPConnection("rx.managed.mst.edu")
conn.request("GET", "/collect/mm/?fn="+file+"&op=get")
r1 = conn.getresponse()

if (r1.status != 200):
    print r1.status, r1.reason
else:
    content = r1.read()
    print content

conn.close()
