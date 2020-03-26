from http.server import BaseHTTPRequestHandler, HTTPServer
import json
import sys


class HandleRequests(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        body = self.rfile.read(content_length)
        tests = json.loads(body)["tests"]
        ntests = []
        for test in tests:
            ntest = {
                "test": test["input"],
                "correct_answers": [test["output"].strip()]
            }
            ntests.append(ntest)
        with open(sys.argv[1] + ":tests", "w") as f:
            f.write(json.dumps(ntests))
        sys.exit()


host = 'localhost'
port = 12345
HTTPServer((host, port), HandleRequests).serve_forever()
