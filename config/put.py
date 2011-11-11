import sys
import httplib, urllib

if (len(sys.argv) != 3):
    print "usage: "+sys.argv[0]+" <file> <dest_file>\n";
    exit(1)

localfile = sys.argv[1]
file = sys.argv[2]

f = open(localfile,'r')
if (not f):
    exit(3)
file_data = f.read()

params = urllib.urlencode({'fn': file, 'op': 'put', 'data': file_data})
print(params)
headers = {"Content-type": "application/x-www-form-urlencoded",
           "Accept": "text/plain"}


conn = httplib.HTTPConnection("rx.managed.mst.edu")
conn.request("POST", "/collect/mm/", params, headers)


response = conn.getresponse()
if (response.status == 200):
    exit(0);
else:
    print response.status, response.reason

conn.close()

