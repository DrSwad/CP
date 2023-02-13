import sys, json;

string_data = ""
line = ""

while True:
  line = input()
  if line == "--":
    break
  string_data += line + '\n'

data1 = json.loads(string_data)

string_data = ""

for line in sys.stdin:
  string_data += line + '\n'

data2 = json.loads(string_data)

sorted_data1, sorted_data2 = json.dumps(data1, sort_keys=True), json.dumps(data2, sort_keys=True)

if sorted_data1 == sorted_data2:
  print("same")
else:
  print("different")
